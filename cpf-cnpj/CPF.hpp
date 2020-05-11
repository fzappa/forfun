/* 
 * File:   CPF.hpp
 * Author: alan
 *
 * Created on 9 de Fevereiro de 2015, 20:57
 */

#ifndef CPF_HPP
#define	CPF_HPP

class CPF {
public:
    int put_convsi(char x1);
    void set_leCpf();
    void get_verifCpf();
    void get_local();
    CPF();
//    CPF(const CPF& orig);
    virtual ~CPF();
    
    
private:
    char cpf9[10], regiao[10][80];
    int i, soma, verif, cpf9d[10];

};

#endif	/* CPF_HPP */

