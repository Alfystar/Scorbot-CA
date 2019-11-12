//
// Created by alfyhack on 10/11/19.
//

#ifndef PCLISTENUART_UARTDRIVER_H
#define PCLISTENUART_UARTDRIVER_H

// #define UartDriverDebug 1

#ifdef linuxSide
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
#include <semaphore.h>
#include <mutex>
#include <DataTransfert_AllInclude.h>

#else
#include "Arduino.h"
#include <stdlib.h>
#include "../globalDef.h"
#include "../circularBuffer/CircularBuffer.h"
#endif

#define sizeofArray(x)  sizeof(x)/sizeof(x[0])
#ifdef linuxSide
#define cbSize 32
#define dataSize 4096
#else
#define cbSize 8
#define dataSize 4*sizeof(uart2Ard)
#endif
#ifdef linuxSide
#else
#endif

namespace Uart {
    using namespace DataPrimitive;
    using namespace DataManipolation;

    enum uartState
            : char {
        waitStart, waitType, waitEnd
    };

    class UartDriver {
    public:
#ifdef linuxSide
        UartDriver(const std::string &device) noexcept(false);
#else
        UartDriver(HardwareSerial *serial, long vel);
#endif
        /// Data Send
        // &pack è l'indirizzo da dove il sender si va a copiare i dati
        void packSend(uartPackType type, data2Rasp *pack);
#ifdef linuxSide
#else
        void serialIsr();
        void serialTrySend();
#endif
        /// Data get
        uart2Rasp *getLastRecive();
#ifdef linuxSide
        uart2Rasp *getLastReciveWait();
#endif
        size_t Available();

        /// Data print for debug
        static void serialPackDb(uart2Ard &p);
        static void serialPackDb(uart2Rasp &p);
    private:
        //todo Rendere un singleton parametrico la classe
        //http://www.jot.fm/issues/issue_2007_03/column2/
        //UartDriver *istance;

        //Variabili della porta Seriale
#ifdef linuxSide
        int fd;                     //file descriptor della com
        struct termios config;      //Struttura di controllo della uart
        std::thread *readerTh;      //Puntatore al Thread avviato
#else
        HardwareSerial *com;
#endif

        //Variabili della coda di ricezione dati
        unsigned char reciveBuf[dataSize];   //4096
        CircularBuffer<unsigned char> *cbByteRecive;

        uartState stateUart = waitStart;
        size_t potPackStart;
        size_t potPackType;
        size_t expettedEnd;


        //Variabili della coda di pacchetti riconosciuti
        uart2Rasp cbReciveBuf[cbSize];
        CircularBuffer<uart2Rasp> *cbRecive;
        sem_t recivedPackSem;

        //Variabili della coda di invio
#ifdef linuxSide
        //Probabilmente non servono poichè oltre la write c'e un buffer del S.O.
#else
        uart2Rasp cbSendPackBuf[packBufSize];
        CircularBuffer<uart2Rasp> *cbSend;
#endif

        //Reader Thread
#ifdef linuxSide
        static void uartReader(UartDriver *d);
#endif
        //State machine to undestand pack
        void dataDiscover();
        size_t sizeMessage(uartPackType t);
#ifdef linuxSide
#else
        void clearPackBuf();
        void clearSerialBuf();
#endif
    };
}
#endif //PCLISTENUART_UARTDRIVER_H
