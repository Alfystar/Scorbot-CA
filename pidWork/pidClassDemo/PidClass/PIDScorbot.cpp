//
// Created by alfy on 02/05/19.
//

#include "PIDScorbot.h"

PIDScorbot::PIDScorbot(float kp, float ki, float kd, int MdeadZone, bool posDir)
{
    /*pid general*/
    this->Kp=kp;
    this->Ki=ki;
    this->Kd=kd;
    this->MOTOR_DEADZONE=MdeadZone;
    this->posDir=posDir;

    this->CONTROL_SATURATION=1.0;   //100% dell'uscita possibile
    this->CONTROL_DEADZONE=0.05;    //se per muovermi devo spostarmi di meno freno

    /*Variabili del pid comp*/
    memset(this->mystack,0, sizeof((this->mystack[0]))*8);
    this->e_prev = 0;
    this->x_i = 0.0;
    this->y_d = 0.0;

    /*pid relativi*/
    gettimeofday(&this->temp,NULL);
    gettimeofday(&this->oldTemp,NULL);

}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int PIDScorbot::motVal(int ref,int en)
{

    this->oldTemp=this->temp;

    gettimeofday(&this->temp,NULL);

    //Serial.print(temp1);Serial.print("    ");

    int er = ref - en;
    float vOut=this->PIDComp(er,this->temp.tv_usec-this->oldTemp.tv_usec);

    vOut*=1-(2*this->posDir);   //per allineare verso dei pwm a incremento degli encoder

    if(fabsf(vOut)<this->CONTROL_DEADZONE)
    {
        return ss; //soft stop
    }else{
        if(vOut>0) return int(0.5+fmap(vOut,0.0,1.0,this->MOTOR_DEADZONE,255));
        else return int(0.5-fmap(vOut,0.0,-1.0,-this->MOTOR_DEADZONE,-255));
    }
}



float PIDScorbot::UpdateSat(float x, float dx, float a, float k, float S)
{
    /* Evaluate the suitable increment dxsat from dx of a variable x such that
      % the saturation constraint |a+k(x+dxsat)| <= S is as much as possibile satisfied
      % with |dxsat| <= |dx| and dxsat*dx>=0.
      % x: the variable to be updated
      % dx: the incremental value for x
      % a,k and S: the parameter of the saturation function |a+k(x+dxsat)| <= S
    */

    float xhat = x + dx;
    float temp = S - fabsf(a + k * xhat);

    if (temp <= 0)
    {
        if (fabsf(a + k * xhat) < fabsf(a + k * x))
        {
            return (dx);
        }
        else return ((dx >= 0 ? 1 : -1) * fmaxf(0, (S - fabsf(a + k * x)) / k));
    }
    else  return (dx);

}


float PIDScorbot::PIDComp(int error, __suseconds_t Ts)
{
    /*Il pid calcola un valore in uscita tra -1.0 e 1.0 che è -100% to 100% della pot di uscita del motore*/
    //TS tempo campione in micro secondi

    //stack update, the higher the newer
    for (short int i = 0; i < 7; i++) {
        this->mystack[i] = this->mystack[i + 1];
    }
    this->mystack[7] = error;
    //7 è la distanza tra i 2 campioni
    this->y_d = this->Kd * (this->mystack[7] - this->mystack[0]) / (7 * Ts);
    this->x_i = this->x_i + this->UpdateSat(this->x_i, this->Ki * Ts * this->e_prev, this->Kp * error + this->y_d, 1, this->CONTROL_SATURATION);
    this->e_prev = error;
    //   Serial.print("x_i = ");
    //   Serial.print(x_i);
    //   Serial.print(", x_d = ");
    //   Serial.print(y_d);
    //   Serial.print(", error = ");
    //   Serial.print(error);
    //   Serial.print(", u = ");
    //   Serial.println(Kp*error + x_i + y_d);
    return ( std::min(this->CONTROL_SATURATION, std::max(-this->CONTROL_SATURATION, this->Kp * error + this->x_i + this->y_d )));
}

