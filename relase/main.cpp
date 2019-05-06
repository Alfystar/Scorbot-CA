#include <iostream>
#include <stdlib.h>
#include <sys/time.h>

#include "PidClass/PIDScorbot.h"
#include "SPILib/spisend.h"
#include "SPILib/spi_scorebot_packdefine.h"
#include "comC/comC.h"


/** Strutture per la com con python**/
struct messaggio msg;


/** Strutture per la comunicazione con lo scorbot**/
PIDScorbot *pidM[nMot];
SpiSend *sender;
SPIPACK *pack;
SPIPACK *packImp;
setPWMSend pwmSend;


/** Strutture per il pid **/
#define ts 10000 // 1 ms (in micro secondi)
struct timeval startCalc,endCalc;


int mot[nMot];

int main(int argc, char *argv[]) {
    if(argc!=3)
    {
        printf("Attenzione chamare:\nscorbot <mainUi.py> <dirPy>  //file python da chiamare  &  dir in cui si trova");
    }

    /** Variabili per il pid **/
    pidM[cMot1] = new PIDScorbot(0.00055,0.0000000015,10,50,false,.8,0.02);
    pidM[cMot2] = new PIDScorbot(0.00055,0.0000000015,10,50,false,1.0,0.02);
    pidM[cMot3] = new PIDScorbot(0.00055,0.0000000015,10,50,true,.8,0.02);
    pidM[cMot4] = new PIDScorbot(0.00055,0.0000000015,10,110,true,.8,0.02);
    pidM[cMot5] = new PIDScorbot(0.00055,0.0000000015,10,133,false,.8,0.02);
    pidM[cMot6] = new PIDScorbot(0.00055,0.0000000015,10,85,false,.8,0.02);
    long wait;

    /** Variabili per la comunicazione con lo scorbot **/
    sender = new SpiSend();
    memset(&pack,0, sizeof(SPIPACK));

    pack = sender->makeSPIPACK();
    packImp = sender->makeSPIPACK();
    sender->getEn(pack);

    /** Variabili per la com con Python **/
    //main_com("/ScorbotUI_py/mainUi.py");
    main_com(argv,argv[2]);
    memset(&msg,0, sizeof(struct messaggio));

    usleep(500000);


    /** Inizio codice */
    //invio prime letture encoder e corrente
    for (int j = 0; j < nMot; ++j) {
        msg.enc[cMot1+j]=pack->in.pack.en.passi[cMot1+j];
    }
    sender->pGetCurrent(pack);
    for (int j = 0; j < nMot; ++j) {
        msg.cor[cMot1+j]=pack->in.pack.cur.current[cMot1+j];
    }
    invia(&msg,"e");

    struct messaggio *msgGet;
    //faccio restare fermo il robot
    struct messaggio *oldMsgGet;
    oldMsgGet=(struct messaggio *)malloc(sizeof(struct messaggio));
    for (int j = 0; j < nMot; ++j) {
        oldMsgGet->enc[cMot1+j]=pack->in.pack.en.passi[cMot1+j];
    }

    while (true)
    {
        msgGet=getLast_m();
        if(msgGet==NULL)    //se non arriva nulla lascio il precedente
            msgGet=oldMsgGet;
        else{               //se arriva qualcosa cancello il precedente
            free(oldMsgGet);
            oldMsgGet=msgGet;
        }
        if (newImpostaziono)
        {
            for (int i = 0; i < nMot; ++i) {
                packImp->out.pack.prop.sets.maxCurrMed[cMot1+i]=imp_ut->maxC[cMot1+i];
                packImp->out.pack.prop.sets.maxEn[cMot1+i]=imp_ut->maxE[cMot1+i];
                packImp->out.pack.prop.sets.minEn[cMot1+i]=imp_ut->minE[cMot1+i];
            }
            sender->pSetSetting(packImp,&packImp->out.pack.prop);
            newImpostaziono=false;
        }


        /** --------------------------------------------------------------- **/
        //Passaggio dei parametri al pid
        for(int i=0;i<nMot;i++)
        {
            mot[cMot1+i]=pidM[cMot1+i]->motVal(msgGet->enc[cMot1+i],pack->in.pack.en.passi[cMot1+i]);
            printf("mot[cMot%d]=%d\n\n",i+1,mot[cMot1+i]);
        }

        //usati i dati dei pid prepara il pacchetto
        sender->fillPWMPACK(&pwmSend,mot[cMot1],mot[cMot2],mot[cMot3],mot[cMot4],mot[cMot5],mot[cMot6]);

        //aspetta il successivo tempo di campionamento
        gettimeofday(&endCalc,NULL);
        wait=abs((ts-(endCalc.tv_usec-startCalc.tv_usec)))%10000;
        usleep(wait);

        sender->pSetPWM(pack,&pwmSend);
        gettimeofday(&startCalc,NULL);
        /** --------------------------------------------------------------- **/
        //Invia encoder e correnti a python
        for (int j = 0; j < nMot; ++j) {
            msg.enc[cMot1+j]=pack->in.pack.en.passi[cMot1+j];
        }
        sender->pGetCurrent(pack);
        for (int j = 0; j < nMot; ++j) {
            msg.cor[cMot1+j]=pack->in.pack.cur.current[cMot1+j];
        }
        invia(&msg,"e");
        /** --------------------------------------------------------------- **/

    }

    return 0;
}
