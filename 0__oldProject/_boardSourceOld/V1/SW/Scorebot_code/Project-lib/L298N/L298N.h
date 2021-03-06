/*
 * L298N.h - Library for L298N motor driver
 Created by Yohendry Hurtado, 28 dec 2014
 Released into the public domain.

 Created on: 25 mar 2019
 *      Author: Yohendry Hurtado, ADAPTION FOR PROJECT BY ALFY
 */

#ifndef L298N_h
#define L298N_h

#include "Arduino.h"

enum {
    moving, movingTiming, H_brake, S_brake, alwaisBrake, free_Mot
};
//typedef bool (funcBool_t)(); // pointer to function with no args and bool return

class L298N {
public:
    L298N(byte ena, byte in1, byte in2);
    void updateMot();                            //no stopping Call, to update status
    //bool goHome(funcBool_t f )					//Funzione che gestrisce la home

    /*State change motor*/
    void drive_motor(int speed);
    void drive_motor(int speed, unsigned int delay_time);
    void reversDir();
    void soft_stop();
    void hard_stop(unsigned int delay_time);    //MAKE HARD STOP FOR DELAYED TIME
    void soft_stop(unsigned int delay_time);
    void freeRun();
private:
    byte in1, in2, pwm, state;
    //bool knowHome;
    int speed;
    int delay_time;
    unsigned long time;

    void clockWise();
    void anticlockwise();
    void setup_motor(int state1, int state2);

};

#ifndef __IN_ECLIPSE__

#include "L298N.cpp"

#endif
#endif
