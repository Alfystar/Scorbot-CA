#ifndef SPISCOREBOT_PACKDEF_H
#define SPISCOREBOT_PACKDEF_H

#include "../globalDef.h"

enum modi {
	setPWM = 0, getCurrent, getSetting, setSetting, goHome
};

/* Tipi di pacchetti da ricevere, uno sovrapposto all'altro*/
typedef struct setPWMRecive_ {
	signed int vel[nMot];
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
		setPWMRecive speed;
		setSettingRecive prop;
	} pack;
} spiRecive;

/*#################################################################*/

/* Tipi di pacchetti da inviare, uno sovrapposto all'altro*/
typedef struct setPWMSend_ {
	int passi[nMot];
} setPWMSend;

typedef struct getCurrentSend_ {
	int current[nMot];
} getCurrentSend;

typedef struct getSettingSend_ {
	settingsBoard sets;
} getSettingSend;

//setSetting non invia parametri

//goHome non invia parametri extra

/*-----------------------------------------------------------------*/
/*Struttura usata dall'interrupt per Inviare le cose a occhi chiusi*/
typedef struct spiSend_ {
	union {
		setPWMSend en;
		getCurrentSend curr;
		getSettingSend prop;
	} pack;
} spiSend;

/** ## -------------------------------------------------------- ## **/
typedef struct SPIPACK_ {
	union {
		spiRecive in;
		char buffIn[sizeof(spiRecive)];
	}inPack;
	union {
		spiSend out;
		char buffOut[sizeof(spiSend)];
	}outPack;
}SPIPACK;
#endif
