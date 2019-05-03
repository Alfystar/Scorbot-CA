#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include "PidClass/PIDScorbot.h"
#include "SPILib/spisend.h"
#include "SPILib/spi_scorebot_packdefine.h"


#define ts 10000 // 1 ms (in micro secondi)


PIDScorbot *pidM[nMot];
SpiSend *sender;
SPIPACK *pack;
setPWMSend pwmSend;

struct timeval startCalc,endCalc;

//0.000000000005
int mot[nMot];
int main() {
    pidM[cMot1] = new PIDScorbot(0.00055,0.0000000015,10,50,false,1.0,0.02);
    pidM[cMot2] = new PIDScorbot(1,1,1,50,false);
    pidM[cMot3] = new PIDScorbot(1,1,1,50,false);
    pidM[cMot4] = new PIDScorbot(1,1,1,50,false);
    pidM[cMot5] = new PIDScorbot(1,1,1,50,false);
    pidM[cMot6] = new PIDScorbot(1,1,1,50,false);
    sender = new SpiSend();
    memset(&pack,0, sizeof(SPIPACK));

    sleep(1);

    pack=sender->makeSPIPACK();
    sender->getEn(pack);
    long wait;
    while (true)
    {
        //Passaggio dei parametri al pid
        mot[cMot1]=pidM[cMot1]->motVal(-10000,pack->in.pack.en.passi[cMot1]);
        printf("mot[cMot1]=%d\n\n",mot[cMot1]);

        //usati i dati dei pid prepara il pacchetto
        sender->fillPWMPACK(&pwmSend,mot[cMot1],ig,ig,ig,ig,ig);

        //aspetta il successivo tempo di campionamento
        gettimeofday(&endCalc,NULL);
        wait=abs((ts-(endCalc.tv_usec-startCalc.tv_usec)))%10000;
        usleep(wait);

        //invia il pacchetto
        sender->pSetPWM(pack,&pwmSend);
        sender->printSPIPACK(pack);
        gettimeofday(&startCalc,NULL);
        printf("\n\n\n\n\n");

    }

    return 0;
}
