//
// Created by alfyhack on 23/09/19.
//

#ifndef SPIRASP_TERMINAL_SCORCALC_H
#define SPIRASP_TERMINAL_SCORCALC_H

#include "../../SpiPack/SpiPack.h"
#include <math.h>

using namespace spiPack;

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
private:
    static float vRef;  //Voltage reference ADC
    static float vCs;  //Voltage current sensitive DriverOutput
    static int bitAdc;
};

#endif //SPIRASP_TERMINAL_SCORCALC_H
