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

#define searchVel 255
#define slowVel 150
//#define overCurrent 250

int overCurrent[nMot] = { 250, 350, 350, 250, 300, 250 };
#define antiRebound(x) delayMicroseconds(x)	//tempo anti rimbalzo

long time = 0;

void home() {

	/*Home del braccio*/
	homeMot(cMot2, -1, 40);
	homeMot(cMot3, 1, 80);
	pinzaHome();

	/*Home del braccio agane*/
	homeMot(cMot2, -1, 40);
	homeMot(cMot3, -1, 80);
	pinzaHome();

	/*Home Base*/
	homeMot(cMot1, 1, 40);

	/*Pinza test*/
	openClaw();
	delay(2000);
	closeClaw();

	updateStepEn();
	for (byte i = 0; i < nMot; i++) //reset degli encoder
		setEn(cMot1 + i, 0);
}

//1= anti orario
//-1= orario
void homeMot(byte motN, signed char stDir, int sleepCurrent) {
	/** Home Mot **/

	Serial.print("Searching Mot");
	Serial.print(motN + 1);
	Serial.println(" HW Home:");
	//Supera innerzia
	mot[motN]->drive_motor(stDir * searchVel);
	delay(10);

	//Cerca Home
	time = millis();
	while (!(msRead() & (1 << motN))) {
		//Sbattuto a bordo pista, devo andare nel senso opposto per trovare la Home
		if ((getSumMot(motN) > overCurrent[motN])
				&& (millis() > time + sleepCurrent)) {
			stDir *= -1;
			mot[motN]->drive_motor(stDir * searchVel);
			Serial.print("\t-- OVER CURRENT, Change Direction ");
			Serial.println(getSumMot(motN));
			time = millis();
			delay(100);
		}
		mot[motN]->drive_motor(stDir * searchVel);
		antiRebound(100);
	}

	//Posiziona a destra del riferimento
	Serial.println("\t--First Click");
	if (stDir == 1) {	//ero a sx dello switch
		while (msRead() & (1 << motN)) {	//proseguo durante al click
			mot[motN]->drive_motor(slowVel);
			delayMicroseconds(100);	//tempo anti rimbalzo
		}
	} else {			//ero a dx dello switch
		mot[motN]->hard_stop(100);
		delay(100);
	}

	//Lieve allontanamento
	Serial.println("\t--Slow Roll away");
	while (msRead() & (1 << motN)) {	//proseguo durante al click
		mot[motN]->drive_motor(slowVel);
		antiRebound(100);
	}
	delay(200);	//continuo poco

	//Avvicinamento lento dal lato giusto
	Serial.println("\t--Slow Approach");
	while (!(msRead() & (1 << motN))) {	//proseguo fino al click
		mot[motN]->drive_motor(-slowVel);
		antiRebound(100);
	}
	mot[motN]->soft_stop(100);
	delay(100);

	//reset degli encoder
	updateStepEn();
	setEn(motN, 0);
	Serial.print("\t--Mot");
	Serial.print(motN + 1);
	Serial.println(" HW Home Found\n");
}

void pinzaHome() {
	/** Roll Home**/
	Serial.println("Searching Claw Roll HW Home:");

	while (!(msRead() & (1 << cMot5))) {

		mot[cMot4]->drive_motor(searchVel);
		mot[cMot5]->drive_motor(-searchVel);
		antiRebound(100);
	}

	//Fermo
	mot[cMot4]->hard_stop(100);
	mot[cMot5]->hard_stop(100);
	delay(100);

	//Lieve allontanamento
	Serial.println("\t--Slow Roll away");
	while (msRead() & (1 << cMot5)) {	//proseguo durante al click
		mot[cMot4]->drive_motor(-slowVel);
		mot[cMot5]->drive_motor(slowVel);
		antiRebound(100);
	}
	delay(200);	//continuo poco

	//Avvicinamento lento dal lato giusto
	Serial.println("\t--Slow Approach");
	while (!(msRead() & (1 << cMot5))) {	//proseguo fino al click
		mot[cMot4]->drive_motor(slowVel);
		mot[cMot5]->drive_motor(-slowVel);
		antiRebound(100);
	}
	mot[cMot4]->soft_stop(100);
	mot[cMot5]->soft_stop(100);
	delay(100);
	Serial.println("\t--Claw Roll HW Home Found\n");

	/*#########################################################################à*/
	/*#########################################################################à*/

	/** Pitch Home **/
	signed char stDir = 1;

	Serial.println("Searching Claw Pitch HW Home:");
	mot[cMot4]->drive_motor(stDir * searchVel);
	mot[cMot5]->drive_motor(stDir * searchVel);
	delay(10);

	//Cerca Home
	time = millis();
	while (!(msRead() & (1 << cMot4))) {
		//Sbattuto a bordo pista, devo andare nel senso opposto per trovare la Home
		if ((getSumMot(cMot5) > overCurrent[cMot5]
				|| getSumMot(cMot6) > overCurrent[cMot6])
				&& (millis() > time + 30)) {
			stDir *= -1;
			mot[cMot4]->drive_motor(stDir * searchVel);
			mot[cMot5]->drive_motor(stDir * searchVel);
			Serial.print("\t-- OVER CURRENT, Change Direction ");
			Serial.print(getSumMot(cMot5));
			Serial.print(" && ");
			Serial.println(getSumMot(cMot6));
			time = millis();
			delay(100);
		}
		mot[cMot4]->drive_motor(stDir * searchVel);
		mot[cMot5]->drive_motor(stDir * searchVel);
		antiRebound(100);
	}

	//Posiziona a destra del riferimento
	Serial.println("\t--First Click");
	if (stDir == 1) {	//ero a sx dello switch
		while (msRead() & (1 << cMot4)) {	//proseguo durante al click
			mot[cMot4]->drive_motor(slowVel);
			mot[cMot5]->drive_motor(slowVel);
			delayMicroseconds(100);	//tempo anti rimbalzo
		}
	} else {			//ero a dx dello switch
		mot[cMot4]->hard_stop(100);
		mot[cMot5]->hard_stop(100);
		delay(100);
	}

	//Lieve allontanamento
	Serial.println("\t--Slow Roll away");
	while (msRead() & (1 << cMot4)) {	//proseguo durante al click
		mot[cMot4]->drive_motor(slowVel);
		mot[cMot5]->drive_motor(slowVel);
		antiRebound(100);
	}
	delay(200);	//continuo poco

	//Avvicinamento lento dal lato giusto
	Serial.println("\t--Slow Approach");
	while (!(msRead() & (1 << cMot4))) {	//proseguo fino al click
		mot[cMot4]->drive_motor(-slowVel);
		mot[cMot5]->drive_motor(-slowVel);
		antiRebound(100);
	}
	mot[cMot4]->soft_stop(100);
	mot[cMot5]->soft_stop(100);
	delay(100);
	Serial.println("\t--Claw Pitch HW Home Found\n");

	//reset degli encoder
	updateStepEn();
	setEn(cMot4, 0);
	setEn(cMot5, 0);
}

void openClaw() {
	mot[cMot6]->drive_motor(140, 2000);
}

void closeClaw() {
	mot[cMot6]->drive_motor(-140, 2000);
}
