#include <iostream>
#include "spisend.h"
#include "spi_scorebot_packdefine.h"
using namespace std;

SpiSend *send;
int main()
{
    send = new SpiSend();

    SPIPACK s;
    memset(&s,0,sizeof(SPIPACK));
    while(1)
    {
        s.out.type=setPWM;
        s.out.pack.speed.vel[cMot1]=255;
        s.out.pack.speed.vel[cMot2]=-255;
        s.out.pack.speed.vel[cMot3]=55;
        s.out.pack.speed.vel[cMot4]=155;
        s.out.pack.speed.vel[cMot5]=255;
        s.out.pack.speed.vel[cMot6]=65;
        /*printf("Vel Send:\n1)%d\t2)%d\t3)%d\t4)%d\t5)%d\t6)%d\n",s.out.pack.speed.vel[cMot1],
               s.out.pack.speed.vel[cMot2],
               s.out.pack.speed.vel[cMot3],
               s.out.pack.speed.vel[cMot4],
               s.out.pack.speed.vel[cMot5],
               s.out.pack.speed.vel[cMot6]);
*/
        send->sendPack(&s);
        printf("Encoder read:\n1)%hd\t2)%hd\t3)%hd\t4)%hd\t5)%hd\t6)%hd\n",s.in.pack.en.passi[cMot1],
               s.in.pack.en.passi[cMot2],
               s.in.pack.en.passi[cMot3],
               s.in.pack.en.passi[cMot4],
               s.in.pack.en.passi[cMot5],
               s.in.pack.en.passi[cMot6]);
        usleep(500000);
    }
    return 0;
}
