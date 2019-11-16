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
    try {
//        scorbot = &AdapterFactory::makeUart("/dev/ttyACM0",B115200);
        scorbot = &AdapterFactory::makeUart("/dev/ttyACM0", B921600);

    } catch (const std::exception &e) {
        // speciffic handling for all exceptions extending std::exception, except
        // std::runtime_error which is handled explicitly
        std::cerr << e.what() << std::endl;
        exit(-1);
    }
    scorbot->setSampleTimeEn(100000);
    scorbot->setSampleTimeCur(1000 * 1000UL);
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
    p->printSetting();
    int i = 0;
    EncoderMot *e = new EncoderMot();
    struct timespec lastPack, newPack, deltaPack;
    clock_gettime(CLOCK_MONOTONIC_RAW, &lastPack);
    timerclearSpec(&deltaPack);
    for (;;) {
        e->copyEn(scorbot->getValidEncoderWait(&newPack));
        timersubSpec(&newPack, &lastPack, &deltaPack);
        timeStampSpec(&deltaPack, "deltaPack");
        lastPack = newPack;
        std::cout << "\n\t##Recived:\n";
        e->printEncoder();
        i++;
        if (i > 100)
            scorbot->setSampleTimeEn(5 * 1000UL);
        std::cout << i << "\n";
        std::cout << "\n";
    }
    return 0;
}