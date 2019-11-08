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

enum uartCode
	: unsigned char {StartCode = 192, EndCode = 168
};

namespace InternalDevice {
	using namespace DataPrimitive;
	using namespace DataManipolation;

	typedef struct uartRecivePack_ {
			uartPackType type;
			data2Ard pack;
	} uartRecivePack;

#define packBufSize 8
#define dataBufSize 4*sizeof(uartRecivePack)
	enum uartState
		: char {waitStart, waitType, waitEnd
	};

	class UartCmd {
		public:
			UartCmd();
			unsigned char uartAvailable();
			uartRecivePack* getLastRecive();

			void serialIsr();

		private:
			char serialRead[dataBufSize];
			CircularBuffer<unsigned char> *cbData;

			uartState stateUart = waitStart;
			char potentialPackStart;
			char potentialPackType;
			char expettedEnd;

			uartRecivePack cbPackBuf[packBufSize];
			CircularBuffer<uartRecivePack> *cbPack;
			unsigned char packAvailable;

			void clearPackBuf();
			void clearSerialBuf();
			char sizeMessage(uartPackType t);

	};

}

#endif /* PROJECT_LIB_UARTSCORBOT_UARTCMD_H_ */
