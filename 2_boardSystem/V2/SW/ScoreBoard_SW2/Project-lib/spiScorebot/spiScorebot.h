#ifndef SPISCOREBOT_H
#define SPISCOREBOT_H
#include "Arduino.h"
#include <stdlib.h>
#include "../globalDef.h"


namespace InternalDevice{
	using namespace spiPack;
	class SpiDevice{
	public:
		static SpiDevice& getIstance();
		//## EXECUTION ##//
		void isrFunxISP();
		void dataLoad();
		//## GET VALUE ##//
		byte spiAvailable();
		Pack& getLastRecive();

	private:
		Pack sp[2];
		volatile byte idTransf, startConv, dRecive, newRecive;
		static SpiDevice *instance;
		//## HARDWARE ##//
		SpiDevice();
	};
}//END namespace SpiLib_Ard

#ifndef __IN_ECLIPSE__
#include "spiScorebot.cpp"
#endif

#endif
