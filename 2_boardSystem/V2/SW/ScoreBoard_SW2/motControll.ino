/*
 * motControll.ino
 *
 *  Created on: 26 mar 2019
 *      Author: alfy
 */
#include "Project-lib/globalDef.h"
#include "Project-lib/msEnlib/msEnlib.h"
#include "Project-lib/Motor/DCdriver.h"

extern DCdriverLimit *mot[nMot];

void motSetup() {
    setMotFreq(globSets.freq);
    //TODO: verificare sia vero quando scritto sotto
    //Ordine INA e INB, per avere una rotazione oraria
    //guardando il braccio di profilo con la pinza a SINISTRA
    //TODO: aggiungere il corretto parametro clockpos
    mot[Mot1] = new DCdriverLimit(EN1, IN1A, IN1B, Mot1, globSets, true);
    mot[Mot2] = new DCdriverLimit(EN2, IN2A, IN2B, Mot2, globSets, true);
    mot[Mot3] = new DCdriverLimit(EN3, IN3B, IN3A, Mot3, globSets, true);
    mot[Mot4] = new DCdriverLimit(EN4, IN4B, IN4A, Mot4, globSets, true);
    mot[Mot5] = new DCdriverLimit(EN5, IN5A, IN5B, Mot5, globSets, true);
    mot[Mot6] = new DCdriverLimit(EN6, IN6A, IN6B, Mot6, globSets, true);
    /*
     mot[Mot1] = new DCdriver(EN1, IN1A, IN1B);
     mot[Mot2] = new DCdriver(EN2, IN2A, IN2B);
     mot[Mot3] = new DCdriver(EN3, IN3B, IN3A);
     mot[Mot4] = new DCdriver(EN4, IN4B, IN4A);
     mot[Mot5] = new DCdriver(EN5, IN5A, IN5B);
     mot[Mot6] = new DCdriver(EN6, IN6A, IN6B);
     */
}

void setMotFreq(pwmFreq freq) {
    switch (freq) {
        case hz30:
            TCCR3B = (TCCR3B & B11111000) | B00000101; // set timer 3 divisor to  1024 for PWM frequency of    30.64 Hz
            TCCR4B = (TCCR4B & B11111000) | B00000101; // set timer 4 divisor to  1024 for PWM frequency of    30.64 Hz
            break;
        case hz120:
            TCCR3B = (TCCR3B & B11111000) | B00000100; // set timer 3 divisor to   256 for PWM frequency of   122.55 Hz
            TCCR4B = (TCCR4B & B11111000) | B00000100; // set timer 4 divisor to   256 for PWM frequency of   122.55 Hz
            break;
        case hz490:
            TCCR3B = (TCCR3B & B11111000) | B00000011; // set timer 3 divisor to    64 for PWM frequency of   490.20 Hz
            TCCR4B = (TCCR4B & B11111000) | B00000011; // set timer 4 divisor to    64 for PWM frequency of   490.20 Hz
            break;
        case hz4k:
            TCCR3B = (TCCR3B & B11111000) | B00000010; // set timer 3 divisor to     8 for PWM frequency of  3921.16 Hz
            TCCR4B = (TCCR4B & B11111000) | B00000010; // set timer 4 divisor to     8 for PWM frequency of  3921.16 Hz
            break;
        case hz30k:
            TCCR3B = (TCCR3B & B11111000) | B00000001; // set timer 3 divisor to     1 for PWM frequency of 31372.55 Hz
            TCCR4B = (TCCR4B & B11111000) | B00000001; // set timer 4 divisor to     1 for PWM frequency of 31372.55 Hz
            break;
    }
}

void motorStateMachine() {
    for (byte i = 0; i < nMot; i++) {
        mot[i]->updateMot();
    }
}

// (10+80)*8=720 ~ 450mA di corrente media in 1 ms

#define searchVel 255
#define slowVel 150
#define waitTime 40

//int overCurrent[nMot] = { 250, 350, 350, 250, 300, 250 }; //correnti sperimentali quando è bloccato
#define antiRebound(x) delayMicroseconds(x)    //tempo anti rimbalzo
unsigned long time = 0;

