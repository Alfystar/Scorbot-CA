#include <iostream>
#include <stdio.h>
#include "SPILib/SpiRaspInterface.h"
#include "../SpiPack/SpiPack.h"
#include <string.h>
#include <sys/time.h>
using namespace SpiRaspInterface;
using namespace spiPack;
#define fflush(stdin) while(getchar() != '\n');

/*
    enum packType {
        invalid = 0, PWMsend_EnRet = 1, PWMsend_CurRet, PWMsend_AllRet, SettingGet, SettingSet, goHome
    };
*/
void help() {
    printf("Menù di controllo TEST SPI dello scorbot:\n");
    printf("\tm -- Muove tutti i motori a caso per il timeout sulla scheda\n");
    printf("\t\tm <m1>;<m1>;<m1>;<m1>;<m1>;<m1> -- Muove Ogni motore della scheda a quel PWM\n");
    printf("\t\t fr = Free Running, hs = Hard Stop, ss = Soft Stop, ig = Ignora\n");
    printf("\te -- Encoder Reading (PWMsend_EnRet)\n");
    printf("\tc -- Current Reading (PWMsend_CurRet)\n");
    printf("\tcM -- Current Reading and save for matlab (PWMsend_CurRet)\n");
    printf("\ta -- Encoder&Current Reading (PWMsend_AllRet)\n");
    printf("\taf -- Encoder&Current Reading for 10 seconds\n");
    printf("\tg -- Read arduino Settings (SettingGet)\n");
    printf("\ts -- Overide arduino setting (SettingSet)\n");
    printf("\tsr -- set next level ref (SettingSet)\n");
    printf("\tsd -- invert diff read (SettingSet)\n");
    printf("\th -- Start Homming procedure (goHome)\n");
    printf("\t? -- visualizza l'help\n");

}

int cfileexists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

ScorBoard &send = ScorBoard::getInstance();;
Pack *p;

/** Cmd terminal **/
char cmdBuf[1024];
char *sArgv[64];  //consento lo storage fino a 64 comandi
int sArgc = 0;
char *savePoint;

struct timeval startTime, endTime;
long wait;

#define Tsamp 3 //ms
FILE *fp;
char fileName[128];
int indexFile=0;

