//
// Created by alfyhack on 03/09/19.
//
#include "SpiPack.h"
//#define PackDebug 1 //attiva/disattiva compilazione del codice per printare dati di debug della classe Pack

namespace spiPack {
	Pack::Pack() {
		this->clearPack();
#ifdef PackDebug
#ifdef ScorboarFirmware
		Serial.println("Data size:");
		Serial.print("packType size :");
		Serial.println(sizeof(packType));
		Serial.print("mEncoder size :");
		Serial.println(sizeof(mEncoder));
		Serial.print("mCurrent size :");
		Serial.println(sizeof(mCurrent));
		Serial.print("mAll size :");
		Serial.println(sizeof(mAll));
		Serial.print("settingsBoard size :");
		Serial.println(sizeof(settingsBoard));
		Serial.print("adcRef size :");
		Serial.println(sizeof(adcRef));
		Serial.print("bool(diff read) size :");
		Serial.println(sizeof(bool));
		Serial.print("pwmFreq size :");
		Serial.println(sizeof(pwmFreq));
		Serial.println();
#else
		printf("Data size:\n");
		printf("packType size : %d\n",sizeof(packType));
		printf("mEncoder size : %d\n",sizeof(mEncoder));
		printf("mCurrent size : %d\n",sizeof(mCurrent));
		printf("mAll size : %d\n",sizeof(mAll));
		printf("settingsBoard size : %d\n",sizeof(settingsBoard));
		printf("adcRef size : %d\n",sizeof(adcRef));
		printf("bool(diff read) size : %d\n",sizeof(bool));
		printf("pwmFreq size : %d\n\n",sizeof(pwmFreq));
#endif //#ifdef ScorboarFirmware

#endif //#ifdef PackDebug
	}

	Pack::Pack(Pack &p) {
		Pack(p.data);
	}

	Pack::Pack(SPIPACK &s) {
		memmove(&this->data, (const void *) &s, sizeof(SPIPACK));
	}

	Pack::~Pack() {
		//for now nothings to delete
	}

	void Pack::clearPack() {
		memset(&this->data, 0, sizeof(SPIPACK));
	}

