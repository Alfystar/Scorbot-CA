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
        s.type=setPWM;
        s.out.pack.speed.vel[cMot1]+=1;
        s.out.pack.speed.vel[cMot2]+=-2;
        s.out.pack.speed.vel[cMot3]+=3;
        s.out.pack.speed.vel[cMot4]+=4;
        s.out.pack.speed.vel[cMot5]+=5;
        s.out.pack.speed.vel[cMot6]+=6;
        printf("Vel Send:\n1)%d\t2)%d\t3)%d\t4)%d\t5)%d\t6)%d\n",s.out.pack.speed.vel[cMot1],
               s.out.pack.speed.vel[cMot2],
               s.out.pack.speed.vel[cMot3],
               s.out.pack.speed.vel[cMot4],
               s.out.pack.speed.vel[cMot5],
               s.out.pack.speed.vel[cMot6]);

        send->sendPack(&s);
        printf("Encoder read:\n1)%hd\t2)%hd\t3)%hd\t4)%hd\t5)%hd\t6)%hd\n",s.in.pack.en.passi[cMot1],
               s.in.pack.en.passi[cMot2],
               s.in.pack.en.passi[cMot3],
               s.in.pack.en.passi[cMot4],
               s.in.pack.en.passi[cMot5],
               s.in.pack.en.passi[cMot6]);
        printf("-------------------------------------------------------\n");
        usleep(500000);


    }
    return 0;
}

void printSPIPACK(SPIPACK *s){
    switch(s ->type){
    case setPWM:
        printf("Pack type: setPWM");
        printf("Vel Send:\n1)%d\t2)%d\t3)%d\t4)%d\t5)%d\t6)%d\n",s->out.pack.speed.vel[cMot1],
               s->out.pack.speed.vel[cMot2],
               s->out.pack.speed.vel[cMot3],
               s->out.pack.speed.vel[cMot4],
               s->out.pack.speed.vel[cMot5],
               s->out.pack.speed.vel[cMot6]);
        printf("Encoder read:\n1)%hd\t2)%hd\t3)%hd\t4)%hd\t5)%hd\t6)%hd\n",s->in.pack.en.passi[cMot1],
               s->in.pack.en.passi[cMot2],
               s->in.pack.en.passi[cMot3],
               s->in.pack.en.passi[cMot4],
               s->in.pack.en.passi[cMot5],
               s->in.pack.en.passi[cMot6]);
        printf("-------------------------------------------------------\n");
        break;

    case getCurrent:
        printf("Sending: no parameters");
        printf("Current read:\n1)%hd\t2)%hd\t3)%hd\t4)%hd\t5)%hd\t6)%hd\n",s->in.pack.cur.current[cMot1],
               s->in.pack.cur.current[cMot2],
               s->in.pack.cur.current[cMot3],
               s->in.pack.cur.current[cMot4],
               s->in.pack.cur.current[cMot5],
               s->in.pack.cur.current[cMot6]);
               printf("-------------------------------------------------------\n");
                break;

    case getSetting:
        /*printf("Properties Send:\n1)%d\t2)%d\t3)%d\t4)%d\t5)%d\t6)%d\n",s->in.pack.prop.sets[cMot1],
               s->in.pack.prop.sets[cMot2],
               s->in.pack.prop.sets[cMot3],
               s->in.pack.prop.sets[cMot4],
               s->in.pack.prop.sets[cMot5],
               s->in.pack.prop.sets[cMot6]);
        */
        printf("Reciving: no parameters");
               printf("-------------------------------------------------------\n");
        break;
    case setSetting:
        printf("Sending: no parameters");
       /* printf("Properties read:\n1)%hd\t2)%hd\t3)%hd\t4)%hd\t5)%hd\t6)%hd\n",s->in.pack.prop.sets[cMot1],
               s->in.pack.prop.sets[cMot2],
               s->in.pack.prop.sets[cMot3],
               s->in.pack.prop.sets[cMot4],
               s->in.pack.prop.sets[cMot5],
               s->in.pack.prop.sets[cMot6]);
               */
               printf("-------------------------------------------------------\n");
        break;
    case goHome:
        printf("Sending: no parameters");
        printf("Reciving: no parameters");
        break;
    }
}
