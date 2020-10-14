#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2020-10-14 19:20:04

#include "Arduino.h"
#include "Arduino.h"
#include "Project-lib/globalDef.h"
#include "Project-lib/globalDef.h"
#include "Project-lib/Motor/DCdriver.h"
#include "EEPROM.h"
#include "Project-lib/globalDef.h"
#include "Project-lib/globalDef.h"
#include "Project-lib/msEnlib/msEnlib.h"
#include "Project-lib/Motor/DCdriver.h"
#include "Arduino.h"

void setup ();
void loop ();
ISR(ADC_vect) ;
ISR(TIMER5_OVF_vect) ;
ISR(PCINT0_vect) ;
void excutePack (uart2Ard &p);
void initDataSend ();
void dataSend ();
void memoryLoad ();
void memorySave (settingsBoard &set);
bool motorLock (motCode mot, short old);
bool clawLock (short oldEn4, short oldEn5);
void motSetup ();
void motorStateMachine ();
void home ();
void homeMot (motCode motN, signed char stDir, bool counterClockWise);
void pinzaHome ();
void rollHome ();
void pitchHome ();
void openClaw ();
void closeClaw ();
void stopClaw ();
void sanityChek (int wait);


#include "ScoreBoard_Uart.ino"
#include "excutePack.ino"
#include "memoriLoad.ino"
#include "motControll.ino"
#include "sanityCheck.ino"

#endif
