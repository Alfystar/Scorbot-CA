/*
 * L298N.h - Library for L298N motor driver
 Created by Yohendry Hurtado, 28 dec 2014
 Released into the public domain.

 Created on: 25 mar 2019
 *      Author: Yohendry Hurtado, ADAPTION FOR PROJECT BY ALFY
 */

#ifndef DCdriver_h
#define DCdriver_h

#include "Arduino.h"
#include "../globalDef.h"
//typedef bool (funcBool_t)(); // pointer to function with no args and bool return

namespace Motor {
    using namespace DataPrimitive;
    void setMotFreq(pwmFreq freq);

    enum motState {
        moving, movingTiming, H_brake, S_brake, alwaysBrake, free_Mot
    };

    class DCdriver {
    public:
        DCdriver(byte ena, byte in1, byte in2);
        void updateMot();               //no stopping Call, to update status

        /*State change motor*/
        void drive_motor(int speed);
        void drive_motor(int speed, unsigned int delay_time);
        void reversDir();
        void soft_stop();
        void soft_stop(unsigned int delay_time);
        void hard_stop(unsigned int delay_time); //MAKE HARD STOP FOR DELAYED TIME
        void freeRun();
    protected:
        byte in1, in2, pwm;
        motState state;
        int speed;
        unsigned int delay_time;
        unsigned long time;
    private:
        void clockWise();
        void anticlockwise();
        void setup_motor(byte in1, byte in2);
    };

    class DCdriverLimit : public DCdriver {
    public:
        DCdriverLimit(byte ena, byte in1, byte in2, motCode mot,
                      settingsBoard *set, bool clockWisePos);
        void driver_motor(int speed);
        void updateMot();
    private:
        bool clockWisePos;
        bool enPosLimit = false;        //true = End clockWise rotation
        bool enNegLimit = false;    //true = End antiClockWise rotation
        settingsBoard *limitSets;
        motCode myMot;

    };
}
#ifndef __IN_ECLIPSE__

#include "DCdriver.cpp"

#endif
#endif //DCdriver_h
