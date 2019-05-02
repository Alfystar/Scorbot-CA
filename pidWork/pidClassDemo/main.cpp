#include <iostream>
#include "PidClass/PIDScorbot.h"
#include "SPILib/spisend.h"
#include "SPILib/spi_scorebot_packdefine.h"


PIDScorbot *pidM[nMot];
SpiSend *sender;
SPIPACK *pack;
setPWMSend packSend;
#define ts 10000 // 10 ms (in micro secondi)
int mot[nMot];
int main() {
    pidM[cMot1] = new PIDScorbot(1,1,1,50,false);
    pidM[cMot2] = new PIDScorbot(1,1,1,50,false);
    pidM[cMot3] = new PIDScorbot(1,1,1,50,false);
    pidM[cMot4] = new PIDScorbot(1,1,1,50,false);
    pidM[cMot5] = new PIDScorbot(1,1,1,50,false);
    pidM[cMot6] = new PIDScorbot(1,1,1,50,false);
    sender = new SpiSend();
    memset(&pack,0, sizeof(SPIPACK));

    while (true)
    {

        mot[cMot1]=pidM[cMot1]->motVal(1000,pack->in.pack.en[cMot1]);
        sender->fillPWMPACK(&packSend,mot[cMot1],ig,ig,ig,ig,ig);
        pack=sender->pSetPWM(&packSend);

        usleep(ts);
    }

    return 0;
}