int main() {
    //Crea gli oggetti e le strutture necessarie alla comunicazione
    p = new Pack();
    ScoreCalc *calc = new ScoreCalc(0.280,0.140,10);
    calc->settingPrint();
    int v = 150;
    p->pwmSet(v, -v, v, -v, v, -v);
    help();
    printf("Start loop\n");
    while (1) {
        printf("\n>> ");
        scanf("%[^\n]", cmdBuf);

        // Tokenizzazione di cmd per creare un effetto argv[] //
        sArgc = 0;
        sArgv[sArgc] = strtok_r(cmdBuf, " ", &savePoint);
        while (sArgv[sArgc] != nullptr) {
            sArgc++;
            sArgv[sArgc] = strtok_r(nullptr, " ", &savePoint);
        }
        fflush(stdin);
        for (int i = 0; i < sArgc; i++) {
            printf("%d) %s\n", i, sArgv[i]);
        }

        //todo: capire perche strcmp da segmentation fault in questa condizione
        //strcmp("m", "m");
        p->clearPack();
        if (sArgc >= 1) {
            if (strcmp(sArgv[0], "m") == 0) {
                v *= -1;
                //al posto di pwm si potrebbe anche mettere &s->out.up.speed,
                //ma la libreria per sicurezza poi in pSetPWM lo copia nuovamente
                //in maniera trasparente al progammatore
                p->pwmSet(v, -v, v, -v, v, -v);
                send.setPwm_EnPack(*p);
                p->printPack();
            }
            if (strcmp(sArgv[0], "e") == 0) {
                send.getEnPack(*p);
                p->printPack();
            }
            if (strcmp(sArgv[0], "c") == 0) {
                send.getCurrentPack(*p);
                p->printPack();
                calc->adc2curr(*p);

            }
            if (strcmp(sArgv[0], "cM") == 0) {
                calc->settingPrint();
                //file opening
                do{
                    sprintf(fileName,"current%d.dat",indexFile);
                    indexFile++;
                    printf("New file name:%s\n",fileName);
                } while(cfileexists(fileName));
                fp = fopen(fileName,"w+");
                fprintf(fp,"Mot1\tMot2\tMot3\tMot4\tMot5\tMot6\tTsample=%dms\n",Tsamp);
                usleep(3000000);
                //Moving scorbot
                send.goHomePack();

                for (int j = 0; j < 3000; j++) {
                    printf("%d\n",j);
                    send.getCurrentPack(*p);
                    gettimeofday(&startTime, NULL);

                    //file saving
                    p->printPack();
                    calc->adc2curr(*p);
                    for(int i = Mot1;i<nMot;i++){
                        fprintf(fp,"%.6f\t",calc->adc2curr(p->getCurrent()[i]));
                    }
                    fprintf(fp,"\n");

                    gettimeofday(&endTime, NULL);
                    wait=abs(Tsamp*1000-(endTime.tv_usec-startTime.tv_usec))%Tsamp*1000;
                    usleep(wait);
                }
                fclose(fp);
            }
            if (strcmp(sArgv[0], "a") == 0) {
                send.getSensPack(*p);
                p->printPack();
                calc->adc2curr(*p);
            }
            if (strcmp(sArgv[0], "af") == 0) {
                for (int i = 0; i < 10000; i++) {
                    send.getSensPack(*p);
                    p->printPack();
                    calc->adc2curr(*p);
                    usleep(2 * 1000);
                }
            }
            if (strcmp(sArgv[0], "g") == 0) {
                send.getSettingPack(*p);
                p->printPack();
            }
            if (strcmp(sArgv[0], "s") == 0) {
                /*Assegnazione limiti scoperti sperimentalmente*/
                p->clearPack();
                p->setPackType(SettingSet);
                //curr neg => no limit
                p->setMotorLimit(pack4Ard, Mot1, 2160, 24300, -19450);
                p->setMotorLimit(pack4Ard, Mot2, 2960, 16200, -1000);
                p->setMotorLimit(pack4Ard, Mot3, 2960, 21900, -7300);
                p->setMotorLimit(pack4Ard, Mot4, 2160, 10000, -10000);
                p->setMotorLimit(pack4Ard, Mot5, 2400, 10000, -10000);
                p->setMotorLimit(pack4Ard, Mot6, 2160, 5770, -10);
                p->setAdcDiff(pack4Ard, false);
                p->setAdcRef(pack4Ard, in1V1);
                p->setPWMfreq(pack4Ard, hz4k);
                p->printPack();
                send.setSettingPack(*p);
                p->printPack();
            }
            if (strcmp(sArgv[0], "sr") == 0) {
                send.getSettingPack(*p);
                //move settings from arduino pack to rasp pack
                p->setSetting(pack4Ard, p->getSetting());
                //change parameter i need
                int ref = p->getSetting().adcVref;
                ref = (ref + 1) % 3;
                p->setAdcRef(pack4Ard, (adcRef) ref);
                send.setSettingPack(*p);
                p->printPack();
            }
            if (strcmp(sArgv[0], "sd") == 0) {
                send.getSettingPack(*p);
                //move settings from arduino pack to rasp pack
                p->setSetting(pack4Ard, p->getSetting());
                //change parameter i need
                p->setAdcDiff(pack4Ard, !p->getSetting().diff);
                send.setSettingPack(*p);
                p->printPack();
            }
            if (strcmp(sArgv[0], "h") == 0) {
                send.goHomePack();
                p->printPack();
            }
            if (strcmp(sArgv[0], "?") == 0) {
                help();
            }
        } else if (sArgc >= 7) {
            if (strcmp(sArgv[0], "m") == 0) {
                mSpeed motP;
                for (int i = 0; i < nMot; ++i) {
                    if (strcmp(sArgv[1 + i], "fr") == 0)
                        motP[Mot1 + i] = freeRun;
                    else if (strcmp(sArgv[1 + i], "hs") == 0)
                        motP[Mot1 + i] = hardStop;
                    else if (strcmp(sArgv[1 + i], "ss") == 0)
                        motP[Mot1 + i] = softStop;
                    else if (strcmp(sArgv[1 + i], "ig") == 0)
                        motP[Mot1 + i] = ignore;
                    else motP[Mot1 + i] = atoi(sArgv[1 + i]);
                }
                p->pwmSet(motP);
                send.setPwm_EnPack(*p);
                p->printPack();
            }
        } else {
            printf("!!! Comando non riconosciuto!!!\n");
            help();
        }
    }
    return 0;
}

