//
// Created by alfyhack on 15/10/19.
//

#include "SettingBoard_C.h"

namespace DataManipolation{
    SettingBoard_C::SettingBoard_C(settingsBoard &s){
        this->changePack(s);
    }

    void SettingBoard_C::changePack(settingsBoard &sets) {
        this->setPack=&sets;
    }

    void SettingBoard_C::copyPack(SettingBoard_C &sets) {
        this->copyPack(sets.getSetting());
    }

    void SettingBoard_C::copyPack(settingsBoard &sets) {
        memcpy(this->setPack,&sets, sizeof(settingsBoard));
    }

    settingsBoard &SettingBoard_C::getSetting() {
        return *this->setPack;
    }

    void SettingBoard_C::setMotorLimit( motCode mot, short enMax, short enMin, short cur) {
        //Set variable inside the pack to send-out
        this->setMaxEn(mot, enMax);
        this->setMinEn(mot, enMin);
        this->setMaxCurrentMed(mot, cur);
    }

    void SettingBoard_C::setMaxEn(motCode mot, short en) {
        this->setPack->maxEn[mot] = en;
    }

    void SettingBoard_C::setMinEn( motCode mot, short en) {
        this->setPack->minEn[mot] = en;
    }

    void SettingBoard_C::setMaxCurrentMed(motCode mot, short current) {
        this->setPack->maxCurrMed[mot] = current;
    }

    void SettingBoard_C::setAdcRef(adcRef adc) {
        this->setPack->adcVref = adc;
    }

    void SettingBoard_C::setAdcDiff(bool diff) {
        this->setPack->diff = diff;
    }

    void SettingBoard_C::setPWMfreq(pwmFreq freq) {
        this->setPack->freq = freq;
    }

    void SettingBoard_C::printSetting() {
        this->printSetting(this->getSetting());
    }

    void SettingBoard_C::printSetting(settingsBoard &sets) {
#ifdef ScorboarFirmware
        Serial.print("#maxEn:\t\t");
        for (byte i = 0; i < nMot; i++) {
            Serial.print("\t");
            Serial.print((int)sets.maxEn[Mot1 + i]);
            delay(1);
        }
        Serial.println();

        Serial.print("#minEn:\t\t");
        for (byte i = 0; i < nMot; i++) {
            Serial.print("\t");
            Serial.print((int)sets.minEn[Mot1 + i]);
            delay(1);
        }
        Serial.println();

        Serial.print("#maxCurrMed:");
        for (byte i = 0; i < nMot; i++) {
            Serial.print("\t");
            Serial.print((int)sets.maxCurrMed[Mot1 + i]);
            delay(1);
        }
        Serial.println();
        Serial.flush();
        Serial.print("#AdcVref set: ");
        switch(sets.adcVref){
            case in1V1:
                Serial.println("Internal Reference at 1.1V");
                break;
            case in2V56:
                Serial.println("Internal Reference at 2.56V");
                break;
            case ext:
                Serial.println("External Reference (trimmer)");
                break;
            default:
                Serial.print("Register not set, number is: ");
                Serial.println(sets.adcVref);
                break;
        }
        delay(1);

        Serial.print("#Adc offset remove State: ");
        if(sets.diff)
            Serial.println("On");
        else
            Serial.println("Off");
        delay(1);

        Serial.println("#PWM duty cycle set timer 3&4 divisor to: ");
        Serial.print("\t");
        switch(sets.freq){
            case hz30:
                Serial.println("1024 for PWM frequency of 30.64 Hz");
                break;
            case hz120:
                Serial.println("256 for PWM frequency of 122.55 Hz");
                break;
            case hz490:
                Serial.println("64 for PWM frequency of 490.20 Hz");
                break;
            case hz4k:
                Serial.println("8 for PWM frequency of 3921.16 Hz");
                break;
            case hz30k:
                Serial.println("1 for PWM frequency of 31372.55 Hz");
                break;
            default:
                Serial.print("Register not set, number is: ");
                Serial.println(sets.freq);
                break;
        }
        Serial.println();
        delay(1);
        return;
#else //Start Rasp print pack
        printf("maxEn:\t");
        for (int i = 0; i < nMot; i++) {
            printf("%d)%hd\t", i + 1, sets.maxEn[Mot1 + i]);
        }
        printf("\nminEn:\t");
        for (int i = 0; i < nMot; i++) {
            printf("%d)%hd\t", i + 1, sets.minEn[Mot1 + i]);
        }
        printf("\nmaxCurrMed:\t");
        for (int i = 0; i < nMot; i++) {
            printf("%d)%hd\t", i + 1, sets.maxCurrMed[Mot1 + i]);
        }
        printf("\nadcReference voltage:\t");
        switch (sets.adcVref) {
            case in1V1:
                printf("Internal Reference 1.1V");
                break;
            case in2V56:
                printf("Internal Reference 2.56V");
                break;
            case ext:
                printf("External Source (Trimmer Reference)");
                break;
            default:
                printf("Register not set, number is: %d", sets.adcVref);
                break;
        }
        printf("\n");
        printf("Adc offset remove Read: ");
        if (sets.diff)
            printf("On");
        else
            printf("Off");
        printf("\n");
        printf("PWM duty cycle set timer 3&4 divisor to: ");
        switch (sets.freq) {
            case hz30:
                printf("1024 for PWM frequency of 30.64 Hz");
                break;
            case hz120:
                printf("256 for PWM frequency of 122.55 Hz");
                break;
            case hz490:
                printf("64 for PWM frequency of 490.20 Hz");
                break;
            case hz4k:
                printf("8 for PWM frequency of 3921.16 Hz");
                break;
            case hz30k:
                printf("1 for PWM frequency of 31372.55 Hz");
                break;
            default:
                printf("Register not set, number is: %d", sets.freq);
                break;
        }
        printf("\n");
        return;
#endif //END Rasp print pack

    }
};