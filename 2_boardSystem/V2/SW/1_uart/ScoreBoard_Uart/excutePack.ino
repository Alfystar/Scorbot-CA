#include "Project-lib/globalDef.h"
#include "Project-lib/Motor/DCdriver.h"

extern DCdriverLimit *mot[nMot];
#define timeOut 2000

void excutePack(uart2Ard &p) {
	switch (p.type) {
		case mSpeedData: {
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
        }
            break;
		case settingBoardData: {
            settingsBoard &s = p.pack.up.prop;
            memorySave(s);
            setMotFreq(s.freq);
            adc->setDiffRead(s.diff);
            adc->setVRefSource(s.adcVref);
            break;
        }
		case sampleTimeEn:
			enP=p.pack.up.sampleEn;
			break;
		case sampleTimeCur:
			curP=p.pack.up.sampleCur;
			break;
		case goHomeUart:
			home();
			break;
        case settingAsk:
            uart->packSend(settingBoardData, (data2Rasp *) &globSets);
            break;
		case RESEND:
			//todo inviare lastPack
			break;
		default:
			break;
	}
}


mAll mAllTmp;
AllSensor *sAllSend;
extern unsigned long nextEnSend, nextCurSend;
extern unsigned long enP, curP;

void initDataSend() {
    sAllSend = new AllSensor(mAllTmp);
    nextEnSend = millis();    //dall'accenzione almeno 5 secondi di pausa
    nextCurSend = nextEnSend;

    //test packs:
    uart->packSend(mEncoderData, (data2Rasp *) &sAllSend->getEn());
    uart->packSend(mAllData, (data2Rasp *) &sAllSend->getSens());
    uart->packSend(mCurrentData, (data2Rasp *) &sAllSend->getCurrent());
    uart->packSend(mEncoderData, (data2Rasp *) &sAllSend->getEn());
    uart->packSend(mAllData, (data2Rasp *) &sAllSend->getSens());
    uart->packSend(mCurrentData, (data2Rasp *) &sAllSend->getCurrent());
    uart->packSend(mEncoderData, (data2Rasp *) &sAllSend->getEn());
    uart->packSend(mAllData, (data2Rasp *) &sAllSend->getSens());
    //extra carico di test
    uart->packSend(mEncoderData, (data2Rasp *) &sAllSend->getEn());
    uart->packSend(mAllData, (data2Rasp *) &sAllSend->getSens());
    uart->packSend(mCurrentData, (data2Rasp *) &sAllSend->getCurrent());
    uart->packSend(mEncoderData, (data2Rasp *) &sAllSend->getEn());
    uart->packSend(mAllData, (data2Rasp *) &sAllSend->getSens());
    uart->packSend(mCurrentData, (data2Rasp *) &sAllSend->getCurrent());
    uart->packSend(mEncoderData, (data2Rasp *) &sAllSend->getEn());
    uart->packSend(mAllData, (data2Rasp *) &sAllSend->getSens());

}

unsigned long time;
void dataSend()
{
    time = micros();

	//To avow the overflow problem this is simple solution
	//https://www.norwegiancreations.com/2018/10/arduino-tutorial-avoiding-the-overflow-issue-when-using-millis-and-micros/
	if(time-nextEnSend>enP && time-nextCurSend>curP)
	{
        sAllSend->copyEn(sFeed->captureEn());
        sAllSend->copyCur(adc->getLastCycle());
        uart->packSend(mAllData, (data2Rasp *) &sAllSend->getSens());
		nextEnSend+=enP;
		nextCurSend+=curP;
        return;
	}else{
		if(time-nextEnSend>enP){
            sAllSend->copyEn(sFeed->captureEn());
            uart->packSend(mEncoderData, (data2Rasp *) &sAllSend->getEn());
			nextEnSend+=enP;
            return;
		}

		if(time-nextCurSend>curP){
            sAllSend->copyEn(sFeed->captureEn());
            uart->packSend(mCurrentData, (data2Rasp *) &sAllSend->getCurrent());
			nextCurSend+=curP;
            return;
		}
	}
}
