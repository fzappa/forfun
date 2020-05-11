/* 
 * File:   CNPJ.hpp
 * Author: alan
 *
 * Created on 9 de Fevereiro de 2015, 21:04
 */

#ifndef CNPJ_HPP
#define	CNPJ_HPP

class CNPJ {
public:
    CNPJ();
//    CNPJ(const CNPJ& orig);
    virtual ~CNPJ();
    int convsi(char x1);
    void leCnpj();
    void verifCnpj();
    

private:
    char cnpj[13], regiao[9][80];
    int i, soma, verif, cnpjd[13];
};

#endif	/* CNPJ_HPP */

