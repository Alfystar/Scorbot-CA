#include "Arduino.h"

unsigned long sanityTime = 0;
extern Motor::DCdriverLimit *mot[nMot];

void sanityChek (int wait){
    if (millis() < sanityTime + wait){
        return;
    }

    sanityTime = millis();
    for (byte i = 0; i < nMot; i++){
        if (globSets.maxCurrMed[i] < 0)
            continue;
        if (globSets.maxCurrMed[i] < adc->getCurrentSum((motCode) i)){
            mot[i]->freeRun();
            #ifdef DB_PRINT
            Db.print("nMot[");
            Db.print(i + 1);
            Db.print("] overcurrent: ");
            Db.print(globSets.maxCurrMed[i]);
            Db.print(" > ");
            Db.println(adc->getCurrentSum((motCode) i));
            #endif
        }
        if (((globSets.maxCurrMed[i] * 3) / 2) < adc->getCurrentSum((motCode) i)){    // WARNING
            digitalWrite(MotEn, 0);
            #ifdef DB_PRINT
            Db.print("nMot[");
            Db.print(i + 1);
            Db.print("] High-overcurrent: ");
            Db.print(globSets.maxCurrMed[i]);
            Db.print(" > ");
            Db.println(adc->getCurrentSum((motCode) i));
            #endif
        }
        if ((globSets.maxCurrMed[i] / 4) < adc->getCurrentSum((motCode) i)){ // Current problem came back
            digitalWrite(MotEn, 1);
        }
    }//for end
}
