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

// (10+80)*8=720 ~ 450mA di corrente media in 1 ms

void home() {
	/** Home Mot 1 **/
	signed char m1Hd = 1; //suppongo di essere acceso in una posizione tale da dover andare in senso orario per la Home

	Serial.println("Searching Mot1 HW Home:");
	while (!(msRead() & (1 << cMot1))) {
		/*
		Serial.print(getSumMot(cMot1));
		Serial.print("  ");
		Serial.println(m1Hd * 200);
		*/
		if (getSumMot(cMot1) > 250){	//ho sbattuto a bordo pista e devo andare nel senso opposto per trovare la Home
			//PARADOSSALE MA SE MESSO SI BLOCCA SU QUESTA LINEA DA CAPIRE
			//Serial.println("\t-- OVER CURRENT, Change Direction");
			m1Hd *= -1;
		}
		mot[cMot1]->drive_motor(m1Hd * 200);
	}
	Serial.println("\t--First Click");
	if (m1Hd == 1) {	//ero a sx dello switch
		while (msRead() & (1 << cMot1)) {	//proseguo durante al click
			mot[cMot1]->drive_motor(100);
		}
	} else {			//ero a dx dello switch
		mot[cMot1]->hard_stop(500);
		delay(500);	//sono in una funzione bloccante, devo attendere io esplicitamente
	}

	Serial.println("\t--Slow Roll away");
	mot[cMot1]->drive_motor(100);
	while (msRead() & (1 << cMot1)) {	//proseguo durante al click
		mot[cMot1]->drive_motor(100);
	}
	delay(100);	//continuo poco

	Serial.println("\t--Slow Approach");
	while (!(msRead() & (1 << cMot1))) {	//proseguo fino al click
		mot[cMot1]->drive_motor(-100);
	}
	mot[cMot1]->soft_stop(500);
	delay(100);
	updateStepEn();
	setEn(cMot1, 0);
	Serial.println("\t--Mot1 HW Found\n");

}