	void Pack::printPack() {
#ifdef ScorboarFirmware
		switch (this->getPackType()) {
			case PWMsend_EnRet:
			case PWMsend_CurRet:
			case PWMsend_AllRet:
			{
				Serial.flush();
				Serial.println("Master Ask 'PWMsend_EnRet || PWMsend_CurRet || PWMsend_AllRet', Parameter:");
				/*Recive*/
				for (byte i = 0; i < nMot; i++) {
					Serial.print("\tSpeed[Mot");
					Serial.print(i+1);
					Serial.print("]:");
					Serial.println(this->getPwm()[Mot1 + i]);
				}
				/*Send*/
				if(this->getPackType()==PWMsend_EnRet || this->getPackType()==PWMsend_AllRet)
				{
					Serial.flush();
					Serial.println("Sended Encoder Step:");
					for (byte i = 0; i < nMot; i++) {
						Serial.print("\tencoder[Mot");
						Serial.print(i+1);
						Serial.print("]:");
						Serial.println(this->getEncoder()[Mot1 + i]);
					}
				}
				if(this->getPackType()==PWMsend_CurRet || this->getPackType()==PWMsend_AllRet)
				{
					Serial.flush();
					Serial.println("Sended Current Value:");
					for (byte i = 0; i < nMot; i++) {
						Serial.print("\tcurrent[Mot");
						Serial.print(i + 1);
						Serial.print("]:");
						Serial.println(this->getCurrent()[Mot1 + i]);
					}
				}
			}
			break;
			case SettingSet:
			case SettingGet:
			{
				if(this->getPackType()==SettingSet)
				{
					Serial.flush();
					Serial.println("Master Ask 'SettingSet':");
					Serial.println("Recive new Settings:");
				}
				else
				{
					Serial.flush();
					Serial.println("Master Ask 'SettingGet':");
					Serial.println("Sending my Settings:");
				}

				this->printSetting(this->getSetting());

			}
			break;
			case goHome:
				Serial.flush();
				Serial.println("Master Ask 'goHome', Parameter:\n");
				//Recive//
				Serial.print("\tNotting\n");
				//Send//
				Serial.print("\tNotting\n");
				break;
			case invalid:
			default:
				Serial.println("Pack type is invalid, should be an error on Connection or inside the Pack compiling.");
				break;
		}
#else //Start Rasp print pack
		switch (this->data.type) {
			case PWMsend_EnRet:
			case PWMsend_CurRet:
			case PWMsend_AllRet:

				printf("PackType: 'PWMsend_EnRet || PWMsend_CurRet || PWMsend_AllRet', Parameter:\n");
				/*Recive*/
				for (char i = 0; i < nMot; i++) {
					printf("%d)%hd\t", i + 1, this->getPwm()[Mot1 + i]);
				}

				/*Send*/
				if(this->getPackType()==PWMsend_EnRet || this->getPackType()==PWMsend_AllRet)
				{
					printf("\nEn:\t");
					for (char i = 0; i < nMot; i++) {
						printf("%d)%hd\t", i + 1, this->getEncoder()[Mot1 + i]);
					}
				}

				if(this->getPackType()==PWMsend_CurRet || this->getPackType()==PWMsend_AllRet)
				{
					printf("\nCurr:\t");
					for (char i = 0; i < nMot; i++) {
						printf("%d)%hd\t", i + 1, this->getCurrent()[Mot1 + i]);
					}
				}
				break;
			case SettingSet:
			case SettingGet:
				if (this->getPackType() == SettingSet) {
					printf("PackType: SettingSet\n");
					printf("Sending new Settings:\n");
				} else {
					printf("PackType: SettingGet\n");
					printf("Recive current Settings:\n");
				}
				this->printSetting(this->getSetting());
				break;
			case goHome:
				printf("PackType: goHomePack\n");
				printf("Sending: no parameters\n");
				printf("Reciving: no parameters\n");
				break;
		}
		printf("\n-------------------------------------------------------\n");
#endif //END Rasp print pack
	}

