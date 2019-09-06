#include "Project-lib/globalDef.h"
extern L298N *mot[nMot];

#define timeOut 2000

void excutePack(Pack& p) {
	switch (p.getPackType()) {
	case invalid:
		break;
	case PWMsend_EnRet:
	case PWMsend_CurRet:
	case PWMsend_AllRet:
	{
		mSpeed& vel=p.getPwm();
		for (byte i = 0; i < nMot; i++) {
			switch (vel[Mot1 + i]) {
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
				mot[Mot1 + i]->drive_motor(vel[Mot1 + i], timeOut);
				break;
			}
		}
	}
	break;
	case SettingSet:
	{
		memorySave(&p.getSetting(pack4Ard));
	}
	break;
	case goHome:
	{
		home();
	}
	break;
	default:
		break;
	}
}
