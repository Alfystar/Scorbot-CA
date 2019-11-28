/*
 * pinDef.h
 *
 *  Created on: 22 mar 2019
 *      Author: alfy
 */

#ifndef PROJECT_LIB_GLOBALDEF_H_
#define PROJECT_LIB_GLOBALDEF_H_

#include "../HW_rename.h"
#include "../DataTransfertPackge/DataTransfert_AllInclude.h"
#include "spiScorebot/spiScorebot.h"
#include "../uartDriver/UartDriver.h"
#include "adcReader/adcReader.h"
#include "msEnlib/msEnlib.h"

namespace DataPrimitive {
}    //to mute the compiler (￣Д￣)
using namespace DataPrimitive;
extern settingsBoard globSets;

namespace DataManipolation {
}    //to mute the compiler (￣Д￣)
using namespace DataManipolation;
extern SettingBoard_C Gset;

namespace InternalDevice {
}    //to mute the compiler (￣Д￣)
using namespace InternalDevice;
namespace Uart {
}    //to mute the compiler (￣Д￣)
using namespace Uart;

extern class SpiDevice *spi;

extern class UartDriver *uart; // @suppress("Ambiguous problem")

extern class AdcDevice *adc;

namespace ScorebotRead {
}    //to mute the compiler (￣Д￣)
using namespace ScorebotRead;

extern class ScorFeed *sFeed;

#define motEn 38 //PD7

//define SPI
#define MISO 50
#define MOSI 51
#define SS 53
#define SCK 52

//define MOTORI
#define MotEn 38        //PD7
#define EN1 5            //PE3
#define IN1A 22            //PA0
#define IN1B 23            //PA1
#define EN2 2            //PE4
#define IN2A 24            //PA2
#define IN2B 25            //PA3
#define EN3 3            //PE5
#define IN3A 26            //PA4
#define IN3B 27            //PA5
#define EN4 6            //PH3
#define IN4A 28            //PA6
#define IN4B 29            //PA7
#define EN5 7            //PH4
#define IN5A 49            //PL0
#define IN5B 48            //PL1
#define EN6 8            //PH5
#define IN6A 47            //PL2
#define IN6B 46            //PL3
#endif /* PROJECT_LIB_GLOBALDEF_H_ */
