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
        SPDR = 0;                        //predispongo lo 0 del primo invio
    }

    //## ELABORATION ##//
    Pack *pTemp;

    void SpiDevice::isrFunxISP() {
        if (!this->startConv) {    //raps ha appena letto 0 e inviato tipo
            pTemp = &this->sp[!this->dRecive];
            pTemp->setPackType((packType) SPDR); //mi segno tipo di comunicazione
            this->dataLoad(*pTemp);
            this->idTransf = 0;
            this->startConv = true;
            SPDR = pTemp->getSPIPACK().forRasp.buf[this->idTransf]; //preparo invio primo dato

#ifdef ISPDEBUG
            Serial.print("type=");
            Serial.print((byte) pTemp->getPackType());
            Serial.println("\t (fromRasp:mySend_PackId)");
#endif
        } else {    //salva nuovo dato
            pTemp->getSPIPACK().forArd.buf[this->idTransf] = SPDR; //salvo l'ultimo arrivo
            idTransf++;
            SPDR = pTemp->getSPIPACK().forRasp.buf[this->idTransf]; //preparo invio alla prossima trasmissione
#ifdef ISPDEBUG
            Serial.print((byte) pTemp->getSPIPACK().forArd.buf[this->idTransf-1]); 	//ricevuto
            Serial.print(":");
            Serial.print((byte) pTemp->getSPIPACK().forRasp.buf[this->idTransf-1]);		//inviato
            Serial.print("_");
            Serial.print(this->idTransf-1);
            Serial.print("  ");
#endif
        }
        if (pTemp->sizePack() == -1) { //tipo pacchetto invalido
            //reimposto i registri e variabili di stato
            SPDR = 0;
            this->startConv = false;
#ifdef ISPDEBUG
            Serial.println(" -1 !! END  !");
#endif
            return;
        }
        if (this->idTransf >= pTemp->sizePack()) { //comunicato ultimo byte
            SPDR = 0;        //ripredispongo lo 0 iniziale
            this->startConv = false;
            this->dRecive = !this->dRecive;
            this->newRecive = true;
#ifdef ISPDEBUG
            Serial.println(" END;");
#endif

        }
    }

    void SpiDevice::dataLoad(Pack &p) {
        //Pack &p = this->sp[!this->dRecive];
        memset(&p.getSPIPACK().forRasp.buf, 0, sizeof(spi2Rasp));
        switch (p.getPackType()) {
            case invalid:
                break;
            case PWMsend_EnRet:
                p.setEncoder(sFeed->captureEn());
                break;
            case PWMsend_CurRet:
                p.setCurrent(adc->getLastCycle());
                break;
            case PWMsend_AllRet:
                p.setEncoder(sFeed->captureEn());
                p.setCurrent(adc->getLastCycle());
                break;
            case SettingGet:
                p.setSetting(pack4Rasp, globSets);
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
