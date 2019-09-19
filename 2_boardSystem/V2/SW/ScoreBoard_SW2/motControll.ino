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
    pinMode(MotEn, OUTPUT);
    digitalWrite(MotEn, 1);
    setMotFreq(globSets.freq);

    //Ordine INA e INB, per avere che con valori di Vel positivi:
    //1)Una rotazione Antioraria della base
    //2)Una rotazione verso l'interno dei giunti
    //3)Gli ingranaggi del differenziale ruotino nello stesso verso e per che ruotando insieme facciano ruotare la PINZA verso l'interno
    //4)Una chiusura per la Pinza
#ifdef MOTOR_LIMIT_ENABLE
    mot[Mot1] = new DCdriverLimit(EN1, IN1A, IN1B, Mot1, &globSets, false);
    mot[Mot2] = new DCdriverLimit(EN2, IN2A, IN2B, Mot2, &globSets, true);
    mot[Mot3] = new DCdriverLimit(EN3, IN3B, IN3A, Mot3, &globSets, true);
    mot[Mot4] = new DCdriverLimit(EN4, IN4B, IN4A, Mot4, &globSets, false);
    mot[Mot5] = new DCdriverLimit(EN5, IN5A, IN5B, Mot5, &globSets, false);
    mot[Mot6] = new DCdriverLimit(EN6, IN6A, IN6B, Mot6, &globSets, true);
#else
    mot[Mot1] = new DCdriver(EN1, IN1A, IN1B);
    mot[Mot2] = new DCdriver(EN2, IN2A, IN2B);
    mot[Mot3] = new DCdriver(EN3, IN3B, IN3A);
    mot[Mot4] = new DCdriver(EN4, IN4B, IN4A);
    mot[Mot5] = new DCdriver(EN5, IN5A, IN5B);
    mot[Mot6] = new DCdriver(EN6, IN6A, IN6B);
#endif
}

void motorStateMachine() {
    for (byte i = 0; i < nMot; i++) {
        mot[i]->updateMot();
    }
}

// (10+80)*8=720 ~ 450mA di corrente media in 1 ms

#define searchVel 255
#define midVel 200
#define slowVel 150
#define waitTime 40

//int overCurrent[nMot] = { 250, 350, 350, 250, 300, 250 }; //correnti sperimentali quando è bloccato
#define antiRebound(x) delayMicroseconds(x)    //tempo anti rimbalzo
unsigned long time = 0;

