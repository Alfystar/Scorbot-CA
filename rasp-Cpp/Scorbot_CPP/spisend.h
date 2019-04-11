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
    SPIPACK *pGetCurrent();
    SPIPACK *pGetSetting();
    SPIPACK *pSetSetting(setSettingSend *sets);
    SPIPACK *pGoHome();
protected:
private:
    char *txbuf,*rxbuf;
    int size,fdSpi;
    const int hzSpeed=50000; //50Khz dovrebbe anche a 100Khz
    const char bitWord=8;
    void setMode(char mode);
    void sendPack (SPIPACK *s);
    int sizeTypePack(SPIPACK *s);

};

#endif // SPISEND_H
