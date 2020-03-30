#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2019-09-23 16:25:20

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

void setup() ;
void loop() ;
void sanityChek(int wait) ;
ISR(SPI_STC_vect) ;
ISR(ADC_vect) ;
ISR(TIMER5_OVF_vect);
ISR(PCINT0_vect) ;
void excutePack(Pack &p) ;
void memoryLoad() ;
void memorySave(settingsBoard &set) ;
void motSetup() ;
void motorStateMachine() ;
void home() ;
void homeMot(byte motN, signed char stDir) ;
void pinzaHome() ;
void openClaw() ;
void closeClaw() ;
void stopClaw() ;

#include "ScoreBoard_SW2.ino"

#include "excutePack.ino"
#include "memoriLoad.ino"
#include "motControll.ino"

#endif
