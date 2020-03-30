#include "EEPROM.h"
#include "Project-lib/globalDef.h"

void memoryLoad() {
    EEPROM.get(0, sets);//carico i valori in memoria dentro alla variabile globale sets
}

void memorySave(settingsBoard *set) {
    EEPROM.put(0, *set);
    memcpy(&sets, set, sizeof(settingsBoard));
    Serial.println("\nValue save on ram:");
    Serial.print("--maxEn:\t\t");
    for (byte i = 0; i < nMot; i++) {
        Serial.print("\t");
        Serial.print(sets.maxEn[cMot1 + i]);
    }
    Serial.println();
    Serial.print("--minEn:\t\t");
    for (byte i = 0; i < nMot; i++) {
        Serial.print("\t");
        Serial.print(sets.minEn[cMot1 + i]);
    }
    Serial.println();
    Serial.print("--maxCurrMed:");
    for (byte i = 0; i < nMot; i++) {
        Serial.print("\t");
        Serial.print(sets.maxCurrMed[cMot1 + i]);
    }
    Serial.println();
}
