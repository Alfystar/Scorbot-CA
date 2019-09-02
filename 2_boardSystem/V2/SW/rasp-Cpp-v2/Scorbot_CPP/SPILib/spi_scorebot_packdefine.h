#ifndef SPI_SCOREBOT_PACKDEFINE
#define SPI_SCOREBOT_PACKDEFINE

#define fr 300 //free running
#define hs 350 //hard stop
#define ss 400 //soft stop
#define ig 450 //ignore


#define nMot 6

typedef struct settingsBoard_ {
    short maxEn[nMot];        //valore massimo di passi prima di considerarsi fuori range di sicurezza (numeri pos)
    short minEn[nMot];        //valore minimo di passi prima di considerarsi fuori range di sicurezza (numeri neg)
    short maxCurrMed[nMot];    //valore massimo di corrente Efficace (con una media di 1 ms ~ ultime 8 letture), numero * 8 per semplificare i conti)
} settingsBoard;

enum modi {
    setPWM = 1, getCurrent, getSetting, setSetting, goHome
};
enum motCode {
    cMot1 = 0, cMot2, cMot3, cMot4, cMot5, cMot6
};

/*Tipi di pacchetti che si possono inviare, uno sovrapposto all'altro*/
typedef struct setPWMSend_ {
    short vel[nMot];
} setPWMSend;

//getCurrent domanda senza parametri

//getSetting domanda senza parametri

typedef struct setSettingSend_ {
    settingsBoard sets;
} setSettingSend;

//goHome richiesta senza parametri


/*Struttura di Invio, usata dalla classe SPISEND*/
typedef struct spiSend_ {
    union {
        setPWMSend speed;
        setSettingSend prop;
    } pack;
} spiSend;

/*#################################################################*/

/*Tipi di pacchetti che si possono ricevere, uno sovrapposto all'altro*/
typedef struct setPWMRet_     //risposta a setPWM
{
    short passi[nMot];
} setPWMRet;

typedef struct getCurrentRet_ {
    short current[nMot];
} getCurrentRet;

typedef struct getSettingRet_     //risposta a getSetting
{
    settingsBoard sets;
} getSettingRet;

//setSetting risposta non prevista


//goHWHome risposta Senza parametri extra

/*-----------------------------------------------------------------*/
/*Struttura di Ricezione, usata dalla classe SPISEND*/
typedef struct spiRet_ {
    union {
        setPWMRet en;
        getCurrentRet cur;
        getSettingRet prop;
    } pack;
} spiRet;

/** ## -------------------------------------------------------- ## **/
//todo mettere la stessaforma con le union presente sull'arduino
typedef struct SPIPACK_ {
    char type;
    spiSend out;
    spiRet in;
} SPIPACK;
/*
typedef struct SPIPACK_ {
	char type;
	union {
		spiRecive in;
		char buffIn[sizeof(spiRecive)];
	}inPack;
	union {
		spiSend out;
		char buffOut[sizeof(spiSend)];
	}outPack;
}SPIPACK;
*/


#endif // SPI_SCOREBOT_PACKDEFINE
