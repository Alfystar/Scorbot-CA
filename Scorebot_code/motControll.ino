/*
 * motControll.ino
 *
 *  Created on: 26 mar 2019
 *      Author: alfy
 */
#include "Project-lib/L298N/L298N.h"
#include "Project-lib/globalDef.h"
#include "Project-lib/msEnlib/msEnlib.h"

extern L298N *mot[nMot];

void motSetup() {
	/*Ordine INA e INB, per avere una rotazione oraria quando il braccio è in piano con la pinza a SINISTRA*/
	mot[0] = new L298N(EN1, IN1A, IN1B);
	mot[1] = new L298N(EN2, IN2A, IN2B);
	mot[2] = new L298N(EN3, IN3B, IN3A);
	mot[3] = new L298N(EN4, IN4B, IN4A);
	mot[4] = new L298N(EN5, IN5A, IN5B);
	mot[5] = new L298N(EN6, IN6A, IN6B);
}

void motorStateMachine() {
	for (byte i = 0; i < nMot; i++) {
		mot[i]->updateMot();
	}
}

//todo Capire perchè non funziona!!!!!!
void home() {
	/** Home Mot 1 **/
	while (!msRead() & (1 << cMot1)) {
		mot[cMot1]->drive_motor(-200);
	}
	mot[cMot1]->hard_stop(500);
	delay(500);	//sono in una funzione bloccante, devo attendere io a mano
	while (msRead() & (1 << cMot1)) {
		mot[cMot1]->drive_motor(100);
	}
	mot[cMot1]->soft_stop(500);
	setEn(cMot1,0);


}
