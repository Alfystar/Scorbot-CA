//
// Created by alfyhack on 23/09/19.
//

#include "ScorCalc.h"

//initiaize static variables here
float ScoreCalc::vRef = 1.1;
float ScoreCalc::vCs = 0.14;
int ScoreCalc::bitAdc = 10;

ScoreCalc::ScoreCalc() {
    //default value
    ScoreCalc(ScoreCalc::vRef, ScoreCalc::vCs, ScoreCalc::bitAdc);
}

ScoreCalc::ScoreCalc(float vR, float vC, int bitAdc) {
    ScoreCalc::vRef = vR;
    ScoreCalc::vCs = vC;
    ScoreCalc::bitAdc = bitAdc;
}

void ScoreCalc::settingPrint() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("ScoreCalc execute trasformation with:\n");
    printf("Vref:\t%.3fV\n", this->vRefGet());
    printf("vCs:\t%.3fV\n", this->vCsGet());
    printf("bitAdc:\t%dBit (range:%d)\n", this->bitAdcGet(), this->rangeAdcGet());
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

float ScoreCalc::vRefNeed(float Imax) {
    this->vRefNeed(Imax, this->vCsGet());
}

float ScoreCalc::vRefNeed(float Imax, float Vcs) {
    return Imax * Vcs;
}

void ScoreCalc::adc2curr(DataManipolation::Pack &currPack) {
    if (currPack.getPackType() == PWMsend_CurRet || currPack.getPackType() == PWMsend_AllRet) {
        for (int i = Mot1; i < nMot; i++) {
            printf("%d)%4.3fA\t", i + 1, this->adc2curr(currPack.current().getCurrent((motCode)i)));
        }
        printf("\n");
    } else {
        printf("PACK type not correct!!!\n");
    }
}

float ScoreCalc::adc2curr(short adc) {
    return this->adc2curr(adc, this->vRefGet(), this->vCsGet(), this->bitAdcGet());
}

float ScoreCalc::adc2curr(int adc, float vRef, float vCs, int bitADC) {
    float iRead = (vRef * adc) / (pow(2, bitADC) * vCs);
    return iRead;
}

short ScoreCalc::curr2adc(float curr) {
    return this->curr2adc(curr, this->vRefGet(), this->vCsGet(), this->bitAdcGet());
}

short ScoreCalc::curr2adc(float curr, float vRef, float vCs, int bitADC) {
    int adcExpetted = (curr * pow(2, bitADC) * vCs) / (vRef);
    return adcExpetted;
}

void ScoreCalc::vRefSet(float v) {
    if (v < 0) v = 1.1;
    ScoreCalc::vRef = v;
}

float ScoreCalc::vRefGet() {
    return this->vRef;
}

void ScoreCalc::vCsSet(float v) {
    if (v < 0) v = 0.140;
    ScoreCalc::vCs = v;
}

float ScoreCalc::vCsGet() {
    return this->vCs;
}

void ScoreCalc::bitAdcSet(int bit) {
    if (bit < 1) bit = 1;
    ScoreCalc::bitAdc = bit;
}

int ScoreCalc::bitAdcGet() {
    return ScoreCalc::bitAdc;
}

int ScoreCalc::rangeAdcGet() {
    return pow(2, ScoreCalc::bitAdc);
}