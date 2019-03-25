#include "EEPROM.h"

void memoryLoad() {
	EEPROM.get(0, sets);	//carico i valori in memoria dentro alla variabile globale sets
}

void memorySave(settings *set) {
	EEPROM.put(0, set);
	memcpy(&sets,set,sizeof(settings));
}
