//
// Created by alfyhack on 09/11/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <UartDriver.h>

using namespace std;
using namespace Uart;
UartDriver *uart;

int main(int argc, char *argv[]) {

//    uart2Rasp testPack;
//    char *mem = (char *) &testPack;
//    mem[0] = 5;
//    mem[1]= 1 ;
//    mem[2]= 0 ;
//    mem[3]= 2 ;
//    mem[4]= 0 ;
//    mem[5]= 3 ;
//    mem[6]= 0 ;
//    mem[7]= 4 ;
//    mem[8]= 0 ;
//    mem[9]= 5 ;
//    mem[10]= 0;
//    mem[11]= 6;
//    mem[12]= 0;
//
//    UartDriver::serialPackDb(testPack);
//
//    mEncoder testEn;
//    mem = (char *) testEn;
//    mem[1-1]= 1 ;
//    mem[2-1]= 0 ;
//    mem[3-1]= 2 ;
//    mem[4-1]= 0 ;
//    mem[5-1]= 3 ;
//    mem[6-1]= 0 ;
//    mem[7-1]= 4 ;
//    mem[8-1]= 0 ;
//    mem[9-1]= 5 ;
//    mem[10-1]= 0;
//    mem[11-1]= 6;
//    mem[12-1]= 0;
//    EncoderMot::printEncoder(testEn);
//
//    return 0;
//    for (size_t i = 0; i < 13; i++) {
//        std::cout<<"i="<<i<<"\n";
//    }
//    return 0;

    try {
        uart = new UartDriver("/dev/ttyACM0");
    } catch (exception e) {
        e.what();
        exit(-1);
    }

    uart2Rasp *dato;
    settingsBoard pData;
    SettingBoard_C *p = new SettingBoard_C(pData);
    //curr neg => no limit
    p->setMotorLimit(Mot1, 2160, 24300, -19450);
    p->setMotorLimit(Mot2, 2960, 16200, -1000);
    p->setMotorLimit(Mot3, 2960, 21900, -7300);
    p->setMotorLimit(Mot4, 2160, 10000, -10000);
    p->setMotorLimit(Mot5, 2400, 10000, -10000);
    p->setMotorLimit(Mot6, 2160, 5770, -10);
    p->setAdcDiff(false);
    p->setAdcRef(in1V1);
    p->setPWMfreq(hz4k);
    p->printSetting();
    int i = 0;
    for (;;) {
        // Lettura non bloccante, Consuma molta CPU, ma è prestante
//        if ((dato = uart->getLastRecive()) != nullptr){
//            UartDriver::serialPackDb(*dato);
//            std::cout << "\n";
//        }

        // Leggo ultimo dato, se non è arrivato il thread viene messo in wait, fino all'arrivo
        std::cout << "Recived:\n";
        UartDriver::serialPackDb(*uart->getLastReciveWait());
        std::cout << "\n";
        i++;
        if (i > 5) {
            i = 0;
            uart->packSend(settingAsk, nullptr);
            p->setAdcDiff(!p->getSetting().diff);
            std::cout << "\nSend:\n";
            p->printSetting();
            uart->packSend(settingBoardData, (data2Rasp *) &p->getSetting());
        }

    }
    return 0;
}