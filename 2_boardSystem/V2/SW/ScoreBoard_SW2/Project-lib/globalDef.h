/*
 * pinDef.h
 *
 *  Created on: 22 mar 2019
 *      Author: alfy
 */

#ifndef PROJECT_LIB_GLOBALDEF_H_
#define PROJECT_LIB_GLOBALDEF_H_

#include "spiScorebot/SpiPack.h"
using namespace spiPack;

#define motEn 38 //PD7

//define SPI
#define MISO 50
#define MOSI 51
#define SS 53
#define SCK 52

//define MOTORI

#define EN1 5		//PE3
#define IN1A 22		//PA0
#define IN1B 23		//PA1

#define EN2 2		//PE4
#define IN2A 24		//PA2
#define IN2B 25		//PA3

#define EN3 3		//PE5
#define IN3A 26		//PA4
#define IN3B 27		//PA5

#define EN4 6		//PH3
#define IN4A 28		//PA6
#define IN4B 29		//PA7

#define EN5 7		//PH4
#define IN5A 49		//PL0
#define IN5B 48		//PL1

#define EN6 8		//PH5
#define IN6A 47		//PL2
#define IN6B 46		//PL3

extern settingsBoard sets;

#endif /* PROJECT_LIB_GLOBALDEF_H_ */
