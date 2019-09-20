#include "Project-lib/globalDef.h"
#include "Project-lib/Motor/DCdriver.h"

extern DCdriverLimit *mot[nMot];
#define timeOut 2000

void excutePack(Pack &p) {
    switch (p.getPackType()) {
        case invalid: {
            //notting to do
        }
            break;
        case PWMsend_EnRet:
        case PWMsend_CurRet:
        case PWMsend_AllRet: {
            mSpeed &vel = p.getPwm();
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
        case SettingSet: {
            settingsBoard &s = p.getSetting(pack4Ard);
            memorySave(s);
            setMotFreq(s.freq);
            adc->setDiffRead(s.diff);
            adc->setVRefSource(s.adcVref);
        }
            break;
        case goHome:
            home();
            break;
        case SettingGet:
        default: {
            //notting to do
        }
            break;
    }
}
