/*
 * motControll.ino
 *
 *  Created on: 26 mar 2019
 *      Author: alfy
 */
#include "Project-lib/globalDef.h"
#include "Project-lib/msEnlib/msEnlib.h"
#include "Project-lib/Motor/DCdriver.h"

using namespace Motor;
extern DCdriverLimit *mot[nMot];

#define searchVel 255
#define midVel 180
#define slowVel 150
#define waitTime 40

// <== Logical MACRO and Function for this File ==>
#define antiRebound(x) delayMicroseconds(x)    //tempo anti rimbalzo

#define lockMargin 25

bool motorLock (motCode mot, short old){
    sFeed->updateStepEn();
    return abs((sFeed->getEn(mot) - old)) < lockMargin;
}

#define oldUpdate(mot, old)                        \
            sFeed->updateStepEn();                \
            old = sFeed->getEn((motCode)mot)

bool clawLock (short oldEn4, short oldEn5){
    \
        sFeed->updateStepEn();
    return ((abs((sFeed->getEn(Mot4) - oldEn4)) < lockMargin)                                \
 || (abs((sFeed->getEn(Mot5) - oldEn5)) < lockMargin));
}

#define oldClawUpdate(oldEn4, oldEn5)            \
            sFeed->updateStepEn();                \
            oldEn4 = sFeed->getEn(Mot4);        \
            oldEn5 = sFeed->getEn(Mot5)

// <======= Motor Move =======>
// The delay Avoid Hysteresis time
#define hysteresiMove(pwm) \
        mot[motN]->drive_motor(pwm);    \
        delay(1)

#define roll(pwm) \
        mot[Mot4]->drive_motor(pwm);    \
        mot[Mot5]->drive_motor(pwm);    \
        delay(1)

// >0 Move to inside (Claw Down)
#define pitch(pwm) \
        mot[Mot4]->drive_motor(-pwm);    \
        mot[Mot5]->drive_motor(pwm);    \
        delay(1)

#define clawStop() \
        mot[Mot4]->hard_stop(100); \
        mot[Mot5]->hard_stop(100); \
        delay(100)

// <======= Switch Click =======>
#define switchClick() \
        (sFeed->msRead() & (1 << motN))        //Switch in pull-up => 1=NotClick

//switch 5 roll
#define rollSwitch() \
        (sFeed->msRead() & (1 << Mot5))    //Logic 1-Hot (1=premuto)
//switch 4 pitch
#define pitchSwitch() \
        (sFeed->msRead() & (1 << Mot4))    //Logic 1-Hot (1=premuto)

