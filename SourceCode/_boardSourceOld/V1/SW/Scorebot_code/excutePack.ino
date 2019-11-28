extern L298N *mot[nMot];
#define timeOut 2000
#define fr 300      //free running
#define hs 350      //hard stop
#define ss 400      //soft stop
#define ig 450      //ignore

void excutePack(SPIPACK *p) {
    switch (p->type) {
        case setPWM:
            for (byte i = 0; i < nMot; i++) {
                int read = p->inPack.in.pack.speed.vel[cMot1 + i];
                switch (read) {
                    case fr:
                        mot[cMot1 + i]->freeRun();
                        break;
                    case hs:
                        mot[cMot1 + i]->hard_stop(timeOut);
                        break;
                    case ss:
                        mot[cMot1 + i]->soft_stop(timeOut);
                        break;
                    case ig:
                        break;
                    default:
                        mot[cMot1 + i]->drive_motor(read, timeOut);
                        break;
                }

            }
            break;
        case setSetting:
            memorySave(&p->inPack.in.pack.prop.sets);
            break;
        case goHome:
            home();
            break;
    }
}
