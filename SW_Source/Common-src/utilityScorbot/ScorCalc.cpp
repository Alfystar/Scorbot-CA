//
// Created by alfyhack on 23/09/19.
//

#include "ScorCalc.h"

#ifdef LinuxSide
#include <iostream>
#endif

//initiaize static variables here
float ScoreCalc::vRef = 1.1;
float ScoreCalc::vCs = 0.14;
int ScoreCalc::bitAdc = 10;

ScoreCalc::ScoreCalc (){
    //default value
    ScoreCalc(ScoreCalc::vRef, ScoreCalc::vCs, ScoreCalc::bitAdc);
}

ScoreCalc::ScoreCalc (float vR, float vC, int bitAdc){
    ScoreCalc::vRef = vR;
    ScoreCalc::vCs = vC;
    ScoreCalc::bitAdc = bitAdc;
}

void ScoreCalc::settingPrint (){
    #ifndef ScorboarFirmware
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("ScoreCalc execute trasformation with:\n");
    printf("Vref:\t%.3fV\n", this->vRefGet());
    printf("vCs:\t%.3fV\n", this->vCsGet());
    printf("bitAdc:\t%dBit (range:%d)\n", this->bitAdcGet(), this->rangeAdcGet());
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    #else
    //todo: Debug print per l'arduino
    #endif
}

float ScoreCalc::vRefNeed (float Imax){
    return this->vRefNeed(Imax, this->vCsGet());
}

float ScoreCalc::vRefNeed (float Imax, float Vcs){
    return Imax * Vcs;
}

float ScoreCalc::adc2curr (int adc){
    return this->adc2curr(adc, this->vRefGet(), this->vCsGet(), this->bitAdcGet());
}

float ScoreCalc::adc2curr (int adc, float vRef, float vCs, int bitADC){
    float iRead = (vRef * adc) / (pow(2, bitADC) * vCs);
    return iRead;
}

int ScoreCalc::curr2adc (float curr){
    return this->curr2adc(curr, this->vRefGet(), this->vCsGet(), this->bitAdcGet());
}

int ScoreCalc::curr2adc (float curr, float vRef, float vCs, int bitADC){
    int adcExpetted = (curr * pow(2, bitADC) * vCs) / (vRef);
    return adcExpetted;
}

void ScoreCalc::vRefSet (float v){
    if (v < 0) v = 1.1;
    ScoreCalc::vRef = v;
}

float ScoreCalc::vRefGet (){
    return this->vRef;
}

void ScoreCalc::vCsSet (float v){
    if (v < 0) v = 0.140;
    ScoreCalc::vCs = v;
}

float ScoreCalc::vCsGet (){
    return this->vCs;
}

void ScoreCalc::bitAdcSet (int bit){
    if (bit < 1) bit = 1;
    ScoreCalc::bitAdc = bit;
}

int ScoreCalc::bitAdcGet (){
    return ScoreCalc::bitAdc;
}

int ScoreCalc::rangeAdcGet (){
    return pow(2, ScoreCalc::bitAdc);
}

void ScoreCalc::en2th (mEncoder e, thetaMot t, conParams *par){
    //    std::cout << "sizeof(thetaMot)=" << sizeof(thetaMot) << "\n";
    //    thetaMot *t = (thetaMot *) malloc(sizeof(thetaMot));
    //    std::cout << "*t=" << t << "\n";

    t[Mot1] = -par->alpha * e[Mot1];

    t[Mot2] = -par->beta * e[Mot2];

    t[Mot3] = par->beta * (e[Mot2] + e[Mot3]);

    t[Mot4] = -par->beta * e[Mot3] + par->gamma * (e[Mot4] - e[Mot5]);

    t[Mot5] = par->delta * (e[Mot4] + e[Mot5]);

    if (par->maxClaw != 0){
        t[Mot6] = e[Mot6] / (double) par->maxClaw;
    }
    if (t[Mot6] < 0)
        t[Mot6] = 0;
    if (t[Mot6] > 1)
        t[Mot6] = 1;

    for (int i = 0; i < Mot6; ++i){
        if (abs(t[i]) < 0.001)
            t[i] = 0;
        t[i] = fmod(t[i], 2 * M_PI);
    }
}

void ScoreCalc::th2en (thetaMot t, mEncoder e, conParams *par){
    //    mEncoder *e = (mEncoder *) malloc(sizeof(mEncoder));
    e[Mot1] = -t[Mot1] / par->alpha;
    e[Mot2] = -e[Mot2] / par->beta;

    e[Mot3] = -(t[Mot2] + t[Mot3]) / par->beta;

    e[Mot4] = 0.5 * ((t[Mot2] + t[Mot3] + t[Mot4]) / par->gamma + t[Mot5] / par->delta);

    e[Mot5] = 0.5 * (-(t[Mot2] + t[Mot3] + t[Mot4]) / par->gamma + t[Mot5] / par->delta);

    if (par->maxClaw != 0){
        e[Mot6] = t[Mot6] * (double) par->maxClaw;
    }
}

void ScoreCalc::dirCin (thetaMot t, positionRobot *p, geometryRobot *g){
    //// calcolo della posizione del polso
    double xpolso = cos(t[Mot1]) * (g->l1 + g->l2 * cos(t[Mot2]) + g->l3 * cos(t[Mot2] + t[Mot3]));
    double ypolso = sin(t[Mot1]) * (g->l1 + g->l2 * cos(t[Mot2]) + g->l3 * cos(t[Mot2] + t[Mot3]));
    double zpolso = g->d1 - g->l2 * sin(t[Mot2]) - g->l3 * sin(t[Mot2] + t[Mot3]);
    //// calcolo della posizione della pinza
    p->x = (xpolso - cos(t[Mot1]) * g->d5 * sin(t[Mot2] + t[Mot3] + t[Mot4]));
    p->y = (ypolso - sin(t[Mot1]) * g->d5 * sin(t[Mot2] + t[Mot3] + t[Mot4]));
    p->z = (zpolso - g->d5 * cos(t[Mot2] + t[Mot3] + t[Mot4]));
    p->beta = t[Mot2] + t[Mot3] + t[Mot4] + M_PI / 2.0;
    p->omega = t[Mot5];
}

int ScoreCalc::invCin (positionRobot *p, geometryRobot *g, bool gomito, thetaMot t){
    t[Mot1] = atan2(p->y, p->x);
    double A1 = p->x * cos(t[Mot1]) + p->y * sin(t[Mot1]) - g->d5 * cos(p->beta) - g->l1;
    double A2 = g->d1 - p->z - g->d5 * sin(p->beta);
    t[Mot3] = (2 * gomito - 1) * acos((pow(A1, 2) + pow(A2, 2) - pow(g->l2, 2) - pow(g->l3, 2)) / (2 * g->l2 * g->l3));
    if (t[Mot3] == NAN)
        return -1;
    t[Mot2] = atan2((g->l2 + g->l3 * cos(t[Mot3])) * A2 - g->l3 * sin(t[Mot3]) * A1,
                    (g->l2 + g->l3 * cos(t[Mot3])) * A2 + g->l3 * sin(t[Mot3]) * A1);
    t[Mot4] = p->beta - t[Mot2] + t[Mot3] - M_PI / 2.0;
    t[Mot5] = p->omega;
    return 0;
}
