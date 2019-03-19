#ifndef SPI_SCOREBOT_PACKDEFINE
#define SPI_SCOREBOT_PACKDEFINE

enum modi {setPWM, getSetting, setSetting, setSWHome,goHWHome};


/*Tipi di pacchetti che si possono inviare, uno sovrapposto all'altro*/
typedef struct setPWMSend_
{
    char text[32];
}setPWMSend;

// getSetting domanda senza parametri

typedef struct setSettingSend_
{
    char newSet[32];
}setSettingSend;

//setSWHome affermazione senza parametri

//goHWHome affermazione senza parametri



/*Struttura di Invio, usata dalla classe SPISEND*/
typedef struct spiSend_
{
    char type;
    union {
        setPWMSend pwm;
        setSettingSend prop;
    }pack;
}spiSend;



/*Tipi di pacchetti che si possono ricevere, uno sovrapposto all'altro*/
typedef struct feedRet_     //risposta a setPWM
{
    char text[32];
}feedRet;


typedef struct getSettingRet_     //risposta a getSetting
{
    char text[32];
}getSettingRet;

//setSetting risposta non prevista

//setSWHome risposta non prevista

//goHWHome risposta non prevista



/*Struttura di Ricezione, usata dalla classe SPISEND*/
typedef struct spiRet_
{
    char type;
    union {
        feedRet_ sensor;
        getSettingRet_ prop;
    }pack;
}spiRet;

#endif // SPI_SCOREBOT_PACKDEFINE
