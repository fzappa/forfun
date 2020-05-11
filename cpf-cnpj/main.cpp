/* 
 * File:   main.cpp
 * Author: alan
 *
 * Created on 9 de Fevereiro de 2015, 20:37
 */

#include <iostream>
#include <stdlib.h>   // system    
#include "CPF.hpp"
#include "CNPJ.hpp"

using namespace std;

/*
 * 
 */
int main() 
{
    int opcao;
    CPF cpf;
    CNPJ cnpj;

//replay:
    system("clear");
    cout << "Digite 0 para CPF ou 1 para CNPJ: ";
    cin >> opcao;
    
    switch(opcao)
    {
        case 0:
            cpf.set_leCpf();
            cpf.get_verifCpf();
            cpf.get_local();
            break;
        
        case 1:
            cnpj.leCnpj();
            cnpj.verifCnpj();
            break;
            
        default:
            cout << "Opção inválida\nSaindo do programa.\n";
//            goto replay;
            break;
    }
    

    return 0;
}

