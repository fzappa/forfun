//**********************************************
//  Class for visualize Mesh in .obj format. (C++11)
//
//  Implemented for study purposes.
//  Uses the libIGL (http://libigl.github.io/libigl/)
//  and Eigen (http://eigen.tuxfamily.org/).
//
//  Types T accepted: float, double e complex<double>
//
//  License: GPLv3
//  Author: Alan Franco - https://github.com/fzappa/
//  Rev.: 25/05/2017 (PT_BR)
//*********************************************

#include <igl/avg_edge_length.h>
#include <igl/barycenter.h>
#include <igl/gaussian_curvature.h>
#include <igl/invert_diag.h>
#include <igl/jet.h>
#include <igl/local_basis.h>
#include <igl/massmatrix.h>
#include <igl/read_triangle_mesh.h>

#include "VisualMalha.hpp"

namespace malha {
VisualMalha::VisualMalha()
{
    privBox       = false;
    privObject    = true;
    privCurvGauss = false;
}

VisualMalha::VisualMalha(const std::string &arq)
{
    igl::read_triangle_mesh(arq, privVertices, privFaces);
}

void VisualMalha::carrega(const std::string &arq)
{
    igl::read_triangle_mesh(arq, privVertices, privFaces);
}

bool VisualMalha::getBoundingBox(void) { return privBox; }
void VisualMalha::setBoundingBox(const bool &val) { privBox = val; }

bool VisualMalha::statusObject(void) { return privObject; }
void VisualMalha::showObject(const bool &val) { privObject = val; }

bool VisualMalha::getCurvaturaGaussiana(void) { return privCurvGauss; }
void VisualMalha::setCurvaturaGaussiana(const bool &val) { privCurvGauss = val; }

void VisualMalha::visualiza(void)
{

    igl::viewer::Viewer Visualiza;

    // Box or Object
    if ((privBox == true) && (privObject == true)) {
        Visualiza.data.set_mesh(privVertices, privFaces);
        VisualMalha::geraBox(Visualiza);
    }
    else if ((privBox == false) && (privObject == true)) {
        Visualiza.data.set_mesh(privVertices, privFaces);
    }
    else if ((privBox == true) && (privObject == false)) {
        VisualMalha::geraBox(Visualiza);
    }

    // Gaussian curvature
    if (privCurvGauss == true)
        VisualMalha::curvGauss(Visualiza);

    Visualiza.launch();

}  // VisualMalha::visualiza()

// Funcoes privadas

void VisualMalha::geraBox(igl::viewer::Viewer &Janela)
{
    // Encontra o bounding box
    Eigen::Vector3d m = privVertices.colwise().minCoeff();
    Eigen::Vector3d M = privVertices.colwise().maxCoeff();

    // Vertices do bounding box
    Eigen::MatrixXd V_box(8, 3);
    V_box << m(0), m(1), m(2), M(0), m(1), m(2), M(0), M(1), m(2), m(0), M(1), m(2), m(0), m(1),
        M(2), M(0), m(1), M(2), M(0), M(1), M(2), m(0), M(1), M(2);

    // bordas do bounding box
    Eigen::MatrixXi E_box(12, 2);
    E_box << 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 7, 3;

    // Plota os vertices do bounding box como pontos
    Janela.data.add_points(V_box, Eigen::RowVector3d(1, 0, 0));

    // Plota as bordas do bounding box
    for (unsigned i = 0; i < E_box.rows(); ++i)
        Janela.data.add_edges(V_box.row(E_box(i, 0)), V_box.row(E_box(i, 1)),
                              Eigen::RowVector3d(1, 0, 0));

}  // VisualMalha::geraBox

void VisualMalha::curvGauss(igl::viewer::Viewer &Janela)
{

    Eigen::VectorXd K;

    // Compute integral of Gaussian curvature
    igl::gaussian_curvature(privVertices, privFaces, K);

    // Compute mass matrix
    Eigen::SparseMatrix<double> M, Minv;
    igl::massmatrix(privVertices, privFaces, igl::MASSMATRIX_TYPE_DEFAULT, M);
    igl::invert_diag(M, Minv);

    // Divide by area to get integral average
    K = (Minv * K).eval();

    // Compute pseudocolor
    Eigen::MatrixXd C;
    igl::jet(K, true, C);

    Janela.data.set_colors(C);

}  // VisualMalha::curvGauss

void VisualMalha::campoVetor(igl::viewer::Viewer &Janela) {}  // VisualMalha::campoVetor

}  // namespace malha
