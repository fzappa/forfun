/*
 * File:   CPF.cpp
 * Author: alan
 *
 * Created on 9 de Fevereiro de 2015, 20:57
 */
#include "CPF.hpp"
#include <iostream>

using namespace std;

CPF::CPF() {}

/*
CPF::CPF(const CPF& orig) {
}
*/

CPF::~CPF() {}

int CPF::put_convsi(char x)  // Converte char para inteiro
{
    if ((x >= '0') && (x <= '9'))
        return (x - '0');
    else
        return 0;
}

void CPF::set_leCpf()
{
    cout << "\n\nEntre com os 9 primeiros digitos do CPF: ";
    cin >> cpf9;
    //    fgets(cpf9, sizeof(cpf9), stdin);
}

void CPF::get_verifCpf()
{
    for (i = 0; i <= 8; i++) cpf9d[i] = put_convsi(cpf9[i]);  // converte os 9 primeiros digitos char para
    int

        soma = 0;
    for (i = 0; i <= 8; i++) soma += cpf9d[i] * (10 - i);

    verif = soma % 11;

    if (verif == 0 || verif == 1)
        cpf9d[9] = 0;
    else
        cpf9d[9] = 11 - verif;

    soma = 0;
    for (i = 0; i <= 9; i++) soma += cpf9d[i] * (11 - i);

    verif = soma % 11;

    if (verif == 0 || verif == 1)
        cpf9d[10] = 0;
    else
        cpf9d[10] = 11 - verif;

    cout << "CPF: " << cpf9 << "-" << cpf9d[9] << cpf9d[10] << "\n";
}

void CPF::get_local()
{
    char regiao[10][80] = {"Rio Grande do Sul",
                           "Distrito Federal, Goiás, Mato Grosso do Sul, Mato Grosso ou Tocantins",
                           "Pará, Amazonas, Acre, Amapá, Rondônia ou Roraima",
                           "Ceará, Maranhão ou Piauí",
                           "Pernambuco, Rio Grande do Norte, Paraíba ou Alagoas",
                           "Bahia ou Sergipe",
                           "Minas Gerais",
                           "Rio de Janeiro ou Espírito Santo",
                           "São Paulo",
                           "Paraná ou Santa Catarina"};

    cout << "Seu CPF foi emitido em: " << regiao[cpf9d[8]] << "\n\n";
}
