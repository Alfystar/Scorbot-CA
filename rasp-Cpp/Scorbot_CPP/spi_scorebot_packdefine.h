#ifndef SPI_SCOREBOT_PACKDEFINE
#define SPI_SCOREBOT_PACKDEFINE

#define nMot 6

typedef struct settingsBoard_ {
	short maxEn[nMot]; 		//valore massimo di passi prima di considerarsi fuori range di sicurezza (numeri pos)
    short minEn[nMot]; 		//valore minimo di passi prima di considerarsi fuori range di sicurezza (numeri neg)
    short maxCurrMed[nMot];	//valore massimo di corrente Efficace (con una media di 1 ms ~ ultime 8 letture), numero * 8 per semplificare i conti)
} settingsBoard;

enum modi {setPWM, getCurrent, getSetting, setSetting, setHome, goHome};

/*Tipi di pacchetti che si possono inviare, uno sovrapposto all'altro*/
typedef struct setPWMSend_
{
    char pwm[nMot];
}setPWMSend;

// getSetting domanda senza parametri

//getSetting domanda senza parametri


typedef struct setSettingSend_
{
    settingsBoard sets;
}setSettingSend;

//goHome richiesta senza parametri


/*Struttura di Invio, usata dalla classe SPISEND*/
typedef struct spiSend_
{
    char type;
    union {
        setPWMSend pwm;
        setSettingSend prop;
    }pack;
}spiSend;

/*#################################################################*/

/*Tipi di pacchetti che si possono ricevere, uno sovrapposto all'altro*/
typedef struct setPWMRet_     //risposta a setPWM
{
    short passi[nMot];
}setPWMRet;

typedef struct getCurrentRet_{
    short current[nMot];
}getCurrentRet;

typedef struct getSettingRet_     //risposta a getSetting
{
    settingsBoard sets;
}getSettingRet;

//setSetting risposta non prevista


//goHWHome risposta Senza parametri extra

/*-----------------------------------------------------------------*/
/*Struttura di Ricezione, usata dalla classe SPISEND*/
typedef struct spiRet_
{
    char type;
    union {
        setPWMRet en;
        getCurrentRet cur;
        getSettingRet prop;
    }pack;
}spiRet;

/** ## -------------------------------------------------------- ## **/
typedef struct SPIPACK_ {
    spiSend out;
    spiRet in;
};

#endif // SPI_SCOREBOT_PACKDEFINE
