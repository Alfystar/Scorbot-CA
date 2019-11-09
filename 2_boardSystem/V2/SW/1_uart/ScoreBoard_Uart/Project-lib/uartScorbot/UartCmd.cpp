/*
 * uartcom->cpp
 *
 *  Created on: 07 nov 2019
 *      Author: alfyhack
 */

#include "UartCmd.h"

namespace InternalDevice {
    UartCmd::UartCmd(HardwareSerial *serial) {
        this->com = serial;
        com->begin(115200);
#ifdef UartDb
        Db.println("UartCmd Created");
#endif
		this->packAvailable = 0;
        this->potPackType = 0;
        this->potPackStart = 0;
		this->expettedEnd = 0;

        //Buffer Circolare per i pacchetti ricevuti
		this->clearPackBuf();
        Db.println("cbRecive:");
        this->cbRecive = new CircularBuffer<uartRecivePack>(
                (uartRecivePack *) this->cbRecivePackBuf, packBufSize);

        //Buffer Circolare per i pacchetti da inviare (Se la dimensione satura la scrittura)
        Db.println("cbSend:");
        this->cbSend = new CircularBuffer<uartSendPack>(
                (uartSendPack *) this->cbSendPackBuf, packBufSize);

        //Buffer Circolare per leggere la seriale prima che si satura
		this->clearSerialBuf();
        Db.println("cbData:");
		this->cbData = new CircularBuffer<unsigned char>(
				(unsigned char *) this->serialRead,
				dataBufSize);

	}
	
	unsigned char UartCmd::uartAvailable() {
		return this->packAvailable;
	}
	
	uartRecivePack* UartCmd::getLastRecive() {
		if (uartAvailable() > 0) {
			this->packAvailable--;
            return this->cbRecive->getPtr();
		}
		return nullptr;
	}
	
	uartRecivePack tempPack;
	void UartCmd::serialIsr() {
		reAsk: switch (this->stateUart) {
			default:
			case waitStart:
				//leggo il nuovo dato
                this->cbData->put(com->read());
				//verifico che se è l'inizio di un pacchetto
				if (this->cbData->readHead() == StartCode)
					this->stateUart = waitType;
            if (com->available() > 0) //se ci sono ancora dati da leggere riavvio la macchina a stati
					goto reAsk;
				break;
			case waitType:
				//ho letto uno start, se anche il type è compatibile allora probabilmente è un pacchetto
                this->potPackStart = this->cbData->put(
                        com->read()); //se è buono salvo l'inizio del pacchetto (type compreso), altrimenti non da fastidio
            this->potPackType = this->cbData->readHead();
				//se tra  mSpeedData <--> mEncoderData è un pacchetto con una dimensione
            if ((potPackType >= uartPackType::mSpeedData)
                && (potPackType <= uartPackType::RESEND)) { //valid type
					this->stateUart = waitEnd;
					//l'end sarà alla dimensione del messaggio +1
                this->expettedEnd = 1
                                    + this->sizeMessage(
                        (uartPackType) potPackType);
				} else
					//altrimenti torno ad aspettare nuovi dati
					this->stateUart = waitStart;
            if (com->available() > 0) //se ci sono ancora dati da leggere riavvio la macchina a stati
					goto reAsk;
				break;
			case waitEnd:
                this->cbData->put(com->read());
            this->expettedEnd--;    //manca ogni volta un pacchetto in meno
				if (this->expettedEnd == 0) {
					if (this->cbData->readHead() == EndCode) {
                        //Aggiungo esternamente a cbRecive il pacchetto ricevuto
                        this->cbData->writeMemOut(
                                (unsigned char *) this->cbRecive->getHeadPtr(),
                                potPackStart,
                                this->sizeMessage((uartPackType) potPackType));
						//aggiorno il buffer dei pacchetti
                        this->cbRecive->put_externalWrite();
						this->packAvailable++;
                    } else {    //ho atteso per nulla, non è la fine corretta
						//todo per ora se non trovo il pacchetto ignoro e vado al prossimo, in futuro può cercare nell'intervallo tra
						//potentialPackStart ed head se esiste un altro start e poi type e ricomincio la macchina a stati da lì
						this->stateUart = waitStart;
					}
				}
            if (com->available() > 0)//se ci sono ancora dati da leggere riavvio la macchina a stati
					goto reAsk;
				break;
		}
	}
	
