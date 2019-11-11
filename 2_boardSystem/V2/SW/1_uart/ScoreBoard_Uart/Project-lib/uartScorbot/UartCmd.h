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

namespace InternalDevice {
	using namespace DataPrimitive;
	using namespace DataManipolation;


#define packBufSize 8
#define dataBufSize 4*sizeof(uart2Ard)
	enum uartState
            : char {
        waitStart, waitType, waitEnd
	};

	class UartCmd {
		public:
        UartCmd(HardwareSerial *serial);
			unsigned char uartAvailable();
        uart2Ard *getLastRecive();

        void
        packSend(uartPackType type, data2Rasp *pack); // &pack è l'indirizzo da dove il sender si va a copiare i dati

			void serialIsr();

        void serialTrySend();

        static void serialPackDb(uart2Ard &p);
        static void serialPackDb(uart2Rasp &p);

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
        uart2Ard cbRecivePackBuf[packBufSize];
        CircularBuffer<uart2Ard> *cbRecive;
			unsigned char packAvailable;

        //Variabili per la gestione dei pacchetti da inviare
        uart2Rasp cbSendPackBuf[packBufSize];
        CircularBuffer<uart2Rasp> *cbSend;


			void clearPackBuf();
			void clearSerialBuf();
			char sizeMessage(uartPackType t);

	};

}

#endif /* PROJECT_LIB_UARTSCORBOT_UARTCMD_H_ */
