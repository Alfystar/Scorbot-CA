#include <iostream>
#include <sys/time.h>
#include "PidClass/PIDScorbot.h"
#include "SPILib/spisend.h"
#include "SPILib/spi_scorebot_packdefine.h"


#define ts 10000 // 10 ms (in micro secondi)


PIDScorbot *pidM[nMot];
SpiSend *sender;
SPIPACK *pack;
setPWMSend pwmSend;

struct timeval startCalc,endCalc;


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

    pack=sender->makeSPIPACK();
    sender->getEn(pack);

    while (true)
    {
        gettimeofday(&startCalc,NULL);
        //Passaggio dei parametri al pid
        mot[cMot1]=pidM[cMot1]->motVal(1000,pack->in.pack.en.passi[cMot1]);

        //usati i dati dei pid prepara il pacchetto
        sender->fillPWMPACK(&pwmSend,mot[cMot1],ig,ig,ig,ig,ig);

        gettimeofday(&endCalc,NULL);

        //aspetta il successivo tempo di campionamento
        usleep(ts-(endCalc.tv_usec-startCalc.tv_usec));
        //invia il pacchetto
        sender->pSetPWM(pack,&pwmSend);

    }

    return 0;
}