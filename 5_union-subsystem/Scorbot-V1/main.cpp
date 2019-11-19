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
SPIPACK *packEn;
SPIPACK *packCur;
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
        exit(0);
    }

    int r[nMot];

    r[cMot1]=  -5490;
    r[cMot2]=   2000;
    r[cMot3]=   4195;
    r[cMot4]=   2500;
    r[cMot5]=   2500;
    r[cMot6]=   1000;



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

    packEn = sender->makeSPIPACK();
    packCur = sender->makeSPIPACK();
    packImp = sender->makeSPIPACK();


    /** Variabili per la com con Python **/
    //main_com("/ScorbotUI_py/mainUi.py");
    memset(&msg,0, sizeof(struct messaggio));
    main_com(argv,argv[2]);

    usleep(500000);


    /** Inizio codice */
    sender->getEn(packEn);

    struct messaggio *msgGet;
    //faccio restare fermo il robot
    struct messaggio *oldMsgGet;
    oldMsgGet=(struct messaggio *)malloc(sizeof(struct messaggio));
    memset(oldMsgGet,0,sizeof(struct messaggio));
    for (int j = 0; j < nMot; ++j) {
        oldMsgGet->enc[cMot1+j]=packEn->in.pack.en.passi[cMot1+j];
    }

    //invio prime letture encoder e corrente
    for (int j = 0; j < nMot; ++j) {
        msg.enc[cMot1+j]=packEn->in.pack.en.passi[cMot1+j];
    }
    sender->pGetCurrent(packCur);
    for (int j = 0; j < nMot; ++j) {
        msg.cor[cMot1+j]=packCur->in.pack.cur.current[cMot1+j];
    }
    invia(&msg,"e");


    sleep(1);
    long counter=0;
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
        int i;
        for(i=0;i<cMot2;i++)
        {
            //mot[cMot1+i]=pidM[cMot1+i]->motVal(r[cMot1+i],packEn->in.pack.en.passi[cMot1+i]);
            mot[cMot1+i]=pidM[cMot1+i]->motVal(msgGet->enc[cMot1+i],packEn->in.pack.en.passi[cMot1+i]);
            printf("msgGet->enc[cMot%d]=%d\tencoder[cMot%d]=%d\tmot[cMot%d]=%d\n\n",i+1,msgGet->enc[cMot1+i],i+1,packEn->in.pack.en.passi[cMot1+i],i+1,mot[cMot1+i]);
            //printf("r[cMot%d]=%d\tencoder[cMot%d]=%d\tmot[cMot%d]=%d\n\n",i+1,r[cMot1+i],i+1,packEn->in.pack.en.passi[cMot1+i],i+1,mot[cMot1+i]);
        }
        i=cMot6;
        mot[cMot1+i]=pidM[cMot1+i]->motVal(r[cMot1+i],packEn->in.pack.en.passi[cMot1+i]);


        //usati i dati dei pid prepara il pacchetto
        sender->fillPWMPACK(&pwmSend,mot[cMot1],mot[cMot2],mot[cMot3],mot[cMot4],mot[cMot5],mot[cMot6]);

        //aspetta il successivo tempo di campionamento
        gettimeofday(&endCalc,NULL);
        wait=abs((ts-(endCalc.tv_usec-startCalc.tv_usec)))%10000;
        usleep(wait);

        sender->pSetPWM(packEn,&pwmSend);
        //sender->getEn(packEn);
        gettimeofday(&startCalc,NULL);
        /** --------------------------------------------------------------- **/
        if(counter%10==0)
        {
            //Invia encoder e correnti a python
            for (int j = 0; j < nMot; ++j) {
                msg.enc[cMot1+j]=packEn->in.pack.en.passi[cMot1+j];
            }
            //sender->printSPIPACK(pack);
            sender->pGetCurrent(packCur);
            for (int j = 0; j < nMot; ++j) {
                msg.cor[cMot1+j]=packCur->in.pack.cur.current[cMot1+j];
            }
            invia(&msg,"e");
            //sender->printSPIPACK(packCur);
        }
        counter= (counter+1)%10;
        /** --------------------------------------------------------------- **/

    }

    return 0;
}