void home() {
    for (byte i = 0; i < nMot; i++)
        mot[Mot1 + i]->freeRun();

    /*Home del braccio*/
    homeMot(Mot2, -1);
    homeMot(Mot3, -1);
    pinzaHome();

    /*Home del braccio agane*/
    homeMot(Mot2, -1);
    homeMot(Mot3, -1);
    pinzaHome();

    /*Home Base*/
    homeMot(Mot1, -1);

    /*Pinza test*/
    closeClaw();
    delay(2000);
    openClaw();
    delay(2000);
    stopClaw();
    delay(10);
    sFeed->updateStepEn();
    for (byte i = 0; i < nMot; i++) //reset degli encoder
        sFeed->setEn((motCode)(Mot1 + i), 0);
}

//1= anti orario
//-1= orario
void homeMot(byte motN, signed char stDir) {
    signed char stDirStart = stDir;
    sFeed->updateStepEn();
    sFeed->setEn((motCode) motN, 0);

    /** Home Mot **/

    Serial.print("Searching Mot");
    Serial.print(motN + 1);
    Serial.println(" HW Home:");
    //Supera innerzia
    mot[motN]->drive_motor(stDir * searchVel);
    delay(10);

    //Cerca Home
    time = millis();
    long oldEn = 0;
    unsigned long antiReboundTimer = 0;
    while (!(sFeed->msRead() & (1 << motN))) {
        sFeed->updateStepEn();
        //Sbattuto a bordo pista, devo andare nel senso opposto per trovare la Home
        if ((millis() > time + waitTime)) {
            //Serial.print("\t-- DELTA: ");
            //Serial.println(abs(getEn(motN) - oldEn));
            if (abs((sFeed->getEn((motCode) motN) - oldEn)) < 3) {
                stDir *= -1;
                mot[motN]->drive_motor(stDir * searchVel);
                Serial.println("\t-- Encoder LOCK, Change Direction ");
            }
            oldEn = sFeed->getEn((motCode) motN);
            time = millis();
            //delay(100);
        }
        mot[motN]->drive_motor(stDir * searchVel);
        while (micros() < antiReboundTimer + waitTime)
            sFeed->updateStepEn();
        antiReboundTimer = micros();
        //antiRebound(100);
    }

    //Posiziona a destra del riferimento
    Serial.println("\t--First Click");
    if (stDir == stDirStart) {    //ero a sx dello switch
        while (sFeed->msRead() & (1 << motN)) {    //proseguo durante al click
            mot[motN]->drive_motor(slowVel);
            delayMicroseconds(100);    //tempo anti rimbalzo
        }
    } else {            //ero a dx dello switch
        mot[motN]->hard_stop(100);
        delay(100);
    }

    //Lieve allontanamento
    Serial.println("\t--Slow Roll away");
    while (sFeed->msRead() & (1 << motN)) {    //proseguo durante al click
        mot[motN]->drive_motor(slowVel);
        antiRebound(100);
    }
    delay(200);    //continuo poco

    //Avvicinamento lento dal lato giusto
    Serial.println("\t--Slow Approach");
    while (!(sFeed->msRead() & (1 << motN))) {    //proseguo fino al click
        mot[motN]->drive_motor(-slowVel);
        antiRebound(100);
    }
    mot[motN]->soft_stop(100);
    delay(100);

    //reset degli encoder
    sFeed->updateStepEn();
    sFeed->setEn((motCode) motN, 0);
    Serial.print("\t--Mot");
    Serial.print(motN + 1);
    Serial.println(" HW Home Found\n");
}

