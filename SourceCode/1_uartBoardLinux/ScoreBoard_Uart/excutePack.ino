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
            enP = p.pack.up.sampleEn;
            break;
        case sampleTimeCur:
            curP = p.pack.up.sampleCur;
            break;
        case goHomeUart:
            home();
            break;
        case settingAsk:
            uart->packSend(settingBoardData, (data2Linux *) &globSets);
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
extern uint32_t enP, curP;

void initDataSend() {
    sAllSend = new AllSensor(mAllTmp);
    nextEnSend = millis();    //dall'accenzione almeno 5 secondi di pausa
    nextCurSend = nextEnSend;
}

mEncoder enTest = {165, 2, 3, 4, 5, 6};
mCurrent curTest = {12, 23, 34, 45, 65, 16};
unsigned long time;

void dataSend() {
    time = micros();

    //To avow the overflow problem this is simple solution
    //https://www.norwegiancreations.com/2018/10/arduino-tutorial-avoiding-the-overflow-issue-when-using-millis-and-micros/
    if (time - nextEnSend > enP && time - nextCurSend > curP) {
        //digitalWrite(31,!digitalRead(31));
        //digitalWrite(30,!digitalRead(30));
        //sAllSend->copyEn(sFeed->captureEn());
        //sAllSend->copyCur(adc->getLastCycle());
        sAllSend->copyEn(enTest);
        sAllSend->copyCur(curTest);
        uart->packSend(mAllData, (data2Linux *) &sAllSend->getSens());
        nextEnSend += enP;
        nextCurSend += curP;
        return;
    }
    if (time - nextEnSend > enP) {
        //digitalWrite(31,!digitalRead(31));
        //sAllSend->copyEn(sFeed->captureEn());
        sAllSend->copyEn(enTest);
        uart->packSend(mEncoderData, (data2Linux *) &sAllSend->getEn());
        nextEnSend += enP;
        return;
    }
    if (time - nextCurSend > curP) {
        //digitalWrite(30,!digitalRead(30));
        //sAllSend->copyCur(adc->getLastCycle());
        sAllSend->copyCur(curTest);
        uart->packSend(mCurrentData, (data2Linux *) &sAllSend->getCurrent());
        nextCurSend += curP;
        return;
    }

}
