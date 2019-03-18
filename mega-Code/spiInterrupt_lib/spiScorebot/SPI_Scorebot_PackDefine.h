#ifndef SPISCOREBOT_PACKDEF_H
#define SPISCOREBOT_PACKDEF_H

enum modi {setPWM, getSetting, setSetting, setHome, goHome};


/* Tipi di pacchetti da ricevere, uno sovrapposto all'altro*/
typedef struct setPWMRecive_ {
  char text[32];
} setPWMRecive;

//getSetting richiesta senza parametri

typedef struct setSettingRecive_ {
  char text[16];
} setSettingRecive;

/*Struttura usata dall'interrupt per salvare le cose a occhi chiusi*/
typedef struct spiRecive_ {
  char type;
  union {
    setPWMRecive pwm;
    setSettingRecive prop;
  } pack;
} spiRecive;


/* Tipi di pacchetti da inviare, uno sovrapposto all'altro*/
typedef struct feedRet_ {
  char encoder[32];
} feedRet;

/*Struttura usata dall'interrupt per Inviare le cose a occhi chiusi*/
typedef struct spiSend_ {
  union {
    feedRet feedBack;
  } pack;
} spiSend;

#endif
