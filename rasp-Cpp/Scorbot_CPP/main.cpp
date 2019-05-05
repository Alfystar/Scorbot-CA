#include <iostream>
#include "SPILib/spisend.h"
#include "SPILib/spi_scorebot_packdefine.h"
#include <string.h>

using namespace std;

#define fflush(stdin) while(getchar() != '\n');

void waitEnter() {
    scanf("%[^\n]", NULL);
    fflush(stdin);
}

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

SpiSend *send;

/** Cmd terminal **/
char cmdBuf[1024];
char *sArgv[64];  //consento lo storage fino a 64 comandi
int sArgc = 0;
char *savePoint;

int main() {
    //Crea gli oggetti e le strutture necessarie alla comunicazione
    send = new SpiSend();
    SPIPACK *s = send->makeSPIPACK();

    //Pachetti per comunicazioni specifiche
    setPWMSend pwm;
    setSettingSend prop;


    int v = 150;
    send->fillPWMPACK(&pwm, v, -v, v, -v, v, -v);

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

        if (sArgc < 1) {
            if (strcmp(sArgv[0], "m") == 0) {
                v *= -1;
                //al posto di pwm si potrebbe anche mettere &s->out.pack.speed,
                //ma la libreria per sicurezza poi in pSetPWM lo copia nuovamente
                //in maniera trasparente al progammatore
                send->fillPWMPACK(&pwm, v, -v, v, -v, v, -v);
                send->pSetPWM(s, &pwm);
                send->printSPIPACK(s);
            }
            if (strcmp(sArgv[0], "e") == 0) {
                send->getEn(s);
                send->pSetPWM(s, &s->out.pack.speed);
                send->printSPIPACK(s);
            }
            if (strcmp(sArgv[0], "c") == 0) {
                send->pGetCurrent(s);
                send->printSPIPACK(s);
            }
            if (strcmp(sArgv[0], "g") == 0) {
                send->pGetSetting(s);
                send->printSPIPACK(s);
            }
            if (strcmp(sArgv[0], "s") == 0) {
                /*for (int i = 0; i < nMot; i++){
                    prop.sets.maxCurrMed[cMot1+i]+=i;
                    prop.sets.maxEn[cMot1+i]+=i*2;
                    prop.sets.minEn[cMot1+i]+=i*3;
                }*/
                /*Assegnazione limiti scoperti sperimentalmente*/
                prop.sets.maxCurrMed[cMot1] = 2160; //250*8
                prop.sets.maxEn[cMot1] = 24300; //24379
                prop.sets.minEn[cMot1] = -19450; //-19509

                prop.sets.maxCurrMed[cMot2] = 2960; //350*8
                prop.sets.maxEn[cMot2] = 16200; //16229
                prop.sets.minEn[cMot2] = -1000; //-1110

                prop.sets.maxCurrMed[cMot3] = 2960; //350*8
                prop.sets.maxEn[cMot3] = 21900; //21960
                prop.sets.minEn[cMot3] = -7300; //-7344

                /********************************************
                 * Dipende da rotazione il numero di encoder, lo lasciamo
                 * apposta molto grande per non far interferire
                 */
                prop.sets.maxCurrMed[cMot4] = 2160; //250*8
                prop.sets.maxEn[cMot4] = 10000; //NA
                prop.sets.minEn[cMot4] = -10000; //NA

                prop.sets.maxCurrMed[cMot5] = 2400; //250*8
                prop.sets.maxEn[cMot5] = 10000; //NA
                prop.sets.minEn[cMot5] = -10000; //NA
                /********************************************/

                /*La pinza al contrario vogliamo che si possa aprire tuttu*/
                prop.sets.maxCurrMed[cMot6] = 2160; //250*8
                prop.sets.maxEn[cMot6] = 5770; //5749
                prop.sets.minEn[cMot6] = -10; //0


                send->pSetSetting(s, &prop);
                send->printSPIPACK(s);
            }
            if (strcmp(sArgv[0], "h") == 0) {
                send->pGoHome(s);
                send->printSPIPACK(s);
            }
            if (strcmp(sArgv[0], "?") == 0) {
                help();
            }
        }
        if (sArgc < 7) {
            if (strcmp(sArgv[0], "m") == 0) {
                /*
                 * #define fr 300 //free running
                 * #define hs 350 //hard stop
                 * #define ss 400 //soft stop
                 * #define ig 450 //ignore
                 */
                int motP[nMot];
                for (int i = 0; i < nMot; ++i) {
                    if (strcmp(sArgv[1 + i], "fr") == 0)
                        motP[cMot1 + i] = fr;
                    else if (strcmp(sArgv[1 + i], "hs") == 0)
                        motP[cMot1 + i] = hs;
                    else if (strcmp(sArgv[1 + i], "ss") == 0)
                        motP[cMot1 + i] = ss;
                    else if (strcmp(sArgv[1 + i], "ig") == 0)
                        motP[cMot1 + i] = ig;
                    else motP[cMot1 + i] = atoi(sArgv[1 + i]);
                }
                send->fillPWMPACK(&pwm, motP[cMot1], motP[cMot2], motP[cMot3], motP[cMot4], motP[cMot5], motP[cMot6]);
                send->pSetPWM(s, &pwm);
                send->printSPIPACK(s);
            }
        }else{
            printf("!!! Comando non riconosciuto!!!\n");
            help();
        }
    }
    return 0;
}

