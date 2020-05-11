/* 
 * File:   CNPJ.cpp
 * Author: alan
 * 
 * Created on 9 de Fevereiro de 2015, 21:04
 */
#include <iostream>
#include "CNPJ.hpp"

using namespace std;

CNPJ::CNPJ() {
}

/*
CNPJ::CNPJ(const CNPJ& orig) {
}
  
*/

CNPJ::~CNPJ() {
}

int CNPJ::convsi(char x)  // Converte char para inteiro
{
    if((x >='0') && (x <='9'))
        return (x - '0');
    else
        return 0;
}


void CNPJ::leCnpj()
{
    cout << "\nEntre com os 12 primeiros digitos do CNPJ: ";
    cin >> cnpj;
//    fgets(cnpj, sizeof(cnpj), stdin);
}


void CNPJ::verifCnpj()
{
    for(i=0;i<=11;i++)
    cnpjd[i] = convsi(cnpj[i]); //converte os 12 primeiros digitos char para int

    soma=0;
// Calcula o primeiro digito verificador
    for(i=0;i<=3;i++) // 4 primeiro digitos
        soma += cnpjd[i]*(6+i);
    
    for(i=4;i<=11;i++) // do 5 ao 12 digito
        soma += cnpjd[i]*(i-2);
    
    verif = soma%11;
    cnpjd[12] = verif;
      
    soma=0;
// Calcula o segundo digito verificador
    for(i=0;i<=4;i++) // 5 primeiro digitos
        soma += cnpjd[i]*(5+i);
    
    for(i=5;i<=12;i++) // do 5 ao 12 digito
        soma += cnpjd[i]*(i-3);
    
    verif = soma%11;
    cnpjd[13] = verif;

// Mostra o resultado
    cout << "CNPJ: " ;
    for(i=0;i<=1;i++)
        cout << cnpj[i] ;
    cout << ".";
    for(i=2;i<=4;i++)
        cout << cnpj[i] ;
    cout << ".";
    for(i=5;i<=7;i++)
        cout << cnpj[i] ;
    cout <<"/";
    for(i=8;i<=11;i++)
        cout << cnpj[i] ;
    cout << "-" << cnpjd[12] << cnpjd[13] << "\n\n";

}

