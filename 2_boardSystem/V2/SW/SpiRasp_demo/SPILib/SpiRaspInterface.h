#ifndef SPISEND_H
#define SPISEND_H

#include "../../SpiPack/SpiPack.h"
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <wiringPi.h>       //to enable comunication, on pin GPIO 17 or for this lib pin 0
/*
 *Need to be root or inside gpio group
 * so tips on terminal:
 * "sudo usermod -a -G gpio <userName>"
 * <userName> :can be discover tips "whoami" or "id"
 *
 * to check the result write "groups <userName>" and search gpio
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <iostream>
#include <mutex>

#define EnCom 17     //Gpio 17(BCM), Pin 0(wiringPi)
namespace SpiRaspInterface {
    using namespace spiPack;

    class ScorBoard {
    public:
        static ScorBoard &getInstance();

        //sending metod
        void goHomePack();

        //Set board Settings
        void setSettingPack(Pack &p);
        void setSettingPack(settingsBoard &s);
        //Get board Settings
        void getSettingPack(Pack &p);
        settingsBoard *getSettingPack();

        //Motor controll with return
        void setPwm_EnPack(Pack &p);
        mEncoder *setPwm_EnPack(mSpeed &ms);
        void setPwm_CurPack(Pack &p);
        mCurrent *setPwm_CurPack(mSpeed &ms);
        void setPwm_AllPack(Pack &p);
        mAll *setPwm_AllPack(mSpeed &ms);

        //Sensor return
        void getEnPack(Pack &p);
        mEncoder *getEnPack();
        void getCurrentPack(Pack &p);
        mCurrent *getCurrentPack();
        void getSensPack(Pack &p);
        mAll *getSensPack();
    protected:
    private:
        struct spi_ioc_transfer spi;
        char *txbuf, *rxbuf;
        int size, fdSpi;
        const int hzSpeed = 31000; //32Khz per dare tempo ad arduino, nella realtà 30.5 kHz
        const char bitWord = 8;

        static ScorBoard *instance;

        //costruttori/distruttori
        ScorBoard();
        ~ScorBoard();
        void sendPack(Pack &p);
        void setMode(packType mode);
        //debug
        void bytePrint(Pack &p);
    };

    class ScoreCalc {
    public:
        ScoreCalc();
        ScoreCalc(float vRef, float vCs, int bitAdc);
        void settingPrint();
//utility function
        float vRefNeed(float Imax);
        static float vRefNeed(float Imax,float Vcs);

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
        settingsBoard boardSet;
        static float vRef;  //Voltage reference ADC
        static float vCs;  //Voltage current sensitive DriverOutput
        static int bitAdc;
    };


}
#endif // SPISEND_H