void pinzaHome() {
    /** Roll Home**/
    Serial.println("Searching Claw Roll HW Home:");
    while (!(sFeed->msRead() & (1 << Mot5))) {
        mot[Mot4]->drive_motor(searchVel);
        mot[Mot5]->drive_motor(-searchVel);
        antiRebound(100);
    }

    //Fermo
    mot[Mot4]->hard_stop(100);
    mot[Mot5]->hard_stop(100);
    delay(100);

    //Lieve allontanamento
    Serial.println("\t--Slow Roll away");
    while (sFeed->msRead() & (1 << Mot5)) {    //proseguo durante al click
        mot[Mot4]->drive_motor(-slowVel);
        mot[Mot5]->drive_motor(slowVel);
        antiRebound(100);
    }
    delay(200);    //continuo poco

    //Avvicinamento lento dal lato giusto
    Serial.println("\t--Slow Approach");
    while (!(sFeed->msRead() & (1 << Mot5))) {    //proseguo fino al click
        mot[Mot4]->drive_motor(slowVel);
        mot[Mot5]->drive_motor(-slowVel);
        antiRebound(100);
    }
    mot[Mot4]->soft_stop(100);
    mot[Mot5]->soft_stop(100);
    delay(100);
    Serial.println("\t--Claw Roll HW Home Found\n");

    /*#########################################################################à*/
    /*#########################################################################à*/

    /** Pitch Home **/
    signed char stDir = -1;
    Serial.println("Searching Claw Pitch HW Home:");
    mot[Mot4]->drive_motor(stDir * searchVel);
    mot[Mot5]->drive_motor(stDir * searchVel);
    delay(10);

    //Cerca Home
    time = millis();
    long oldEn4 = 0;
    long oldEn5 = 0;
    unsigned long antiReboundTimer = 0;
    while (!(sFeed->msRead() & (1 << Mot4))) {
        sFeed->updateStepEn();
        //Sbattuto a bordo pista, devo andare nel senso opposto per trovare la Home
        if ((millis() > time + waitTime)) {
            if ((abs((sFeed->getEn(Mot4) - oldEn4)) < 3)
                && (abs((sFeed->getEn(Mot5) - oldEn5)) < 3)) {
                stDir *= -1;
                mot[Mot4]->drive_motor(stDir * searchVel);
                mot[Mot5]->drive_motor(stDir * searchVel);
                Serial.print("\t-- Encoder LOCK, Change Direction ");
                Serial.print(abs((sFeed->getEn(Mot4) - oldEn4)));
                Serial.print(" && ");
                Serial.println(abs((sFeed->getEn(Mot5) - oldEn5)));
                time = millis();
            }
            oldEn4 = sFeed->getEn(Mot4);
            oldEn5 = sFeed->getEn(Mot5);
            time = millis();
        }
        mot[Mot4]->drive_motor(stDir * searchVel);
        mot[Mot5]->drive_motor(stDir * searchVel);
        while (micros() < antiReboundTimer + 100)
            sFeed->updateStepEn();
        antiReboundTimer = micros();
    }

    //Posiziona a destra del riferimento
    Serial.println("\t--First Click");
    if (stDir == 1) {    //ero a sx dello switch
        while (sFeed->msRead() & (1 << Mot4)) {    //proseguo durante al click
            mot[Mot4]->drive_motor(slowVel);
            mot[Mot5]->drive_motor(slowVel);
            delayMicroseconds(100);    //tempo anti rimbalzo
        }
    } else {            //ero a dx dello switch
        mot[Mot4]->hard_stop(100);
        mot[Mot5]->hard_stop(100);
        delay(100);
    }

    //Lieve allontanamento
    Serial.println("\t--Slow Roll away");
    while (sFeed->msRead() & (1 << Mot4)) {    //proseguo durante al click
        mot[Mot4]->drive_motor(slowVel);
        mot[Mot5]->drive_motor(slowVel);
        antiRebound(100);
    }
    delay(200);    //continuo poco

    //Avvicinamento lento dal lato giusto
    Serial.println("\t--Slow Approach");
    while (!(sFeed->msRead() & (1 << Mot4))) {    //proseguo fino al click
        mot[Mot4]->drive_motor(-slowVel);
        mot[Mot5]->drive_motor(-slowVel);
        antiRebound(100);
    }
    mot[Mot4]->soft_stop(100);
    mot[Mot5]->soft_stop(100);
    delay(100);
    Serial.println("\t--Claw Pitch HW Home Found\n");

    //reset degli encoder
    sFeed->updateStepEn();
    sFeed->setEn(Mot4, 0);
    sFeed->setEn(Mot5, 0);
}

void openClaw() {
    mot[Mot6]->drive_motor(-140, 2000);
}

void closeClaw() {
    mot[Mot6]->drive_motor(140, 2000);
}

void stopClaw() {
    mot[Mot6]->soft_stop(2000);
}
