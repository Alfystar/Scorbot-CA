//
// Created by alfyhack on 10/11/19.
//

#ifndef PCLISTENUART_UARTDRIVER_H
#define PCLISTENUART_UARTDRIVER_H

//#define UartDriverDebug 1
//#define CMD_Send_PRINT 1

#ifdef linuxSide

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include "UartException.h"
#include <CircularBuffer.h>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <DataTransfert_AllInclude.h>

#else
#include "Arduino.h"
#include <stdlib.h>
#include "../DataTransfertPackge/DataTransfert_AllInclude.h"
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
#ifdef linuxSide
    typedef data2Ard dOut;
    typedef uart2Ard pOut;
    typedef data2Rasp dIn;
    typedef uart2Rasp pIn;
#else
    typedef data2Ard dIn;
    typedef uart2Ard pIn;
    typedef data2Rasp dOut;
    typedef uart2Rasp pOut;

#endif
    enum uartState
            : char {
        waitStart, waitType, waitEnd
    };


    class UartDriver {
    public:
#ifdef linuxSide
        UartDriver(const std::string &device) noexcept(false);
        ~UartDriver();  //should be called only by singleton Parametric factory
        void uartSpeed(int vel) noexcept(false);
#else
        UartDriver(HardwareSerial *serial, long vel);
#endif
        /// Data Send
        // &pack è l'indirizzo da dove il sender si va a copiare i dati
        void packSend(uartPackType type, dOut *pack);
#ifndef linuxSide
        void serialIsr();
        void serialTrySend();
#endif
        /// Data get
        size_t Available(); // su ard uartAvailable
        pIn *getData();
#ifdef linuxSide
        pIn *getDataWait() noexcept(false);
        pIn *getDataWait(struct timespec *timeOut) noexcept(false);
#endif
        /// Data print for debug
        static void serialPackDb(uart2Ard &p);
        static void serialPackDb(uart2Rasp &p);
    private:
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

        unsigned char dato;
        size_t datoId;


        //Variabili della coda di pacchetti riconosciuti

        pIn cbReciveBuf[cbSize];
        CircularBuffer<pIn> *cbRecive;
#ifdef linuxSide
        //std::mutex readCb_mutex;  // protects gets data from concurrency
        sem_t recivedPackSem;
#endif

        //Variabili della coda di invio
#ifdef linuxSide
        //Probabilmente non servono poichè oltre la write c'e un buffer del S.O.
        std::mutex writeUart_mutex;  // protects packSend from concurrency
#else
        pOut cbSendPackBuf[cbSize];
        CircularBuffer<pOut> *cbSend;
#endif

        //Reader Thread
#ifdef linuxSide
        static void uartReader(UartDriver &d);
#endif
        //State machine to undestand pack
        void dataDiscover();
        bool typeCheck(int p);
        size_t sizeMessage(uartPackType t);
    };
}
#endif //PCLISTENUART_UARTDRIVER_H
