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
#include <iostream>
#include <dataTransfert_AllInclude.h>
#include <timeSpecOp.h>
//#include "../uartSubSystem/AdapterClasses/ComUartAdapter.h"


using namespace DataPrimitive;
using namespace DataManipolation;
typedef struct data_{
    int er;     //errore dal riferimento
    long time;  //Tempo dall'ultimo campine
} data;

class PIDScorbot{
public:
    PIDScorbot (float kp, float ki, float kd, int MdeadZone);
    PIDScorbot (float kp, float ki, float kd, int MdeadZone, float cSat, float cDead);
    short motVal (int ref, int en);
    short pid (int ref, int feeback, struct timespec *dt);
private:
    /*pid general*/
    float Kp, Ki, Kd;
    float CONTROL_SATURATION;   //100% dell'uscita possibile
    float CONTROL_DEADZONE;    //se per muovermi devo spostarmi di meno freno
    int MOTOR_DEADZONE;

    /*Variabili del pid comp*/
    data mystack[8]; //data
    float x_i = 0.0;
    float y_d = 0.0;
    /*pid timing*/
    struct timespec temp, oldTemp, result;
    float PIDComp (int error, long Ts);  //Ts micro secondi
    float UpdateSat (float x, float dx, float a, float k, float s, float S);
protected:
};

#endif //PIDCLASSDEMO_PIDSCORBOT_H