	void UartCmd::clearPackBuf() {
		//Pulisco la memoria del buffer dei pacchetti decodificati
        memset(this->cbRecivePackBuf, 0,
               sizeof(this->cbRecivePackBuf[0]) * packBufSize);
        memset(this->cbSendPackBuf, 0,
               sizeof(this->cbSendPackBuf[0]) * packBufSize);
	}
	
	void UartCmd::clearSerialBuf() {
		//pulisco la memoria byte ricevuti
		memset(this->serialRead, 0, sizeof(this->serialRead[0]) * dataBufSize);
	}

    void UartCmd::packSend(uartPackType type, data2Rasp *pack) {
        //lavoro a mano per accelerare il salvataggio, altrimenti usavo "size_t put(T* item, size_t len);"
        //uartSendPack *p = this->cbSend->getHeadPtr();
        uartSendPack *p = &this->cbSendPackBuf[this->cbSend->getHead()];
        this->cbSend->put_externalWrite();
        p->type = type;
        memcpy((void *) p->pack.buf, pack, this->sizeMessage(type));
    }

    uartSendPack *sTemp = nullptr;
    char len = 0;

    void UartCmd::serialTrySend() {
        if (this->cbSend->empty()) {
            return;
        }
        sTemp = this->cbSend->getTailPtr();
        len = this->sizeMessage(sTemp->type);
        if (com->availableForWrite() > (len + 3))    //len+Type+StartCode+EndCode
        {
            //aggiorno la lettura della coda
            this->cbSend->get_externalRead();
#ifdef CMD_Send_PRINT
            UartCmd::serialPackDb(*sTemp);
#endif
            com->write((unsigned char) StartCode);
            com->write((unsigned char) sTemp->type);
            for (char i = 0; i < len; i++)
                com->write((unsigned char) sTemp->pack.buf[i]);
            com->write((unsigned char) EndCode);
        } else {    //non c'era abbastanza spazio, la prossima volta riparto dallo stesso punto
            return;
        }

    }

    //mSpeedData=1,settingBoardData, mCurrentData, mAllData, mEncoderData, sampleTimeEn , sampleTimeCur, goHomeUart, settingAsk, RESEND
    char UartCmd::sizeMessage(uartPackType t) {
        switch (t) {
            case mSpeedData:
                return sizeof(mSpeed);
            case settingBoardData:
                return sizeof(settingsBoard);
            case mCurrentData:
                return sizeof(mCurrent);
            case mAllData:
                return sizeof(mAll);
            case mEncoderData:
                return sizeof(mEncoder);
            case sampleTimeEn:
            case sampleTimeCur:
                return sizeof(short);
            case goHomeUart:
            case settingAsk:
            case RESEND:
            default:
                return 0;
                break;
        }

    }

    void UartCmd::serialPackDb(uartRecivePack &p) {
        Db.print("serialPackDb(uartRecivePack):");
        Db.println((unsigned int) &p);
        switch (p.type) {
            case mSpeedData:
                SpeedMot::printSpeed(p.pack.up.speed);
                break;
            case settingBoardData:
                SettingBoard_C::printSetting(p.pack.up.prop);
                break;
            case sampleTimeEn:
                Db.print("Data Recive: sampleTimeEn:");
                Db.println(p.pack.up.sampleEn);
                break;
            case sampleTimeCur:
                Db.print("Data Recive: sampleTimeCur:");
                Db.println(p.pack.up.sampleCur);
                break;
            default:
                Db.print("Dentro Default!! type=");
                Db.println((char) p.type);
                break;
        }
    }

    void UartCmd::serialPackDb(uartSendPack &p) {
        Db.print("serialPackDb(uartSendPack):");
        Db.println((unsigned int) &p);
        switch (p.type) {
            case mEncoderData:
                EncoderMot::printEncoder(p.pack.up.en);
                break;
            case mCurrentData:
                CurrentMot::printCurrent(p.pack.up.cur);
                break;
            case mAllData:
                AllSensor::printAll(p.pack.up.sens);
                break;
            case settingBoardData:
                SettingBoard_C::printSetting(p.pack.up.prop);
                break;
            default:
                Db.print("Dentro Default!! type=");
                Db.println(p.type);
                break;
        }
    }

}

