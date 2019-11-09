//
// Created by alfyhack on 15/10/19.
//

#ifndef DATAPRIMITIVE_H
#define DATAPRIMITIVE_H

#include "../ScoreBoard_Uart/HW_rename.h"

namespace DataPrimitive{
    /// Enum Declaration for the comunication
    enum packDest : char {
        pack4Ard, pack4Rasp
    };

    enum specialPwmCode : short {
        freeRun = 300, hardStop = 350, softStop = 400, ignore = 450
    };
    enum motCode : char {
        Mot1 = 0, Mot2, Mot3, Mot4, Mot5, Mot6, nMot
    };
    enum packType : char {
        //invalid = 0, prima presente ma forse inutile
        PWMsend_EnRet = 1, PWMsend_CurRet, PWMsend_AllRet, SettingGet, SettingSet, goHome
    };
    enum uartPackType : char{
        mSpeedData = 1,
        settingBoardData,
        mCurrentData,
        mAllData,
        mEncoderData,
        sampleTimeEn,
        sampleTimeCur,
        goHomeUart,
        settingAsk,
        RESEND
    };
    //sampleTimeEn && sampleTimeCur tempi in micro secondi (unsigned short), se devono essere inviati sia En che Cur, si invia un mAll
    enum adcRef : char {
        in1V1 = 0, in2V56, ext
    };
// set timer divisor to     1 for PWM frequency of 31372.55 Hz
// set timer divisor to     8 for PWM frequency of  3921.16 Hz
// set timer divisor to    64 for PWM frequency of   490.20 Hz
// set timer divisor to   256 for PWM frequency of   122.55 Hz
// set timer divisor to  1024 for PWM frequency of    30.64 Hz
    enum pwmFreq : char {
        hz30, hz120, hz490, hz4k, hz30k
    };
///#################################################################
///Pack information structure

    typedef short mSpeed[nMot];

    typedef short mCurrent[nMot];

    typedef short mEncoder[nMot];

    typedef struct settingsBoard_ {
        mEncoder maxEn;          //valore massimo di passi prima di considerarsi fuori range di sicurezza (numeri pos)
        mEncoder minEn;          //valore minimo di passi prima di considerarsi fuori range di sicurezza (numeri neg)
        mCurrent maxCurrMed;     //valore massimo di corrente Efficace (con una media di 1 ms ~ ultime 8 letture), numero * 8 per semplificare i conti)
        adcRef adcVref;
        bool diff;                  //true = offset delete, false = basicValue
        pwmFreq freq;
    }__attribute__((packed)) settingsBoard; //https://www.geeksforgeeks.org/how-to-avoid-structure-padding-in-c/

    typedef struct mAll_ {
        mEncoder en;
        mCurrent cur;
    }mAll;

/*Struttura di Invio dati all'arduino*/
    typedef union {
        union sendType {
            mSpeed speed;
            settingsBoard prop;
            unsigned short sampleEn;
            unsigned short sampleCur;
        } up;
        char buf[sizeof(sendType)];
    } data2Ard;


/*Struttura di Invio dati al Rapsberry*/
    typedef union {
        union ricType {
            mEncoder en;
            mCurrent cur;
            mAll sens;
            settingsBoard prop;
        } up;
        char buf[sizeof(ricType)];
    } data2Rasp;

///#################################################################
///Send/Recive spi pack
   typedef struct SPIPACK_ {
        packType type;
        data2Ard forArd;
        data2Rasp forRasp;
    } SPIPACK;

///#################################################################
///Sendable uart pack
    typedef struct uart2Ard_ {
        packType type;
        //short checkSum; Prima vedere se serve
        data2Ard data;
    } uart2Ard;

    typedef struct uart2Rasp_ {
        packType type;
        //short checkSum; Prima vedere se serve
        data2Rasp data;
    } uart2Rasp;
}


#endif //DATAPRIMITIVE_H