	void Pack::printSetting(settingsBoard &sets) {
#ifdef ScorboarFirmware
		Serial.print("#maxEn:\t\t");
		for (byte i = 0; i < nMot; i++) {
			Serial.print("\t");
			Serial.print((int)sets.maxEn[Mot1 + i]);
			delay(1);
		}
		Serial.println();

		Serial.print("#minEn:\t\t");
		for (byte i = 0; i < nMot; i++) {
			Serial.print("\t");
			Serial.print((int)sets.minEn[Mot1 + i]);
			delay(1);
		}
		Serial.println();

		Serial.print("#maxCurrMed:");
		for (byte i = 0; i < nMot; i++) {
			Serial.print("\t");
			Serial.print((int)sets.maxCurrMed[Mot1 + i]);
			delay(1);
		}
		Serial.println();
		Serial.flush();
		Serial.print("#AdcVref set: ");
		switch(sets.adcVref){
			case in1V1:
				Serial.println("Internal Reference at 1.1V");
				break;
			case in2V56:
				Serial.println("Internal Reference at 2.56V");
				break;
			case ext:
				Serial.println("External Reference (trimmer)");
				break;
			default:
				Serial.print("Register not set, number is: ");
				Serial.println(sets.adcVref);
				break;
		}
		delay(1);

		Serial.print("#Adc offset remove State: ");
		if(sets.diff)
			Serial.println("On");
		else
			Serial.println("Off");
		delay(1);

		Serial.println("#PWM duty cycle set timer 3&4 divisor to: ");
		Serial.print("\t");
		switch(sets.freq){
			case hz30:
				Serial.println("1024 for PWM frequency of 30.64 Hz");
				break;
			case hz120:
				Serial.println("256 for PWM frequency of 122.55 Hz");
				break;
			case hz490:
				Serial.println("64 for PWM frequency of 490.20 Hz");
				break;
			case hz4k:
				Serial.println("8 for PWM frequency of 3921.16 Hz");
				break;
			case hz30k:
				Serial.println("1 for PWM frequency of 31372.55 Hz");
				break;
			default:
				Serial.print("Register not set, number is: ");
				Serial.println(sets.freq);
				break;
		}
		Serial.println();
		delay(1);
		return;
#else //Start Rasp print pack
		printf("maxEn:\t");
		for (int i = 0; i < nMot; i++) {
			printf("%d)%hd\t", i + 1, sets.maxEn[Mot1 + i]);
		}

		printf("\nminEn:\t");
		for (int i = 0; i < nMot; i++) {
			printf("%d)%hd\t", i + 1, sets.minEn[Mot1 + i]);
		}

		printf("\nmaxCurrMed:\t");
		for (int i = 0; i < nMot; i++) {
			printf("%d)%hd\t", i + 1, sets.maxCurrMed[Mot1 + i]);
		}

		printf("\nadcReference voltage:\t");
		switch (sets.adcVref) {
			case in1V1:
                printf("Internal Reference 1.1V");
				break;
			case in2V56:
                printf("Internal Reference 2.56V");
				break;
			case ext:
                printf("External Source (Trimmer Reference)");
				break;
			default:
				printf("Register not set, number is: %d",sets.adcVref);
				break;
		}
		printf("\n");

		printf("Adc offset remove Read: ");
		if (sets.diff)
			printf("On");
		else
			printf("Off");
		printf("\n");

		printf("PWM duty cycle set timer 3&4 divisor to: ");
		switch (sets.freq) {
			case hz30:
				printf("1024 for PWM frequency of 30.64 Hz");
				break;
			case hz120:
				printf("256 for PWM frequency of 122.55 Hz");
				break;
			case hz490:
				printf("64 for PWM frequency of 490.20 Hz");
				break;
			case hz4k:
				printf("8 for PWM frequency of 3921.16 Hz");
				break;
			case hz30k:
				printf("1 for PWM frequency of 31372.55 Hz");
				break;
			default:
				printf("Register not set, number is: %d",sets.freq);
				break;
		}
		printf("\n");
		return;
#endif //END Rasp print pack

	}


	int Pack::sizePack() {
		switch (this->data.type) {
			case invalid:
				return -1;
				break;
			case PWMsend_EnRet:
				return max(sizeof(mSpeed), sizeof(mEncoder));
				break;
			case PWMsend_CurRet:
				return max(sizeof(mSpeed), sizeof(mCurrent));
				break;
			case PWMsend_AllRet:
				return max(sizeof(mSpeed), sizeof(mAll));
				break;
			case SettingGet:
				return sizeof(settingsBoard);
				break;
			case SettingSet:
				return sizeof(settingsBoard);
				break;
			case goHome:
				return 0;
				break;
		}
		return -1;
	}

	SPIPACK &Pack::getSPIPACK() {
		return this->data;
	}

	void Pack::setPackType(packType t) {
		this->data.type = t;
	}

	packType Pack::getPackType() {
		return this->data.type;
	}

	void Pack::pwmSet(mSpeed &pwms) {
		this->pwmSet(pwms[Mot1], pwms[Mot2], pwms[Mot3], pwms[Mot4], pwms[Mot5], pwms[Mot6]);
	}

	void Pack::pwmSet(short m1, short m2, short m3, short m4, short m5, short m6) {
		this->pwmSet(Mot1, m1);
		this->pwmSet(Mot2, m2);
		this->pwmSet(Mot3, m3);
		this->pwmSet(Mot4, m4);
		this->pwmSet(Mot5, m5);
		this->pwmSet(Mot6, m6);
	}

