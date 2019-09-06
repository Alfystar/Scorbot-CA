#include <iostream>
#include "SPILib/SpiRaspInterface.h"
#include "SPILib/SpiPack.h"
#include <string.h>

using namespace SpiRaspInterface;
using namespace spiPack;

#define fflush(stdin) while(getchar() != '\n');

void help() {
    printf("Menù di controllo TEST SPI dello scorbot:\n");
    printf("\tm -- Muove tutti i motori a caso per il timeout sulla scheda\n");
    printf("\t\tm <m1>;<m1>;<m1>;<m1>;<m1>;<m1> -- Muove Ogni motore della scheda a quel PWM\n");
    printf("\t\t\t fr = Free Running, hs = Hard Stop, ss = Soft Stop, ig = Ignora\n");
    printf("\te -- Ritorna Encoder di tutti\n");
    printf("\tc -- get current \n");
    printf("\tg -- get setting\n");
    printf("\ts -- set setting valori di default\n");
    printf("\th -- go home\n");
    printf("\t? -- visualizza l'help\n");

}

ScorBoard &send = ScorBoard::getInstance();;
Pack *p;

/** Cmd terminal **/
char cmdBuf[1024];
char *sArgv[64];  //consento lo storage fino a 64 comandi
int sArgc = 0;
char *savePoint;

int main() {
    //Crea gli oggetti e le strutture necessarie alla comunicazione
    p = new Pack();
    int v = 150;
    p->pwmSet(v, -v, v, -v, v, -v);

    help();

    printf("Start loop\n");

    while (1) {
        printf("\n>> ");
        scanf("%[^\n]", cmdBuf);

        /** Tokenizzazione di cmd per creare un effetto argv[] **/
        sArgc = 0;
        sArgv[sArgc] = strtok_r(cmdBuf, " ", &savePoint);
        while (sArgv[sArgc] != nullptr) {
            sArgc++;
            sArgv[sArgc] = strtok_r(nullptr, " ", &savePoint);
        }
        fflush(stdin);

        p->clearPack();

        if (sArgc <= 1) {
            if (strcmp(sArgv[0], "m") == 0) {
                v *= -1;
                //al posto di pwm si potrebbe anche mettere &s->out.up.speed,
                //ma la libreria per sicurezza poi in pSetPWM lo copia nuovamente
                //in maniera trasparente al progammatore
                p->pwmSet(v, -v, v, -v, v, -v);
                send.setPwm_EnPack(*p);
            }
            if (strcmp(sArgv[0], "e") == 0) {
                send.getEnPack(*p);
                p->printPack();
            }
            if (strcmp(sArgv[0], "c") == 0) {
                send.getCurrentPack(*p);
                p->printPack();
            }
            if (strcmp(sArgv[0], "g") == 0) {
                send.getSettingPack(*p);
                p->printPack();
            }
            if (strcmp(sArgv[0], "s") == 0) {
                /*Assegnazione limiti scoperti sperimentalmente*/
                p->setMotorLimit(pack4Ard,Mot1,2160,24300,-19450);
                p->setMotorLimit(pack4Ard,Mot2,2960,16200,-1000);
                p->setMotorLimit(pack4Ard,Mot3,2960,21900,-7300);
                p->setMotorLimit(pack4Ard,Mot4,2160,10000,-10000);
                p->setMotorLimit(pack4Ard,Mot5,2400,10000,-10000);
                p->setMotorLimit(pack4Ard,Mot6,2160,5770,-10);

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
        }
        if (sArgc <= 7) {
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
        }else{
            printf("!!! Comando non riconosciuto!!!\n");
            help();
        }
    }
    return 0;
}

