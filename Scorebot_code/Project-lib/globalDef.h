/*
 * pinDef.h
 *
 *  Created on: 22 mar 2019
 *      Author: alfy
 */

#ifndef PROJECT_LIB_GLOBALDEF_H_
#define PROJECT_LIB_GLOBALDEF_H_

#define motEn 38 //PD7

#define MISO 50
#define MOSI 51
#define SS 53
#define SCK 52

#define nMot 6
enum motCode {cMot1=0, cMot2, cMot3, cMot4, cMot5, cMot6};



typedef struct settingsBoard_ {
	int maxEn[nMot]; 		//valore massimo di passi prima di considerarsi fuori range di sicurezza
	int maxCurrMed[nMot];	//valore massimo di corrente Efficace (con una media di 1 ms ~ ultime 8 letture), numero * 8 per semplificare i conti)
} settingsBoard;

#endif /* PROJECT_LIB_GLOBALDEF_H_ */
