/*
 * uartCmd.cpp
 *
 *  Created on: 07 nov 2019
 *      Author: alfyhack
 */

#include "UartCmd.h"

namespace InternalDevice {

	UartCmd::UartCmd() {
		Cmd.begin(115200);
		Cmd.println("UartCmd Created");
		this->packAvailable = 0;
		this->potentialPackType = 0;
		this->potentialPackStart = 0;
		this->expettedEnd = 0;
		this->clearPackBuf();
		this->cbPack = new CircularBuffer<uartRecivePack>(
				(uartRecivePack *) this->cbPackBuf, packBufSize);

		this->clearSerialBuf();
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
			return this->cbPack->getPtr();
		}
		return nullptr;
	}
	
	uartRecivePack tempPack;
	void UartCmd::serialIsr() {
		reAsk: switch (this->stateUart) {
			default:
			case waitStart:
				//leggo il nuovo dato
				this->cbData->put(Cmd.read());
				//verifico che se è l'inizio di un pacchetto
				if (this->cbData->readHead() == StartCode)
					this->stateUart = waitType;
				if (Cmd.available() > 0) //se ci sono ancora dati da leggere riavvio la macchina a stati
					goto reAsk;
				break;
			case waitType:
				//ho letto uno start, se anche il type è compatibile allora probabilmente è un pacchetto
				this->potentialPackStart = this->cbData->put(Cmd.read()); //se è buono salvo l'inizio del pacchetto (type compreso), altrimenti non da fastidio
				this->potentialPackType = this->cbData->readHead();
				//se tra  mSpeedData <--> mEncoderData è un pacchetto con una dimensione
				if ((potentialPackType >= uartPackType::mSpeedData)
						&& (potentialPackType <= uartPackType::RESEND)) { //valid type
					this->stateUart = waitEnd;
					//l'end sarà alla dimensione del messaggio +1
					this->expettedEnd = 1+this->sizeMessage(
							(uartPackType) potentialPackType);
				} else
					//altrimenti torno ad aspettare nuovi dati
					this->stateUart = waitStart;

				if (Cmd.available() > 0)//se ci sono ancora dati da leggere riavvio la macchina a stati
					goto reAsk;
				break;
			case waitEnd:
				this->cbData->put(Cmd.read());
				this->expettedEnd--;			//manca ogni volta un pacchetto in meno
				if (this->expettedEnd == 0) {
					if (this->cbData->readHead() == EndCode) {
						//todo leggo i dati tra potentialPackStart e head e li salvo ne buffer dei pacchetti
						this->cbData->writeMem(
								(unsigned char *) &this->cbPackBuf[this->cbPack->getHead()],
								potentialPackStart,
								this->sizeMessage(
										(uartPackType) potentialPackType));
						//aggiorno il buffer dei pacchetti
						this->cbPack->put_externalWrite();
						this->packAvailable++;
					}else{	//ho atteso per nulla, non è la fine corretta
						//todo per ora se non trovo il pacchetto ignoro e vado al prossimo, in futuro può cercare nell'intervallo tra
						//potentialPackStart ed head se esiste un altro start e poi type e ricomincio la macchina a stati da lì
						this->stateUart = waitStart;
					}
				}


				if (Cmd.available() > 0)//se ci sono ancora dati da leggere riavvio la macchina a stati
					goto reAsk;
				break;
		}
	}
	
	void UartCmd::clearPackBuf() {
		//Pulisco la memoria del buffer dei pacchetti decodificati
		memset(this->cbPackBuf, 0, sizeof(this->cbPackBuf[0]) * packBufSize);
	}
	
	void UartCmd::clearSerialBuf() {
		//pulisco la memoria byte ricevuti
		memset(this->serialRead, 0, sizeof(this->serialRead[0]) * dataBufSize);
	}
	//        mSpeedData=1,settingBoardData, mCurrentData, mAllData, mEncoderData, sampleTimeEn , sampleTimeCur, goHomeUart ,RESEND

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
			case RESEND:
			default:
				return 0;
				break;
		}

	}

}
