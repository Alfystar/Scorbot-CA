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
            pwm.vel[cMot1]*=-1;
            pwm.vel[cMot2]*=-1;
            pwm.vel[cMot3]*=-1;
            pwm.vel[cMot4]*=-1;
            pwm.vel[cMot5]*=-1;
            pwm.vel[cMot6]*=-1;

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
            for (int i = 0; i < nMot; i++){
                prop.sets.maxCurrMed[cMot1+i]+=i;
                prop.sets.maxEn[cMot1+i]+=i*2;
                prop.sets.minEn[cMot1+i]+=i*3;
            }

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

