#ifndef ND100GPS_HPP_
#define ND100GPS_HPP_
//**********************************************
//  Class ND-100 GPS Dongle (C++11)
//
//  Implemented for study purposes.
//
//  License: GPLv3
//  Author: Alan Franco - https://github.com/fzappa/
//  Rev.: 28/07/2017 (PT_BR)
//*********************************************
#include <iostream>

class ND100GPS {

  private:
    void pAbrePorta(void);
    char const *pPorta;
    int pTaxaTrans;
    int pfd;  // file descriptor

  public:
    ND100GPS(char const *Porta, unsigned int TaxaTrans);
    ~ND100GPS(void);  // Destrutor

    int setAtributos(unsigned int baudrate);
    void setMinCont(unsigned int mcount);
    void getLeitura(void);
    void getArquivo(const char *arq);
};

#endif
