#ifndef SpiPack_H
#define SpiPack_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef ScorboarFirmware
#warning ScorboarFirmware define not Declared, if you are compiling library to Arduino, add at the end of gcc compiler: -D ScorboarFirmware

#include <exception>
#include <string>
#include <bits/exception.h>

using std::max;
#else
#include <Arduino.h>
#endif
namespace spiPack {
/// Enum Declaration for the comunication
    enum packDest {
        pack4Ard, pack4Rasp
    };

    enum specialPwmCode {
        freeRun = 300, hardStop = 350, softStop = 400, ignore = 450
    };
    enum motCode {
        Mot1 = 0, Mot2, Mot3, Mot4, Mot5, Mot6, nMot
    };

    enum packType {
        invalid = 0, PWMsend_EnRet = 1, PWMsend_CurRet, PWMsend_AllRet, CurrentGet, SettingGet, SettingSet, goHome
    };

    enum adcRef {
        in1V1 = -1, in2V56 = -2, ext = -3
    };
///#################################################################
///Pack information structure

    typedef short mSpeed[nMot];

    typedef struct settingsBoard_ {
        short maxEn[nMot];        //valore massimo di passi prima di considerarsi fuori range di sicurezza (numeri pos)
        short minEn[nMot];        //valore minimo di passi prima di considerarsi fuori range di sicurezza (numeri neg)
        short maxCurrMed[nMot];    //valore massimo di corrente Efficace (con una media di 1 ms ~ ultime 8 letture), numero * 8 per semplificare i conti)
        adcRef adcVref;
        //todo: lettura diretta/differenziale
        //todo: frequenza pwm
    } settingsBoard;

    typedef short mCurrent[nMot];

    typedef short mEncoder[nMot];

    typedef struct mAll_ {
        mEncoder en;
        mCurrent cur;
    } mAll;
///#################################################################
///Send/Recive pack union

/*Struttura di Invio, usata dalla classe SPISEND*/
    typedef struct spi2Ard_ {
        union sendType {
            mSpeed speed;
            settingsBoard prop;
        } up;
        char buf[sizeof(sendType)];
    } spi2Ard;


/*Struttura di Ricezione, usata dalla classe SPISEND*/
    typedef struct spi2Rasp_ {
        union recType {
            mEncoder en;
            mCurrent cur;
            mAll sens;
            settingsBoard prop;
        } up;
        char buf[sizeof(recType)];
    } spi2Rasp;

//## -------------------------------------------------------- ##//
    typedef struct SPIPACK_ {
        packType type;
        spi2Ard forArd;
        spi2Rasp forRasp;
    } SPIPACK;

    class Pack {
    public:
        Pack();
        Pack(Pack &p);
        Pack(SPIPACK &s);
        ~Pack();
        /// utility method
        void clearPack();
        void printPack();
        /// send/recive information
        int sizePack();
        SPIPACK &getSPIPACK();
        void setPackType(packType t);
        packType getPackType();
        /// pack Compilation
        void pwmSet(mSpeed &pwms);
        void pwmSet(short m1, short m2, short m3, short m4, short m5, short m6);
        void pwmSet(motCode mot, short pwm);
#ifndef ScorboarFirmware
        void setEncoder(mEncoder &c) noexcept(false);
        void setEncoder(motCode mot, short en) noexcept(false);

        void setCurrent(mCurrent &c) noexcept(false);
        void setCurrent(motCode mot, short cur) noexcept(false);
#else
        void setEncoder(mEncoder &c);
        void setEncoder(motCode mot, short en);

        void setCurrent(mCurrent &c);
        void setCurrent(motCode mot, short cur);
#endif
        void setSetting(settingsBoard &sets, packDest dest);
        void setMotorLimit(packDest dest, motCode mot, short enMax, short enMin, short cur);
        void setMaxEn(packDest dest, motCode mot, short en);
        void setMinEn(packDest dest, motCode mot, short en);
        void setMaxCurrentMed(packDest dest, motCode mot, short current);
        void setAdcRef(packDest dest, adcRef adc);
        /// pack Data read

#ifndef Arduino_h
        mSpeed &getPwm() noexcept(false);
        mEncoder &getEncoder() noexcept(false);
        mCurrent &getCurrent() noexcept(false);
        mAll &getSens() noexcept(false);
        settingsBoard &getSetting(packDest dest) noexcept(false);
        settingsBoard &getSetting() noexcept(false);    //base of pack type
#else
        mSpeed &getPwm();
        mEncoder &getEncoder();
        mCurrent &getCurrent();
        mAll &getSens();
        settingsBoard &getSetting(packDest dest);
        settingsBoard &getSetting();                    //base of pack type

#endif
    private:
        SPIPACK data;
    };

#ifndef ScorboarFirmware

//Exeption tree
    class typePackWrongExcept : public std::exception {
        std::string _msg;
    public:
        typePackWrongExcept(const std::string &msg) : _msg(msg) {}

        virtual const char *what() const noexcept override {
            std::string tipo = "typePackWrongExcept";
            return tipo.append(_msg).c_str();
        }
    };

#endif
    SPIPACK *makeSPIPACK();
    void freeSPIPACK(SPIPACK *p);
}
#ifndef __GNUC__
#include "SpiPack.cpp"
#endif
#endif // SpiPack_H
