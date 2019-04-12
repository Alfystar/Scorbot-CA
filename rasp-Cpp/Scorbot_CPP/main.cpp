#include <iostream>
#include "spisend.h"
#include "spi_scorebot_packdefine.h"
using namespace std;

SpiSend *send;
int main()
{
    send = new SpiSend();
    SPIPACK *s;
    setPWMSend pwm;
    setSettingSend prop;
    while(1)
    {
        pwm.vel[cMot1]+=1;
        pwm.vel[cMot2]+=-2;
        pwm.vel[cMot3]+=3;
        pwm.vel[cMot4]+=1;
        pwm.vel[cMot5]+=-2;
        pwm.vel[cMot6]+=3;

        s =send->pSetPWM(&pwm);
        send->printSPIPACK(s);
        free(s);

        usleep(100000);

        s = send->pGetCurrent();
        send->printSPIPACK(s);
        free(s);
        usleep(100000);

        s = send->pGetSetting();
        send->printSPIPACK(s);
        free(s);
        usleep(100000);

        usleep(100000);

        for (int i = 0; i < nMot; i++){
            prop.sets.maxCurrMed[cMot1+i]+=i;
            prop.sets.maxEn[cMot1+i]+=i*2;
            prop.sets.minEn[cMot1+i]+=i*3;
        }

        s=send->pSetSetting(&prop);
        send->printSPIPACK(s);
        free(s);

        usleep(100000);

        s=send->pGoHome();
        send->printSPIPACK(s);
        free(s);
        usleep(100000);

    }
    return 0;
}