void motSetup (){
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
    mot[Mot3] = new DCdriverLimit(EN3, IN3A, IN3B, Mot3, &globSets, true);
    mot[Mot4] = new DCdriverLimit(EN4, IN4A, IN4B, Mot4, &globSets, false);
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

void motorStateMachine (){
    for (byte i = 0; i < nMot; i++){
        mot[i]->updateMot();
    }
}

void home (){
    #ifdef HOME_DB
    Db.println("Moving in secure zone");
    #endif

    mot[Mot2]->drive_motor(midVel);
    delay(1000);
    mot[Mot2]->soft_stop();

    for (byte i = Mot1; i < nMot; i++){
        mot[Mot1 + i]->freeRun();
    }

    #ifdef HOME_DB
    Db.println("Homming Procedure Start");
    #endif
    /*Home del braccio*/
    homeMot(Mot2, -1, true);
    homeMot(Mot3, -1, false);
    pinzaHome();

    // <== Home del braccio agane ==>
    homeMot(Mot2, -1, true);
    homeMot(Mot3, -1, false);
    pinzaHome();

    // <== Home Base ==>
    homeMot(Mot1, -1, true);

    /*Pinza test*/
    closeClaw();
    delay(2000);
    openClaw();
    delay(2000);
    stopClaw();
    delay(10);

    for (byte i = Mot1; i < nMot; i++)
        mot[i]->freeRun();

    sFeed->updateStepEn();
    for (byte i = Mot1; i < nMot; i++) //reset degli encoder
        sFeed->setEn((motCode) (i), 0);
}

// counterClockWise: positive PWM make counterClockWise rotation?
// stDir: 1(outside) -1 (inside)
// switchFace: true(for Mot 1&2, switch correct face) false(for Mot 3)
// need to invert the face of MS home
void homeMot (motCode motN, signed char stDir, bool counterClockWise){
    bool limitFound = false;
    signed char sign = stDir * (counterClockWise * 2 - 1);// 1 Antiorario, -1 orario

    sFeed->updateStepEn();
    sFeed->setEn((motCode) motN, 0);
    short oldEn = sFeed->getEn((motCode) motN);


    // <== Home Mot ==>
    #ifdef HOME_DB
    Db.print("Searching Mot");
    Db.print(motN + 1);
    Db.println(" HW_Source Home:");
    #endif

    // Search Switch
    unsigned long timeHome = millis();
    while (!switchClick()){ // Until find the switch first time
        //sFeed->updateStepEn();
        hysteresiMove(sign * searchVel);
        //Every waitTime check limit switch
        //If true invert rotation to find Home
        if ((millis() > timeHome + waitTime)){
            if (motorLock(motN, oldEn)){
                sign *= -1;
                limitFound = true;
                hysteresiMove(sign * searchVel);
                #ifdef HOME_DB
                Db.println("\t-- Encoder LOCK, Change Direction ");
                #endif
            }
            oldUpdate(motN, oldEn);
            timeHome = millis();
        }
    }

    // Se tocco lo switch DOPO di essermi bloccato:
    if (!limitFound){
        #ifdef HOME_DB
        Db.println("\t--First Click before lock, switch @ outside rotation");
        #endif
        mot[motN]->hard_stop(100);
        delay(100);
    }
    else{        // Home found
        #ifdef HOME_DB
        Db.println("\t--First Click after lock, switch @ inside rotation");
        #endif
        do{    // Continue during click
            hysteresiMove(sign * slowVel);
        }while (switchClick());
        mot[motN]->hard_stop(100);
        delay(100);
    }

    // Little separation
    #ifdef HOME_DB
    Db.println("\t--Slow Roll away");
    #endif
    do{    // Continue during click
        hysteresiMove(sign * (-slowVel));
    }while (switchClick());
    delay(200);    // Continue little bit

    // Slow rendezvous in right side
    #ifdef HOME_DB
    Db.println("\t--Slow Approach");
    #endif
    while (!switchClick()){    // Continue until click
        hysteresiMove(sign * slowVel);
    }
    mot[motN]->hard_stop(100);
    delay(100);

    // <== Encoder Reset ==>
    sFeed->updateStepEn();
    sFeed->setEn((motCode) motN, 0);
    #ifdef HOME_DB
    Db.print("\t--Mot");
    Db.print(motN + 1);
    Db.println(" HW_Source Home Found\n");
    #endif
}

// <========================================================>

//switch 4 pitch
//switch 5 roll

void pinzaHome (){
    pitchHome();
    rollHome();

    //reset degli encoder
    sFeed->updateStepEn();
    sFeed->setEn(Mot4, 0);
    sFeed->setEn(Mot5, 0);
}

void rollHome (){
    // <== Roll Home ==>
    #ifdef HOME_DB
    Db.println("Searching Claw Roll HW_Source Home:");
    #endif

    while (!rollSwitch()){
        roll(-searchVel);
    }

    //Fermo
    clawStop();

    //Lieve allontanamento
    #ifdef HOME_DB
    Db.println("\t--Slow Roll away");
    #endif
    do{    //proseguo durante al click
        roll(slowVel);
    }while (rollSwitch());
    delay(200);    //continuo poco per mettermi circa al centro

    //Avvicinamento lento dal lato giusto
    #ifdef HOME_DB
    Db.println("\t--Slow Approach");
    #endif
    while (!rollSwitch()){    //proseguo fino al click
        roll(-slowVel);
    }
    clawStop();
    roll(slowVel); //Sposto poco per mettermi circa al centro
    delay(200);
    clawStop();

    #ifdef HOME_DB
    Db.println("\t--Claw Roll HW_Source Home Found\n");
    #endif
}

void pitchHome (){
    // <== Pitch Home ==>
    signed char stDir = 1;
    bool limitTouch = false;

    sFeed->updateStepEn();
    sFeed->setEn(Mot4, 0);
    sFeed->setEn(Mot5, 0);
    short oldEn4 = sFeed->getEn(Mot4);
    short oldEn5 = sFeed->getEn(Mot5);

    #ifdef HOME_DB
    Db.println("Searching Claw Pitch HW_Source Home:");
    #endif

    pitch(stDir * searchVel);

    //Cerca Home
    oldClawUpdate(oldEn4, oldEn5);
    unsigned long timeHome = millis();
    while (!pitchSwitch()){
        sFeed->updateStepEn();
        //Sbattuto a bordo pista, devo andare nel senso opposto per trovare la Home
        if ((millis() > timeHome + waitTime)){
            if (clawLock(oldEn4, oldEn5)){
                stDir *= -1;
                limitTouch = true;
                pitch(stDir * searchVel);
                #ifdef HOME_DB
                Db.println("\t-- Encoder LOCK, Change Direction ");
                #endif
            }
            oldClawUpdate(oldEn4, oldEn5);
            timeHome = millis();
        }
    }

    if (!limitTouch){    //se non ho toccato sono nel lato sbagliato
        #ifdef HOME_DB
        Db.println("\t--First Click before lock, switch @ outside rotation");
        #endif
        do{    //proseguo durante al click
            pitch(stDir * slowVel);
        }while (pitchSwitch());
        mot[Mot4]->hard_stop(100);
        mot[Mot5]->hard_stop(100);
        delay(100);
    }
    else{    //se ho toccato il bordo sono nel lato giusto, devo fermarmi
        #ifdef HOME_DB
        Db.println("\t--First Click after lock, switch @ inside rotation");
        #endif
        clawStop();
    }

    // <==== Arrivato qui devo puntare più verso la base ====>

    //Lieve allontanamento
    #ifdef HOME_DB
    Db.println("\t--Slow Roll away");
    #endif
    do{    //proseguo durante al click
        pitch(slowVel);
    }while (sFeed->msRead() & (1 << Mot4));
    delay(200);    //continuo poco

    //Avvicinamento lento dal lato giusto
    #ifdef HOME_DB
    Db.println("\t--Slow Approach");
    #endif
    while (!(sFeed->msRead() & (1 << Mot4))){    //proseguo fino al click
        pitch(-slowVel);
    }
    clawStop();
    #ifdef HOME_DB
    Db.println("\t--Claw Pitch HW_Source Home Found\n");
    #endif
}

void openClaw (){
    #ifdef HOME_DB
    Db.println("Opening claw...");
    #endif
    mot[Mot6]->drive_motor(-140, 2000);
}

void closeClaw (){
    #ifdef HOME_DB
    Db.println("Closing claw...");
    #endif
    mot[Mot6]->drive_motor(140, 2000);
}

void stopClaw (){
    #ifdef HOME_DB
    Db.println("Stopping claw...");
    #endif
    mot[Mot6]->soft_stop(2000);
}
