#include <iostream>

#include <termios.h>

#include "ND100GPS.hpp"

int main()
{

    try {

        char const *porta = "/dev/ttyUSB0";

        ND100GPS GPS(porta, B38400);
        // GPS.setAtributos(B38400);   /*baudrate B38400, 8 bits, no parity, 1 stop bit */
        GPS.setMinCont(0); /* set to pure timed read */
        GPS.getLeitura();
        // GPS.getArquivo("saida_GPS.txt");
    }
    catch (std::exception &e) {
        std::cout << "Erro: " << e.what() << "\n";
    }

    return 0;
}
