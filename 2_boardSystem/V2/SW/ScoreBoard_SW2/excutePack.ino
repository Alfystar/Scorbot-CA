#include "Project-lib/globalDef.h"
extern L298N *mot[nMot];

#define timeOut 2000

void excutePack(SPIPACK *p) {
	switch (p->type) {
	case PWMsend_EnRet:
	case PWMsend_CurRet:
	case PWMsend_AllRet:
		mSpeed vel;
		for (byte i = 0; i < nMot; i++) {

			int read = p->inPack.in.pack.speed.vel[Mot1 + i];
			switch (read) {
			case freeRun:
				mot[Mot1 + i]->freeRun();
				break;
			case hardStop:
				mot[Mot1 + i]->hard_stop(timeOut);
				break;
			case softStop:
				mot[Mot1 + i]->soft_stop(timeOut);
				break;
			case ignore:
				break;
			default:
				mot[Mot1 + i]->drive_motor(read, timeOut);
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
