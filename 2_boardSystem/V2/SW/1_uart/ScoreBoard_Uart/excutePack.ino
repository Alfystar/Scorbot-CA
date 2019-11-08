#include "Project-lib/globalDef.h"
#include "Project-lib/Motor/DCdriver.h"

extern DCdriverLimit *mot[nMot];
#define timeOut 2000

extern unsigned long nextEnSend,nextCurSend;
extern unsigned short enP, curP;

void excutePack(uartRecivePack &p) {
	switch (p.type) {
		case mSpeedData:
			mSpeed &vel = p.pack.up.speed;
			for (byte i = 0; i < nMot; i++) {
				switch (vel[Mot1 + i]) {
					case freeRun:
						mot[Mot1 + i]->freeRun();
						break;
					case hardStop:
						mot[Mot1 + i]->hard_stop(timeOut);
						break;
					case softStop:
						mot[Mot1 + i]->soft_stop(timeOut);
						break;
					case ignore:
						break;
					default:
						mot[Mot1 + i]->drive_motor(vel[Mot1 + i], timeOut);
						break;
				}
			}
			break;
		case settingBoardData:
			settingsBoard &s = p.pack.up.prop;
			memorySave(s);
			setMotFreq(s.freq);
			adc->setDiffRead(s.diff);
			adc->setVRefSource(s.adcVref);
			break;
		case sampleTimeEn:
			enP=p.pack.up.sampleEn;
			break;
		case sampleTimeCur:
			curP=p.pack.up.sampleCur;
			break;
		case goHomeUart:
			home();
			break;
		case RESEND:
			//todo inviare lastPack
			break;
		default:
			break;
	}
}


void dataSend()
{
	//To avow the overflow problem this is simple solution
	//https://www.norwegiancreations.com/2018/10/arduino-tutorial-avoiding-the-overflow-issue-when-using-millis-and-micros/
	unsigned long time = micros();
	if(time-nextEnSend>enP && time-nextCurSend>curP)
	{
		//todo send data as mAll to uart
		nextEnSend+=enP;
		nextCurSend+=curP;
	}else{
		if(time-nextEnSend>enP){
			//todo send data to uart
			nextEnSend+=enP;
		}

		if(time-nextCurSend>curP){
			//todo send data to uart
			nextCurSend+=curP;
		}
	}
}
