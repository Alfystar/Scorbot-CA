/*
 * uartcom->cpp
 *
 *  Created on: 07 nov 2019
 *      Author: alfyhack
 */

#include "UartCmd.h"

namespace InternalDevice {
	UartCmd::UartCmd(HardwareSerial *serial, long vel) {
		this->com = serial;
		com->begin(vel);
#ifdef UartDriverDebug
		Db.println("UartCmd Created");
#endif
		this->potPackType = 0;
		this->potPackStart = 0;
		this->expettedEnd = 0;

		//Buffer Circolare per i pacchetti ricevuti
		this->clearPackBuf();
#ifdef UartDriverDebug
		Db.println("cbRecive:");
#endif
		this->cbRecive = new CircularBuffer<uart2Ard>(
				(uart2Ard *) this->cbRecivePackBuf,
				sizeofArray(cbRecivePackBuf));

		//Buffer Circolare per i pacchetti da inviare (Se la dimensione satura la scrittura)
#ifdef UartDriverDebug
		Db.println("cbSend:");
#endif
		this->cbSend = new CircularBuffer<uart2Rasp>(
				(uart2Rasp *) this->cbSendPackBuf, sizeofArray(cbSendPackBuf));

		//Buffer Circolare per leggere la seriale prima che si satura
		this->clearSerialBuf();
#ifdef UartDriverDebug
		Db.println("cbData:");
#endif
		this->cbByteRecive = new CircularBuffer<unsigned char>(
				(unsigned char *) this->reciveBuf,
				sizeofArray(reciveBuf));

	}
	
	unsigned char UartCmd::uartAvailable() {
		//return this->packAvailable;
		return this->cbRecive->size();
	}

	uart2Ard *UartCmd::getLastRecive() {
		if (uartAvailable() > 0) {
			return this->cbRecive->getPtr();
		}
		return nullptr;
	}

	uart2Ard tempPack;
	void UartCmd::serialIsr() {
		//carico il buffer dei dati da leggere
		while (com->available())
			this->cbByteRecive->put(com->read());
		//analizzo i dati
		this->dataDiscover();
		return;
	}

	unsigned char dato;
	size_t datoId;
	void UartCmd::dataDiscover() {
#ifdef UartDriverDebug
#ifdef linuxSide

		std::cout << "dataDiscover:\n";
#else
		Db.println("dataDiscover:");
#endif
#endif
		while (!cbByteRecive->empty()) {
			datoId = cbByteRecive->getTail();
			dato = cbByteRecive->get();
#ifdef UartDriverDebug
#ifdef linuxSide
			std::cout << "\tdatoId = " << datoId << "  dato = " << (int) dato;
#else
			Db.print("\tdatoId = ");
			Db.print(datoId);
			Db.print("  dato = ");
			Db.println((int) dato);
#endif
#endif
			switch (this->stateUart) {
				default:
				case waitStart:
					//verifico che se è l'inizio di un pacchetto
					if (dato == StartCode) {
#ifdef UartDriverDebug
#ifdef linuxSide
						std::cout <<" StartCode Found =D ";
#else
						Db.println(" StartCode Found =D ");
#endif
#endif
						this->stateUart = waitType;
					}
				break;
				case waitType:
					//ho letto uno start, se anche il type è compatibile allora probabilmente è un pacchetto
					this->potPackStart = datoId; //se è buono salvo l'inizio del pacchetto (type compreso), altrimenti non da fastidio
					this->potPackType = dato;
					//se tra  mSpeedData <--> mEncoderData è un pacchetto con una dimensione
					if ((potPackType >= uartPackType::mSpeedData)
							&& (potPackType <= uartPackType::RESEND)) { //valid type
						this->stateUart = waitEnd;
#ifdef UartDriverDebug
#ifdef linuxSide
						std::cout <<" Valid Type Found =D ";
#else
						Db.println(" Valid Type Found =D ");
#endif
#endif	//l'end sarà alla dimensione del messaggio +1
						this->expettedEnd = 1
								+ this->sizeMessage((uartPackType) potPackType);
					} else { //altrimenti torno ad aspettare nuovi dati
#ifdef UartDriverDebug
#ifdef linuxSide

						std::cout <<" Not valid Type =( ";
#else
						Db.println(" Not valid Type =( ");
#endif
#endif
						this->stateUart = waitStart;
					}
				break;
				case waitEnd:
					this->expettedEnd--; //manca ogni volta un pacchetto in meno
					if (this->expettedEnd == 0) {
						if (dato == EndCode) {

							//Aggiungo esternamente a cbRecive il pacchetto ricevuto
							cbByteRecive->writeMemOut((unsigned char *) this->cbRecive->getHeadPtr(), potPackStart,
							                                                      1+this->sizeMessage((uartPackType) potPackType)); //type+mexsize
#ifdef UartDriverDebug
#ifdef linuxSide

							std::cout <<" EndCode Found =D ";
							std::cout << "\n";
							this->serialPackDb(*this->cbRecive->getHeadPtr());
#else
							Db.println(" EndCode Found =D ");
							this->serialPackDb(*this->cbRecive->getHeadPtr());
#endif
#endif		//aggiorno il buffer dei pacchetti aggiungendone 1
							this->cbRecive->put_externalWrite();
#ifdef linuxSide
							if(!cbRecive->empty())
							sem_post(&recivedPackSem);
#endif
						} else {   //ho atteso per nulla, non è la fine corretta
#ifdef UartDriverDebug
#ifdef linuxSide
							std::cout <<" EndCode miss =( ";
#else
							Db.println(" EndCode miss =( ");
#endif
#endif		//todo per ora se non trovo il pacchetto ignoro e vado al prossimo, in futuro può cercare nell'intervallo tra
							//potentialPackStart ed head se esiste un altro start e poi type e ricomincio la macchina a stati da lì
						}
						this->stateUart = waitStart;
					}
				break;
			}	                            //End switch
#ifdef UartDriverDebug
#ifdef linuxSide

			std::cout <<" stateUart = " << this->stateUart << "\n";
#else
#endif
#endif
		}	                            //End while
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
		memset(this->reciveBuf, 0, sizeof(this->reciveBuf[0]) * dataBufSize);
	}

	void UartCmd::packSend(uartPackType type, data2Rasp *pack) {
//lavoro a mano per accelerare il salvataggio, altrimenti usavo "size_t put(T* item, size_t len);"
//uartSendPack *p = this->cbSend->getHeadPtr();
		uart2Rasp *p = this->cbSend->getHeadPtr();
//&this->cbSendPackBuf[this->cbSend->getHead()];
		this->cbSend->put_externalWrite();
		p->type = type;
		memcpy((void *) p->pack.buf, pack, this->sizeMessage(type));
	}

	uart2Rasp *sTemp = nullptr;
	char len = 0;

	void UartCmd::serialTrySend() {
		if (this->cbSend->empty()) {
			return;
		}
		sTemp = this->cbSend->getTailPtr();
		len = this->sizeMessage(sTemp->type);

		if (com->availableForWrite() > (len + 3))   //len+Type+StartCode+EndCode
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
		} else { //non c'era abbastanza spazio, la prossima volta riparto dallo stesso punto
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

	void UartCmd::serialPackDb(uart2Ard &p) {
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
			case settingAsk:
				Db.print("Data Recive: settingAsk");
				break;
			case goHomeUart:
				Db.print("Data Recive: goHomeUart");
				break;
			default:
				Db.print("Dentro Default!! type=");
				Db.println((int) p.type);
			break;
		}
	}

	void UartCmd::serialPackDb(uart2Rasp &p) {
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
				Db.println((int)p.type);
			break;
		}
	}

}

