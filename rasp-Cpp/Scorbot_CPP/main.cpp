#include <iostream>
#include "spisend.h"
#include "spi_scorebot_packdefine.h"
using namespace std;

#define fflush(stdin) while(getchar() != '\n');

void waitEnter() {
    scanf("%[^\n]",NULL);
    fflush(stdin);
}

void help()
{
    printf("Menù di controllo TEST SPI dello scorbot:\n");
    printf("\tm -- Muove tutti i motori a caso per il timeout sulla scheda\n");
    printf("\te -- Ritorna Encoder di tutti\n");
    printf("\tc -- get current \n");
    printf("\tg -- get setting\n");
    printf("\ts -- set setting\n");
    printf("\th -- go home\n");
    printf("\t? -- visualizza l'help\n");

}

SpiSend *send;

char com[64];
int main()
{
    send = new SpiSend();
    SPIPACK *s;
    setPWMSend pwm;
    setSettingSend prop;
    int v=150;
    send->fillPWMPACK(&pwm,v,-v,v,-v,v,-v);
    pwm.vel[cMot1]=v;
    pwm.vel[cMot2]=-v;
    pwm.vel[cMot3]=v;
    pwm.vel[cMot4]=-v;
    pwm.vel[cMot5]=v;
    pwm.vel[cMot6]=-v;
    help();
    printf("Start loop\n");
    while(1)
    {
        printf("\n>> ");
        scanf("%s",com);
        fflush(stdin);
        if(strcmp(com,"m")==0)
        {
            v*=-1;
            send->fillPWMPACK(&pwm,v,-v,v,-v,v,-v);
            s =send->pSetPWM(&pwm);
            send->printSPIPACK(s);
            free(s);
        }
        if(strcmp(com,"e")==0)
        {
            send->fillPWMPACK(&pwm,ig,ig,ig,ig,ig,ig);
            s =send->pSetPWM(&pwm);
            send->printSPIPACK(s);
            free(s);
        }
        if(strcmp(com,"c")==0)
        {
            s = send->pGetCurrent();
            send->printSPIPACK(s);
            free(s);
        }
        if(strcmp(com,"g")==0)
        {
            s = send->pGetSetting();
            send->printSPIPACK(s);
            free(s);
        }
        if(strcmp(com,"s")==0)
        {
            /*for (int i = 0; i < nMot; i++){
                prop.sets.maxCurrMed[cMot1+i]+=i;
                prop.sets.maxEn[cMot1+i]+=i*2;
                prop.sets.minEn[cMot1+i]+=i*3;
            }*/
            /*Assegnazione limiti scoperti sperimentalmente*/
            prop.sets.maxCurrMed[cMot1]=270; //250
            prop.sets.maxEn[cMot1]=24300; //24379
            prop.sets.minEn[cMot1]=-19450; //-19509

            prop.sets.maxCurrMed[cMot2]=370; //350
            prop.sets.maxEn[cMot2]=16200; //16229
            prop.sets.minEn[cMot2]=-1000; //-1110

            prop.sets.maxCurrMed[cMot3]=370; //350
            prop.sets.maxEn[cMot3]=21900; //21960
            prop.sets.minEn[cMot3]=-7300; //-7344

            /********************************************
             * Dipende da rotazione il numero di encoder, lo lasciamo
             * apposta molto grande per non far interferire
             */
            prop.sets.maxCurrMed[cMot4]=270; //250
            prop.sets.maxEn[cMot4]=10000; //NA
            prop.sets.minEn[cMot4]=-10000; //NA

            prop.sets.maxCurrMed[cMot5]=300; //250
            prop.sets.maxEn[cMot5]=10000; //NA
            prop.sets.minEn[cMot5]=-10000; //NA
            /********************************************/

            /*La pinza al contrario vogliamo che si possa aprire tuttu*/
            prop.sets.maxCurrMed[cMot6]=270; //250
            prop.sets.maxEn[cMot6]=5770; //5749
            prop.sets.minEn[cMot6]=-10; //0


            s=send->pSetSetting(&prop);
            send->printSPIPACK(s);
            free(s);
        }
        if(strcmp(com,"h")==0)
        {
            s=send->pGoHome();
            send->printSPIPACK(s);
            free(s);
        }
        if(strcmp(com,"?")==0)
        {
            help();
        }
    }
    return 0;
}

