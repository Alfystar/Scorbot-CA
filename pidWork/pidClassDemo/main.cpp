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


int mot[nMot];

int main(int argc, char *argv[]) {
    if(argc!=2)
    {
        printf("inserire +/- per indicare obiettivo\n");
        exit(0);
    }

    int r[nMot];
    if(strcmp(argv[1],"+")==0)
    {
        r[cMot1]=  -5490;
        r[cMot2]=   2000;
        r[cMot3]=   4195;
        r[cMot4]=   2500;
        r[cMot5]=   2500;
        r[cMot6]=   1000;
    }else{
        r[cMot1]=   1666;
        r[cMot2]=  4000;
        r[cMot3]=   -542;
        r[cMot4]=   -240;
        r[cMot5]=  -3533;
        r[cMot6]=   2500;
    }
    printf("r1=%d, r2=%d, r3=%d, r4=%d, r5=%d, r6=%d\n",r[0],r[1],r[2],r[3],r[4],r[5]);

    pidM[cMot1] = new PIDScorbot(0.00055,0.0000000015,10,50,false,.8,0.02);
    pidM[cMot2] = new PIDScorbot(0.00055,0.0000000015,10,50,false,1.0,0.02);
    pidM[cMot3] = new PIDScorbot(0.00055,0.0000000015,10,50,true,.8,0.02);
    pidM[cMot4] = new PIDScorbot(0.00055,0.0000000015,10,110,true,.8,0.02);
    pidM[cMot5] = new PIDScorbot(0.00055,0.0000000015,10,133,false,.8,0.02);
    pidM[cMot6] = new PIDScorbot(0.00055,0.0000000015,10,85,false,.8,0.02);
    sender = new SpiSend();
    memset(&pack,0, sizeof(SPIPACK));

    usleep(500000);

    pack=sender->makeSPIPACK();
    sender->getEn(pack);
    long wait;

    while (true)
    {
        //Passaggio dei parametri al pid
        for(int i=cMot4;i<nMot;i++)
        {
            mot[cMot1+i]=pidM[cMot1+i]->motVal(r[cMot1+i],pack->in.pack.en.passi[cMot1+i]);
            printf("mot[cMot%d]=%d\n\n",i+1,mot[cMot1+i]);
        }

        //mot[cMot2]=pidM[cMot2]->motVal(r[cMot2],pack->in.pack.en.passi[cMot2]);
        //printf("mot[cMot%d]=%d ref=%d\n\n",2,mot[cMot2],r[cMot2]);

        //usati i dati dei pid prepara il pacchetto
        sender->fillPWMPACK(&pwmSend,mot[cMot1],mot[cMot2],mot[cMot3],mot[cMot4],mot[cMot5],mot[cMot6]);
        //sender->fillPWMPACK(&pwmSend,ig,ig,ig,ig,ig,85);

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
