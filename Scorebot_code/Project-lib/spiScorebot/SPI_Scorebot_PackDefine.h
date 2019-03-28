#ifndef SPISCOREBOT_PACKDEF_H
#define SPISCOREBOT_PACKDEF_H

#include "../globalDef.h"

enum modi {
	setPWM, getCurrent, getSetting, setSetting, setHome, goHome
};

/* Tipi di pacchetti da ricevere, uno sovrapposto all'altro*/
typedef struct setPWMRecive_ {
	char pwm[nMot];
} setPWMRecive;

//getCurrent richiesta senza parametri

//getSetting richiesta senza parametri

typedef struct setSettingRecive_ {
	settingsBoard sets;
} setSettingRecive;

//goHome richiesta senza parametri

/*-----------------------------------------------------------------*/
/*Struttura usata dall'interrupt per salvare le cose a occhi chiusi*/
typedef struct spiRecive_ {
	char type;
	union {
		setPWMRecive pwm;
		setSettingRecive prop;
	} pack;
} spiRecive;

/*#################################################################*/

/* Tipi di pacchetti da inviare, uno sovrapposto all'altro*/
typedef struct setPWMSend_ {
	int passi[nMot];
} setPWMSend;

typedef struct getCurrentSend_{
	int current[nMot];
}getCurrentSend;

typedef struct getSettingSend_ {
	settingsBoard sets;
} getSettingSend;

//setSetting non invia parametri

//goHome non invia parametri extra

/*-----------------------------------------------------------------*/
/*Struttura usata dall'interrupt per Inviare le cose a occhi chiusi*/
typedef struct spiSend_ {
	union {
		setPWMSend feedBack;
		getCurrentSend curr;
		getSettingSend prop;
	} pack;
} spiSend;



/** ## -------------------------------------------------------- ## **/
typedef struct SPIPACK_ {
	spiRecive in;
	spiSend out;
};
#endif
