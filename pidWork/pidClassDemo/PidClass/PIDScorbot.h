//
// Created by alfy on 02/05/19.
//

#ifndef PIDCLASSDEMO_PIDSCORBOT_H
#define PIDCLASSDEMO_PIDSCORBOT_H

#include <cmath>
#include <algorithm>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include "../SPILib/spi_scorebot_packdefine.h"

class PIDScorbot {
public:
    PIDScorbot(float kp, float ki, float kd, int MdeadZone, bool posDir);
    int motVal(int ref,int en);

private:
    /*pid general*/
    float Kp,Ki,Kd;
    float CONTROL_SATURATION=1.0;   //100% dell'uscita possibile
    float CONTROL_DEADZONE=0.05;    //se per muovermi devo spostarmi di meno freno
    int MOTOR_DEADZONE;
    bool posDir= false; //per allineare verso dei pwm a incremento degli encoder

    /*Variabili del pid comp*/
    int mystack[8] = {0}; //data
    int e_prev = 0;
    float x_i = 0.0;
    float y_d = 0.0;

    /*pid timing*/
    struct timeval temp;
    struct timeval oldTemp;

    float PIDComp(int error, __suseconds_t Ts);
    float UpdateSat(float x, float dx, float a, float k, float S);

protected:

};


#endif //PIDCLASSDEMO_PIDSCORBOT_H
