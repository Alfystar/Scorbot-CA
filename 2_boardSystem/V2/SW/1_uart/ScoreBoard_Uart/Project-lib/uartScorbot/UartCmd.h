/*
 * uartCmd.h
 *
 *  Created on: 07 nov 2019
 *      Author: alfyhack
 */

#ifndef PROJECT_LIB_UARTSCORBOT_UARTCMD_H_
#define PROJECT_LIB_UARTSCORBOT_UARTCMD_H_

#include "Arduino.h"
#include <stdlib.h>
#include "../globalDef.h"
#include "../circularBuffer/CircularBuffer.h"

#define UartDb 1
#define CMD_Send_PRINT 1

enum uartCode
        : unsigned char {
    StartCode = 192, EndCode = 168
};

namespace InternalDevice {
	using namespace DataPrimitive;
	using namespace DataManipolation;
    //todo spostare questi due in DataPrimitive
    typedef struct uartRecivePack_ {
        uartPackType type;
        data2Ard pack;
    } uartRecivePack;

    typedef struct uartSendPack_ {
        uartPackType type;
        data2Rasp pack;
    } uartSendPack;

#define packBufSize 8
#define dataBufSize 4*sizeof(uartRecivePack)
	enum uartState
            : char {
        waitStart, waitType, waitEnd
	};

	class UartCmd {
		public:
        UartCmd(HardwareSerial *serial);
			unsigned char uartAvailable();
			uartRecivePack* getLastRecive();

        void
        packSend(uartPackType type, data2Rasp *pack); // &pack è l'indirizzo da dove il sender si va a copiare i dati

			void serialIsr();

        void serialTrySend();

        static void serialPackDb(uartRecivePack &p);
        static void serialPackDb(uartSendPack &p);

		private:
        HardwareSerial *com;

        //Variabili per la ricezione dei dati byte
        char serialRead[dataBufSize];
			CircularBuffer<unsigned char> *cbData;

			uartState stateUart = waitStart;
        char potPackStart;
        char potPackType;
			char expettedEnd;

        //Variabili per la gestione dei pacchetti ricevuti
        uartRecivePack cbRecivePackBuf[packBufSize];
        CircularBuffer<uartRecivePack> *cbRecive;
			unsigned char packAvailable;

        //Variabili per la gestione dei pacchetti da inviare
        uartSendPack cbSendPackBuf[packBufSize];
        CircularBuffer<uartSendPack> *cbSend;


			void clearPackBuf();
			void clearSerialBuf();
			char sizeMessage(uartPackType t);

	};

}

#endif /* PROJECT_LIB_UARTSCORBOT_UARTCMD_H_ */
