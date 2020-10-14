#include "EEPROM.h"
#include "Project-lib/globalDef.h"

void memoryLoad (){
    EEPROM.get(0, globSets); //carico i valori in memoria dentro alla variabile globale sets
}

void memorySave (settingsBoard &set){
    EEPROM.put(0, set);
    memcpy(&globSets, &set, sizeof(settingsBoard));    //update global set
    #ifdef EEPROM_DB
    Db.println("\n~~~~~~Value save on ram:~~~~~~");
    DataManipolation::SettingBoard_C::printSetting(set);
    Db.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    #endif
}
