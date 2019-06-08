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
#include <fstream>
#include <boost/circular_buffer.hpp>
#include <boost/lexical_cast.hpp> // conversao de tipos

// C libs
#include <errno.h>
#include <fcntl.h> 
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "ND100GPS.hpp"

ND100GPS::~ND100GPS(void){
    delete pPorta;
}

ND100GPS::ND100GPS(char const *Porta, unsigned int TaxaTrans){

    pfd = 0;
    pPorta = Porta;
    pTaxaTrans = TaxaTrans;
    setAtributos(pTaxaTrans);
    
}


int ND100GPS::setAtributos(unsigned int baudrate){

    pAbrePorta();

        struct termios ND_100;

        if (tcgetattr(pfd, &ND_100) < 0) {
            std::cerr << "[ND100GPS::setAtributos] Erro tcgetattr: " << strerror(errno) << std::endl;
            throw 10;
        }

        cfsetospeed(&ND_100, (speed_t)baudrate);
        cfsetispeed(&ND_100, (speed_t)baudrate);

        ND_100.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
        ND_100.c_cflag &= ~CSIZE;
        ND_100.c_cflag |= CS8;         /* 8-bit characters */
        ND_100.c_cflag &= ~PARENB;     /* no parity bit */
        ND_100.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
        ND_100.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

        /* setup for non-canonical mode */
        ND_100.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
        ND_100.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        ND_100.c_oflag &= ~OPOST;

        /* fetch bytes as they become available */
        ND_100.c_cc[VMIN] = 1;
        ND_100.c_cc[VTIME] = 1;

        if (tcsetattr(pfd, TCSANOW, &ND_100) != 0) {
            std::cerr << "[ND100GPS::setAtributos] Erro tcsetattr: " << strerror(errno) << std::endl;
            throw 11;
        }
    

    return 0;
}


void ND100GPS::setMinCont(unsigned int mcount){

    struct termios ND_100;

    if (tcgetattr(pfd, &ND_100) < 0) {
        std::cerr << "[ND100GPS::setMinCont] Error tcgetattr: " << strerror(errno) << std::endl;
        throw 12;
    }

    // UNIX termios VMIN and VTIME
    ND_100.c_cc[VMIN] = mcount ? true : false; // VMIN is a character count ranging from 0 to 255 characters
    ND_100.c_cc[VTIME] = 5;             // VTIME is time measured in 0.1 second intervals, (0 to 25.5 seconds)

    if (tcsetattr(pfd, TCSANOW, &ND_100) < 0){
        std::cerr << "[ND100GPS::setMinCont] Erro tcsetattr: " << strerror(errno) << std::endl;
        throw 13;
    }
}

void ND100GPS::getLeitura(void){

    int noDataTime = 0;

    do {
        unsigned char buf[80] = {'\0'};
        //boost::circular_buffer<unsigned char> serialBuffer(80); 
        int rdlen;

        rdlen = read(pfd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
            noDataTime = 0;
			buf[rdlen] = '\0';
            std::cout << buf;
            //if(0 == memcmp(buf, "$", 1))
            //    std::cout << "GPGGA";
            //serialBuffer.push_back(*buf);
        } else {
            noDataTime++;
            if (noDataTime >= 5){
                std::cerr << "[ND100GPS::getDados] Falha de comunicação com o dispositivo." << std::endl;
                throw 14;
            }
        }

    } while (noDataTime < 5);
}



void ND100GPS::getArquivo(const char *arq){

    int noDataTime = 0; // Stop if unplug USB
    std::fstream arqsaida;
    arqsaida.open (arq, std::fstream::out | std::fstream::trunc);
    
    do {
        unsigned char buf[80] = "";
        int rdlen;

        rdlen = read(pfd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
            noDataTime = 0;
			buf[rdlen] = '\0';
            arqsaida << boost::lexical_cast<std::string>(buf); //Just I wanna ;)
            //arqsaida << buf;
        } else {
            noDataTime++;
            if (noDataTime >= 5){
                arqsaida.close();
                std::cerr << "[ND100GPS::getDados] Falha de comunicação com o dispositivo." << std::endl;
                throw 14;
            }
        }
    } while (noDataTime < 5);
}






// Funcoes membro
void ND100GPS::pAbrePorta(void){
    
    pfd = open(pPorta, O_RDWR | O_NOCTTY | O_SYNC);
    if (pfd < 0) {
        std::cerr << "[ND100GPS::AbrePorta] Erro ao abrir a porta " << pPorta << " : " << strerror(errno) << std::endl;
        throw 15;
    }
}