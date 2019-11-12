#include "EEPROM.h"
#include "Project-lib/globalDef.h"

void memoryLoad() {
    EEPROM.get(0, globSets); //carico i valori in memoria dentro alla variabile globale sets
}

void memorySave(settingsBoard &set) {
    Db.println("Salvataggio setting in corso");
    EEPROM.put(0, set);
    memcpy(&globSets, &set, sizeof(settingsBoard));    //update global set
#ifdef SERIAL_PRINT
    Serial.println("\n~~~~~~Value save on ram:~~~~~~");
    Pack::printSetting(set);
    Serial.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
#endif
}