	void Pack::pwmSet(motCode mot, short mVal) {
		if (mVal == freeRun || mVal == hardStop || mVal == softStop || mVal == ignore || abs(mVal) <= 255)
			this->data.forArd.up.speed[mot] = mVal;
		else
			this->data.forArd.up.speed[mot] = ignore;
	}

	void Pack::setEncoder(mEncoder &en) {
		if (this->data.type == PWMsend_EnRet)
			memmove(&this->data.forRasp.up.en, &en, sizeof(mEncoder));
		else if (this->data.type == PWMsend_AllRet)
			memmove(&this->data.forRasp.up.sens.en, &en, sizeof(mEncoder));
#ifndef ScorboarFirmware
		else
			throw typePackWrongExcept("This pack can't set Encoder");
#endif
	}

	void Pack::setEncoder(motCode mot, short en) {
		if (this->data.type == PWMsend_EnRet)
			this->data.forRasp.up.cur[mot] = en;
		else if (this->data.type == PWMsend_AllRet)
			this->data.forRasp.up.sens.cur[mot] = en;
#ifndef ScorboarFirmware
		else
			throw typePackWrongExcept("This pack can't set Encoder");
#endif
	}

	void Pack::setCurrent(mCurrent &c) {
		if (this->data.type == PWMsend_CurRet)
			memmove(&this->data.forRasp.up.cur, &c, sizeof(mCurrent));
		else if (this->data.type == PWMsend_AllRet)
			memmove(&this->data.forRasp.up.sens.cur, &c, sizeof(mCurrent));
#ifndef ScorboarFirmware
		else
			throw typePackWrongExcept("This pack can't set Current");
#endif
	}

	void Pack::setCurrent(motCode mot, short cur) {
		if (cur < 0) cur = 0;
		if (this->data.type == PWMsend_CurRet)
			this->data.forRasp.up.cur[mot] = cur;
		else if (this->data.type == PWMsend_AllRet)
			this->data.forRasp.up.sens.cur[mot] = cur;
#ifndef ScorboarFirmware
		else
			throw typePackWrongExcept("This pack can't set Encoder");
#endif
	}

	void Pack::setSetting(settingsBoard &sets, packDest dest) {
		if (dest == pack4Ard) {
			this->setPackType(SettingSet);
			memmove(&this->data.forArd.up.prop, &sets, sizeof(settingsBoard));
		} else if (dest == pack4Rasp) {
			this->setPackType(SettingGet);
			memmove(&this->data.forRasp.up.prop, &sets, sizeof(settingsBoard));
		}
	}

	void Pack::setMotorLimit(packDest dest, motCode mot, short enMax, short enMin, short cur) {
		//Set variable inside the pack to send-out
		this->setMaxEn(dest, mot, enMax);
		this->setMinEn(dest, mot, enMin);
		this->setMaxCurrentMed(dest, mot, cur);
	}

	void Pack::setMaxEn(packDest dest, motCode mot, short en) {
		//Set variable inside the pack to send-out
		if (dest == pack4Ard) {
			this->setPackType(SettingSet);
			this->data.forArd.up.prop.maxEn[mot] = en;
		} else if (dest == pack4Rasp) {
			this->setPackType(SettingGet);
			this->data.forArd.up.prop.maxEn[mot] = en;
		}
	}

	void Pack::setMinEn(packDest dest, motCode mot, short en) {
		//Set variable inside the pack to send-out
		if (dest == pack4Ard) {
			this->setPackType(SettingSet);
			this->data.forArd.up.prop.minEn[mot] = en;
		} else if (dest == pack4Rasp) {
			this->setPackType(SettingGet);
			this->data.forRasp.up.prop.minEn[mot] = en;
		}
	}

