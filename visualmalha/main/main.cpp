//**********************************************
//  Main for VisualMalha test.
//
//  Implemented for study purposes.
//  Uses the libIGL (http://libigl.github.io/libigl/)
//  and Eigen (http://eigen.tuxfamily.org/).
//
//
//  License: GPLv3
//  Author: Alan Franco - https://github.com/fzappa/
//  Rev.: 28/05/2017 (PT_BR)
//*********************************************
#include "VisualMalha.hpp"

using namespace std;
using namespace malha;

int main(int argc, char *argv[])
{
    try {

        if (argc >= 1) {
            VisualMalha A;
            A.carrega(argv[1]);
            A.showObject(true);
            A.setBoundingBox(true);
            A.setCurvaturaGaussiana(false);
            A.visualiza();
        }
    }
    catch (std::exception &e) {
        cout << "Erro: " << e.what() << "\n";
    }

    return 0;
}
