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


class SpiSend
{
public:
    SpiSend();
    virtual ~SpiSend();
    void hello();
    void sendPack (SPIPACK *s);
protected:
private:
    char *txbuf,*rxbuf;
    int size,fdSpi;
    void setMode(char mode);
    int sizeTypePack(SPIPACK *s);

};

#endif // SPISEND_H
