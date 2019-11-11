//
// Created by alfyhack on 10/11/19.
//

#ifndef PCLISTENUART_UARTDRIVER_H
#define PCLISTENUART_UARTDRIVER_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include "UartExeption.h"
#include <CircularBuffer.h>
#include <thread>
#include <mutex>
#include <DataTransfert_AllInclude.h>

namespace Uart {
    using namespace DataPrimitive;
    using namespace DataManipolation;

    enum uartState
            : char {
        waitStart, waitType, waitEnd
    };

    class UartDriver {
    public:
        UartDriver(const std::string &device) noexcept(false);
        void
        packSend(uartPackType type, data2Rasp *pack); // &pack è l'indirizzo da dove il sender si va a copiare i dati

        size_t Available();
        uart2Rasp *getLastRecive();

        static void serialPackDb(uart2Ard &p);
        static void serialPackDb(uart2Rasp &p);
    private:
        //todo Rendere un singleton parametrico la classe
        //http://www.jot.fm/issues/issue_2007_03/column2/
        UartDriver *istance;

        //Variabili della porta
        int fd;                     //file descriptor della com
        struct termios config;      //Struttura di controllo della uart

        //Variabili della coda di ricezione dati
        unsigned char reciveBuf[256];   //4096
        CircularBuffer<unsigned char> *cbByteRecive;

        uartState stateUart = waitStart;
        char potPackStart;
        char potPackType;
        char expettedEnd;


        //Variabili della coda di pacchetti riconosciuti
        uart2Rasp cbReciveBuf[32];
        CircularBuffer<uart2Rasp> *cbRecive;
        unsigned int packAvailable;

        //Variabili della coda di invio
        //Probabilmente non servono poichè oltre la write c'e un buffer del S.O.
        /*
        uart2Ard cbSendBuf[32];
        CircularBuffer<uart2Ard> *cbSend;
        */

        std::thread *readerTh;

        //Reader Thread
        static void uartReader(UartDriver *d);

        //State machine to undestand pack
        void dataDiscover();
        char sizeMessage(uartPackType t);


    };
}
#endif //PCLISTENUART_UARTDRIVER_H
