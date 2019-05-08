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
    SpiSend();
    virtual ~SpiSend();
    void printSPIPACK(SPIPACK *s);
    SPIPACK *pSetPWM(setPWMSend *pwm);
    setPWMSend *fillPWMPACK(setPWMSend * pack,int m1,int m2,int m3,int m4,int m5,int m6);
    SPIPACK *pGetCurrent();
    SPIPACK *pGetSetting();
    SPIPACK *pSetSetting(setSettingSend *sets);
    SPIPACK *pGoHome();
protected:
private:
    char *txbuf,*rxbuf;
    int size,fdSpi;
    const int hzSpeed=50000; //50Khz per dare tempo ad arduino
    const char bitWord=8;
    void setMode(char mode);
    void sendPack (SPIPACK *s);
    int sizeTypePack(SPIPACK *s);
    SPIPACK *makeSPIPACK();

};

#endif // SPISEND_H
