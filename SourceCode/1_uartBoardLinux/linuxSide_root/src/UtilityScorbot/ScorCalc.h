//
// Created by alfyhack on 23/09/19.
//

#ifndef SPIRASP_TERMINAL_SCORCALC_H
#define SPIRASP_TERMINAL_SCORCALC_H

#include <math.h>
#include <DataTransfert_AllInclude.h>

using namespace DataManipolation;
using namespace DataPrimitive;

typedef struct {
    double alpha, beta, gamma, delta;
    int maxClaw;
} conParams;

typedef double thetaMot[nMot];

typedef struct {
    double x, y, z;
    double beta, omega;
} positionRobot;


class ScoreCalc {
public:
    ScoreCalc();

    ScoreCalc(float vRef, float vCs, int bitAdc);

    void settingPrint();

//utility function
    float vRefNeed(float Imax);

    static float vRefNeed(float Imax, float Vcs);

    void adc2curr(Pack &currPack);
    float adc2curr(int adc);
    static float adc2curr(int adc, float vRef, float vCs, int bitADC);

    int curr2adc(float curr);
    static int curr2adc(float curr, float vRef, float vCs, int bitADC);

    void vRefSet(float v);

    float vRefGet();

    void vCsSet(float v);

    float vCsGet();

    void bitAdcSet(int bit);

    int bitAdcGet();

    int rangeAdcGet();

    void en2th(mEncoder e, thetaMot t, conParams *par);  // en-> rad ( eccetto pinza, %)
    void th2en(thetaMot t, mEncoder e, conParams *par);  // rad ( eccetto pinza, %) -> en
    void dirCin(thetaMot t, positionRobot *p);

    void invCin(positionRobot *p, thetaMot t);


private:
    static float vRef;  //Voltage reference ADC
    static float vCs;  //Voltage current sensitive DriverOutput
    static int bitAdc;
};

#endif //SPIRASP_TERMINAL_SCORCALC_H
