#include "spiScorebot.h"

namespace InternalDevice {
    //Static variable initialize
    //SpiDevice* SpiDevice::instance = NULL;
    /*
    SpiDevice& SpiDevice::getIstance() {
        if (SpiDevice::instance == nullptr)
            SpiDevice::instance = new SpiDevice();
        return *SpiDevice::instance;
    }
    */
    SpiDevice::SpiDevice() {
        pinMode(MISO, OUTPUT);
        this->sp[0].clearPack();
        this->sp[1].clearPack();
        this->idTransf = 0;
        this->startConv = 0;
        this->newRecive = 0;
        this->dRecive = 0;
        SPCR = (1 << SPIE) | (1 << SPE);    //attiva spi e abilita interrupt
        SPDR = 5;                        //predispongo lo 0 del primo invio
    }

    //## ELABORATION ##//
    void SpiDevice::isrFunxISP() {
        if (!this->startConv) {    //raps ha appena letto 0 e inviato tipo
            this->sp[!this->dRecive].setPackType((packType) SPDR); //mi segno tipo di comunicazione
            this->dataLoad();
            this->idTransf = 0;
            this->startConv = true;
            SPDR =
                    this->sp[!this->dRecive].getSPIPACK().forRasp.buf[this->idTransf]; //preparo invio primo dato

#ifdef ISPDEBUG
            Serial.print("type=");
            Serial.print((byte) spiPackp[!this->dRecive].type);
            Serial.print("-");
            Serial.print("S");
            Serial.print(":");
            Serial.print((byte) spiPackp[!this->dRecive].outPack.buffOut[this->idTransf]);
            Serial.print("_");
            Serial.print(this->idTransf);
            Serial.print("  ");
#endif
        } else {    //salva nuovo dato
            this->sp[!this->dRecive].getSPIPACK().forArd.buf[this->idTransf] =
                    SPDR; //salvo l'ultimo invio
            idTransf++;
            SPDR =
                    this->sp[!this->dRecive].getSPIPACK().forRasp.buf[this->idTransf]; //preparo invio il mio dato
#ifdef ISPDEBUG
            Serial.print((byte) spiPackp[!this->dRecive].inPack.buffIn[this->idTransf - 1]);
            Serial.print(":");
            Serial.print((byte) spiPackp[!this->dRecive].outPack.buffOut[this->idTransf]);
            Serial.print("_");
            Serial.print(this->idTransf);
            Serial.print("  ");
#endif
        }
        if (this->sp[!this->dRecive].sizePack() == -1) {
            SPDR = 0;        //ripredispongo lo 0 iniziale
            this->startConv = false;
#ifdef ISPDEBUG
            Serial.println(" -1 !! END  !");
#endif
            return;
        }
        if (this->idTransf >= this->sp[!this->dRecive].sizePack()) { //comunicazione all'ultimo byte
            SPDR = 0;        //ripredispongo lo 0 iniziale
            this->startConv = false;
            this->dRecive = !this->dRecive;
            this->newRecive = true;
#ifdef ISPDEBUG
            Serial.println(" END;");
#endif

        }
    }

    void SpiDevice::dataLoad() {
        Pack &p = this->sp[!this->dRecive];
        memset(&p.getSPIPACK().forRasp, 0, sizeof(spi2Rasp));
        switch (p.getPackType()) {
            case invalid:
                break;
            case PWMsend_EnRet:
                p.setEncoder(sFeed->captureEn());
                break;
            case PWMsend_CurRet:
                p.setCurrent(adc->getLastCicle());
                break;
            case PWMsend_AllRet:
                p.setEncoder(sFeed->captureEn());
                p.setCurrent(adc->getLastCicle());
                break;
            case SettingGet:
                p.setSetting(globSets, pack4Rasp);
                break;
            case SettingSet:
                break;
            case goHome:
                break;
            default:
                break;
        }
    }

    //## GET VALUE ##//
    byte SpiDevice::spiAvailable() {
        if (this->newRecive != 0) {
            this->newRecive = 0;
            return 1;
        } else
            return 0;
    }

    Pack &SpiDevice::getLastRecive() {
        return this->sp[this->dRecive];
    }
}    //END namespace SpiLib_Ard