	void Pack::setMaxCurrentMed(packDest dest, motCode mot, short current) {
		//Set variable inside the pack to send-out
		if (dest == pack4Ard) {
			this->setPackType(SettingSet);
			this->data.forArd.up.prop.maxCurrMed[mot] = current;
		} else if (dest == pack4Rasp) {
			this->setPackType(SettingGet);
			this->data.forRasp.up.prop.maxCurrMed[mot] = current;
		}
	}

	void Pack::setAdcRef(packDest dest, adcRef adc) {
		//Set variable inside the pack to send-out
		if (dest == pack4Ard) {
			this->setPackType(SettingSet);
			this->data.forArd.up.prop.adcVref = adc;
		}else if (dest == pack4Rasp) {
			this->setPackType(SettingGet);
			this->data.forRasp.up.prop.adcVref = adc;
		}
	}

	void Pack::setAdcDiff(packDest dest, bool diff) {
		if (dest == pack4Ard) {
			this->setPackType(SettingSet);
			this->data.forArd.up.prop.diff = diff;
		} else if (dest == pack4Rasp) {
			this->setPackType(SettingGet);
			this->data.forRasp.up.prop.diff = diff;
		}
	}

	void Pack::setPWMfreq(packDest dest, pwmFreq freq) {
		if (dest == pack4Ard) {
			this->setPackType(SettingSet);
			this->data.forArd.up.prop.freq = freq;
		} else if (dest == pack4Rasp) {
			this->setPackType(SettingGet);
			this->data.forRasp.up.prop.freq = freq;
		}
	}

	mSpeed &Pack::getPwm() {
#ifndef ScorboarFirmware
		if (this->data.type != PWMsend_EnRet && this->data.type != PWMsend_CurRet && this->data.type != PWMsend_AllRet)
			throw typePackWrongExcept("This pack not contain PWM");
#endif
		return this->data.forArd.up.speed;
	}

	mEncoder &Pack::getEncoder() {
		if (this->data.type == PWMsend_EnRet)
			return this->data.forRasp.up.en;
		else if (this->data.type == PWMsend_AllRet)
			return this->data.forRasp.up.sens.en;
#ifndef ScorboarFirmware
		else
			throw typePackWrongExcept("This pack not contain Encoder");
#endif
	}

	mCurrent &Pack::getCurrent() {
		if (this->data.type == PWMsend_CurRet)
			return this->data.forRasp.up.cur;
		else if (this->data.type == PWMsend_AllRet)
			return this->data.forRasp.up.sens.cur;
#ifndef ScorboarFirmware
		else
			throw typePackWrongExcept("This pack not contain Current");
#endif
	}

	mAll &Pack::getSens() {
		if (this->data.type == PWMsend_AllRet)
			return this->data.forRasp.up.sens;
#ifndef ScorboarFirmware
		else
			throw typePackWrongExcept("This pack not contain Sensor Data");
#endif
	}

	settingsBoard &Pack::getSetting(packDest dest) {
#ifndef ScorboarFirmware
		if (this->data.type != SettingSet && this->data.type != SettingGet)
			throw typePackWrongExcept("This pack not contain Settings");
#endif
		if (dest == pack4Ard)
			return this->data.forArd.up.prop;
		else if (dest == pack4Rasp)
			return this->data.forRasp.up.prop;
	}

	settingsBoard &Pack::getSetting() {
#ifndef ScorboarFirmware
		if (this->data.type != SettingSet && this->data.type != SettingGet)
			throw typePackWrongExcept("This pack not contain Settings");
#endif
		if (this->data.type == SettingSet)
			return this->data.forArd.up.prop;
		else if (this->data.type == SettingGet)
			return this->data.forRasp.up.prop;
		return this->data.forArd.up.prop;	//se non parte l'eccezione sono nell'arduino
	}

	SPIPACK *makeSPIPACK() {
		SPIPACK *p = (SPIPACK *) malloc(sizeof(SPIPACK));
		memset(p, 0, sizeof(SPIPACK));
		return p;
	}

	void freeSPIPACK(SPIPACK *p) {
		free(p);
	}

}
