//
// Created by alfyhack on 09/11/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <UartSubSystem.h>
#include <DataTransfert_AllInclude.h>

using namespace std;
using namespace DataPrimitive;
using namespace DataManipolation;
ScorInterface *scorbot;

int main(int argc, char *argv[]) {
    /// Initialize board
    try {
//        scorbot = &AdapterFactory::makeUart("/dev/ttyACM0",B115200);
        scorbot = &AdapterFactory::makeUart("/dev/ttyACM0", B921600);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }

    /// Setting test
    settingsBoard pData;
    SettingBoard_C *p = new SettingBoard_C(pData);

    //Setting per ora di default
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
    SettingBoard_C *pRecive;
    std::cout << "============================================================\n";
    std::cout << "Default Settings:\n";
    p->printSetting();
    std::cout << "\n";

    std::cout << "Settings from board directly:\n";
    pRecive = scorbot->getSetting_board();
    pRecive->printSetting();
    delete pRecive;
    std::cout << "\n";

    std::cout << "Settings read from local:\n";
    pRecive = scorbot->getSetting_local();
    pRecive->printSetting();
    delete pRecive;
    std::cout << "\n";

    std::cout << "Sending default settings:\n";
    scorbot->setSetting(*p);
    std::cout << "\n";

    std::cout << "Settings read from local:\n";
    pRecive = scorbot->getSetting_local();
    pRecive->printSetting();
    delete pRecive;
    std::cout << "\n";

    std::cout << "Settings from board directly:\n";
    pRecive = scorbot->getSetting_board();
    pRecive->printSetting();
    delete pRecive;
    std::cout << "============================================================\n";

    /// Data test
    int i = 0;
    EncoderMot *e;
    CurrentMot *c;
    AllSensor *allS;
//    scorbot->setSampleTimeCur(30 * 1000UL);
    scorbot->setSampleTimeCur(50 * 1000UL);
    struct timespec lastPackT, newPackT, deltaPackT;
    clock_gettime(CLOCK_MONOTONIC_RAW, &lastPackT);
    timerclearSpec(&deltaPackT);
    for (;;) {
        e = scorbot->getValidEncoderWait(&newPackT);
//        c = scorbot->getValidCurrentWait(&newPackT);
        timersubSpec(&newPackT, &lastPackT, &deltaPackT);
        timeStampSpec(&deltaPackT, "deltaPackT");
        lastPackT = newPackT;
        std::cout << "\n\t##Recived:\n";
        e->printEncoder();
//        c->printCurrent();
        i++;
        if (i == 100) {
//            scorbot->setSampleTimeCur(10 * 1000UL);
            scorbot->setSampleTimeEn(1 * 1000UL);
        }
        delete e;
//        delete c;
        std::cout << i << "\n";
        std::cout << "\n";
    }
    return 0;
}