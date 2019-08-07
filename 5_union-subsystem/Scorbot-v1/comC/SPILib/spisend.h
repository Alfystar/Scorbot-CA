#ifndef SPISEND_H
#define SPISEND_H

#include "spi_scorebot_packdefine.h"

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstring>
#include <iostream>

//enum modi {setPWM=1, getCurrent, getSetting, setSetting, goHome};

class SpiSend
{
public:
    //costruttori/distruttori
    SpiSend();
    virtual ~SpiSend();

    //debug funx
    void printSPIPACK(SPIPACK *s);

    //sending metod
    SPIPACK *pSetPWM(SPIPACK *pack,setPWMSend *pwm);
    SPIPACK *getEn(SPIPACK *p);
    SPIPACK *pGetCurrent(SPIPACK *p);
    SPIPACK *pGetSetting(SPIPACK *p);
    SPIPACK *pSetSetting(SPIPACK *p,setSettingSend *sets);
    SPIPACK *pGoHome(SPIPACK *p);

    //utility
    setPWMSend *fillPWMPACK(setPWMSend * pack,int m1,int m2,int m3,int m4,int m5,int m6);

    //create/destroy pack
    SPIPACK *makeSPIPACK();
    void freeSPIPACK(SPIPACK *p);


protected:
private:
    char *txbuf,*rxbuf;
    int size,fdSpi;
    const int hzSpeed=50000; //50Khz per dare tempo ad arduino
    const char bitWord=8;
    void setMode(char mode);
    void sendPack (SPIPACK *s);
    int sizeTypePack(SPIPACK *s);

};

#endif // SPISEND_H