void home() {
    for (byte i = Mot2; i < nMot; i++) {
        mot[i]->drive_motor(-midVel);
        delay(1000);
        mot[i]->soft_stop();
    }
    for (byte i = Mot1; i < nMot; i++)
        mot[i]->freeRun();

    /*Home del braccio*/
    homeMot(Mot2, -1);
    homeMot(Mot3, 1);
    pinzaHome();

    /*Home del braccio agane*/
    homeMot(Mot2, -1);
    homeMot(Mot3, 1);
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

//stDir: 1(outside) -1 (inside)
//switchFace: true(for Mot 1&2, switch correct face) false(for Mot 3)
//need to invert the face of MS home
void homeMot(byte motN, signed char stDir) {
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
    bool limitFound = false;
    //Loop continuo finchè non trovo lo switch la prima volta
    sFeed->updateStepEn();
    sFeed->setEn((motCode) motN, 0);
    oldEn = sFeed->getEn((motCode) motN);
    while (!(sFeed->msRead() & (1 << motN))) {
        sFeed->updateStepEn();

        //Ogni waitTime verifico se ho sbattuto a bordo pista
        //in tal caso devo andare nel senso opposto per trovare la Home
        if ((millis() > time + waitTime)) {
            //Serial.print("\t-- DELTA: ");
            //Serial.println(abs(getEn(motN) - oldEn));
            if (abs((sFeed->getEn((motCode) motN) - oldEn)) < 3) {
                //if(!limitTouch)	//cambio verso una sola volta
                stDir *= -1;
                limitFound = !limitFound;
                mot[motN]->drive_motor(stDir * searchVel);
                Serial.println("\t-- Encoder LOCK, Change Direction ");
            }
            oldEn = sFeed->getEn((motCode) motN);
            time = millis();
            //delay(100);
        }
        mot[motN]->drive_motor(stDir * searchVel);

        //Attesa per evitare false letture
        while (millis() < antiReboundTimer + 1)
            sFeed->updateStepEn();
        antiReboundTimer = millis();
    }
    if (limitFound) {    //se ho toccato sono già nel lato giusto
        Serial.println("\t--First Click after lock, switch @ inside rotation (Mot3)");
        mot[motN]->hard_stop(100);
        delay(100);
    } else {    //se non ho toccato devo spostarmi dall'altro lato e fermarmi
        Serial.println("\t--First Click before lock, switch @ outside rotation (Mot3)");
        do {    //proseguo durante al click
            mot[motN]->drive_motor(slowVel);
            antiRebound(100);    //tempo anti rimbalzo
        } while ((sFeed->msRead() & (1 << motN)));
        mot[motN]->hard_stop(100);
        delay(100);
    }
    //MIRACOLO, dopo 2h che non funzionava il pezzo sopra per il motore 3, ora funziona!!!
    /*if (switchFace) //mot1&2
    {
        if(limitFound){	//se ho toccato sono già nel lato giusto
            Serial.println("\t--First Click after lock, switch @ inside rotation");
            mot[motN]->hard_stop(100);
            delay(100);
        }
        else{	//se non ho toccato devo spostarmi dall'altro lato e fermarmi
            Serial.println("\t--First Click before lock, switch @ outside rotation");
            do {    //proseguo durante al click
                mot[motN]->drive_motor(slowVel);
                antiRebound(100);    //tempo anti rimbalzo
            }while (sFeed->msRead() & (1 << motN));
            mot[motN]->hard_stop(100);
            delay(100);
        }
    }else{	//mot3
        if(limitFound){	//se ho toccato sono già nel lato giusto
            Serial.println("\t--First Click after lock, switch @ inside rotation (Mot3)");
            mot[motN]->hard_stop(100);
            delay(100);
        }
        else{	//se non ho toccato devo spostarmi dall'altro lato e fermarmi
            Serial.println("\t--First Click before lock, switch @ outside rotation (Mot3)");
            do {    //proseguo durante al click
                mot[motN]->drive_motor(slowVel);
                antiRebound(100);    //tempo anti rimbalzo
            }while ((sFeed->msRead() & (1 << motN)));
            mot[motN]->hard_stop(100);
            delay(100);
        }
    }
     */


    //Lieve allontanamento
    Serial.println("\t--Slow Roll away");
    do {    //proseguo durante al click
        mot[motN]->drive_motor(-slowVel);
        antiRebound(100);
    } while (sFeed->msRead() & (1 << motN));
    delay(200);    //continuo poco

    //Avvicinamento lento dal lato giusto
    Serial.println("\t--Slow Approach");
    while (!(sFeed->msRead() & (1 << motN))) {    //proseguo fino al click
        mot[motN]->drive_motor(slowVel);
        antiRebound(100);
    }
    mot[motN]->hard_stop(100);
    delay(100);

    //reset degli encoder
    sFeed->updateStepEn();
    sFeed->setEn((motCode) motN, 0);
    Serial.print("\t--Mot");
    Serial.print(motN + 1);
    Serial.println(" HW Home Found\n");
}

//switch 4 pich
//switch 5 roll
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
    do {    //proseguo durante al click
        mot[Mot4]->drive_motor(-slowVel);
        mot[Mot5]->drive_motor(slowVel);
        antiRebound(100);
    } while (sFeed->msRead() & (1 << Mot5));
    delay(200);    //continuo poco

    //Avvicinamento lento dal lato giusto
    Serial.println("\t--Slow Approach");
    while (!(sFeed->msRead() & (1 << Mot5))) {    //proseguo fino al click
        mot[Mot4]->drive_motor(slowVel);
        mot[Mot5]->drive_motor(-slowVel);
        antiRebound(100);
    }
    mot[Mot4]->hard_stop(100);
    mot[Mot5]->hard_stop(100);
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
    bool limitTouch = false;
    unsigned long antiReboundTimer = 0;
    sFeed->updateStepEn();
    sFeed->setEn(Mot4, 0);
    sFeed->setEn(Mot5, 0);
    long oldEn4 = 0;
    long oldEn5 = 0;
    while (!(sFeed->msRead() & (1 << Mot4))) {
        sFeed->updateStepEn();
        //Sbattuto a bordo pista, devo andare nel senso opposto per trovare la Home
        if ((millis() > time + waitTime)) {
            if ((abs((sFeed->getEn(Mot4) - oldEn4)) < 3)
                || (abs((sFeed->getEn(Mot5) - oldEn5)) < 3)) {
                //if(!limitTouch)	//cambio verso una sola volta
                stDir *= -1;
                limitTouch = true;
                mot[Mot4]->drive_motor(stDir * searchVel);
                mot[Mot5]->drive_motor(stDir * searchVel);
                /*
                Serial.print("\t-- Encoder LOCK, Change Direction ");
                Serial.print(abs((sFeed->getEn(Mot4) - oldEn4)));
                Serial.print(" && ");
                Serial.println(abs((sFeed->getEn(Mot5) - oldEn5)));
                 */
                time = millis();
            }
            oldEn4 = sFeed->getEn(Mot4);
            oldEn5 = sFeed->getEn(Mot5);
            time = millis();
        }
        mot[Mot4]->drive_motor(stDir * searchVel);
        mot[Mot5]->drive_motor(stDir * searchVel);
        while (millis() < antiReboundTimer + 1)
            sFeed->updateStepEn();
        antiReboundTimer = millis();
    }
    if (limitTouch) {    //se ho toccato sono nel lato sbagliato
        Serial.println("\t--First Click after lock, switch @ inside rotation");
        do {    //proseguo durante al click
            mot[Mot4]->drive_motor(slowVel);
            mot[Mot5]->drive_motor(slowVel);
            antiRebound(100);    //tempo anti rimbalzo
        } while (sFeed->msRead() & (1 << Mot4));
        mot[Mot4]->hard_stop(100);
        mot[Mot5]->hard_stop(100);
        delay(100);
    } else {    //se non ho toccato il fondo sono dal lato giusto, devo fermarmi
        Serial.println("\t--First Click before lock, switch @ outside rotation");
        mot[Mot4]->hard_stop(100);
        mot[Mot5]->hard_stop(100);
        delay(100);
    }

    //Lieve allontanamento
    Serial.println("\t--Slow Roll away");
    do {    //proseguo durante al click
        mot[Mot4]->drive_motor(slowVel);
        mot[Mot5]->drive_motor(slowVel);
        antiRebound(100);
    } while (sFeed->msRead() & (1 << Mot4));
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
