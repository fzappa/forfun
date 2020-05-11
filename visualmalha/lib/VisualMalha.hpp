#ifndef VISUALMALHA_HPP
#define VISUALMALHA_HPP
//**********************************************
//  Class for visualize Mesh in .obj format. (C++11)
//
//  Implemented for study purposes.
//  Uses the libIGL (http://libigl.github.io/libigl/)
//  and Eigen (http://eigen.tuxfamily.org/).
//
//
//  License: GPLv3
//  Author: Alan Franco - https://github.com/fzappa/
//  Rev.: 25/05/2017 (PT_BR)
//*********************************************

#include <Eigen/Dense>
#include <igl/viewer/Viewer.h>
#include <iostream>
#include <string>

namespace malha {

class VisualMalha {
  private:
    Eigen::MatrixXd privVertices;
    Eigen::MatrixXi privFaces;
    bool privBox;
    bool privObject;
    bool privCurvGauss;
    void geraBox(igl::viewer::Viewer &);
    void curvGauss(igl::viewer::Viewer &);
    void campoVetor(igl::viewer::Viewer &);

  public:
    VisualMalha(void);
    VisualMalha(const std::string &);
    virtual ~VisualMalha(void) noexcept(true){};  // Destrutor

    // Funcoes membro
    void carrega(const std::string &);
    void visualiza(void);

    bool getBoundingBox(void);
    void setBoundingBox(const bool &);

    void showObject(const bool &);
    bool statusObject(void);

    bool getCurvaturaGaussiana(void);
    void setCurvaturaGaussiana(const bool &);

};  // class

}  // namespace malha

#endif
