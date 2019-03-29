#include <iostream>
#include "spisend.h"
#include "spi_scorebot_packdefine.h"
using namespace std;

SpiSend *send;
int main()
{
    send = new SpiSend();

    SPIPACK s;
    s.out.type=setPWM;
    s.out.pack.speed.pwm[cMot1]=255;
    s.out.pack.speed.pwm[cMot2]=-255;
    s.out.pack.speed.pwm[cMot3]=55;
    s.out.pack.speed.pwm[cMot4]=155;
    s.out.pack.speed.pwm[cMot5]=255;
    s.out.pack.speed.pwm[cMot6]=65;
    printf("Vel Send: 1)%d 2)%d 3)%d 4%d 5)%d 6)%d\n",s.out.pack.speed.pwm[cMot1],
           s.out.pack.speed.pwm[cMot2],
           s.out.pack.speed.pwm[cMot3],
           s.out.pack.speed.pwm[cMot4],
           s.out.pack.speed.pwm[cMot5],
           s.out.pack.speed.pwm[cMot6]);
    while(1)
    {
        send->sendPack(&s);
        printf("Encoder read: 1)%d 2)%d 3)%d 4%d 5)%d 6)%d\n",s.in.pack.en.passi[cMot1],
               s.in.pack.en.passi[cMot2],
               s.in.pack.en.passi[cMot3],
               s.in.pack.en.passi[cMot4],
               s.in.pack.en.passi[cMot5],
               s.in.pack.en.passi[cMot6]);
        usleep(100000);
    }
    return 0;
}
