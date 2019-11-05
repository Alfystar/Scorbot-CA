/*
 * msEnlib.h
 *	Libreria di lettura e elaborazione dei passi encoder
 *	e dei micro switch dello scorebot
 *  Created on: 25 mar 2019
 *      Author: alfy
 */

#ifndef PROJECT_LIB_MSENLIB_H_
#define PROJECT_LIB_MSENLIB_H_

#include "Arduino.h"
#include "wiring_private.h"    //work on bit
#include <stdlib.h>
#include "circular_buffer/circular_buffer.h"
#include "../globalDef.h"

#define sizeMem 255    //numero di celle (di int [2 byte])nel buffer circolare
//One of this 2
#define PCINT_EN 1
//#define TIMER5OVF_EN 1

namespace ScorebotRead {
    using namespace DataPrimitive;

    class ScorFeed {
    public:
        ScorFeed();                //Imposta i pin di uscita e registri
        void updateStepEn();
        static void interruptEn(bool en);
        void isrFunxEN();

        mEncoder &captureEn();//Crea un istantanea FISSA degli encoder(fino a successiva chiamata)
        byte msRead();            //Ritorna MicroSwitch con logica 1-hot
        short enRead();    //Ritorna il valore degli encoder con logica 1-hot dove i byte sono:[0]ChA e [1]ChB

        void setEn(motCode mot, short st);
        short getEn(motCode mot);

        void dSubDebug();
        void storedData();
        void printSteps();
    private:
        cbuf_handle_t circularBuf;
        mEncoder bufMem[sizeMem];
        mEncoder step;
        mEncoder tempStep;

        void calcStep(int oldEn, int newEn);
    };

}            //END namespace ScorebotRead

#ifndef __IN_ECLIPSE__

#include "msEnlib.cpp"

#endif
#endif /* PROJECT_LIB_MSENLIB_H_ */
