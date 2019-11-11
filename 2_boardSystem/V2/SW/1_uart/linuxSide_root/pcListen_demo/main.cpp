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
    try {
        uart = new UartDriver("/dev/ttyACM0");
    } catch (exception e) {
        e.what();
        exit(-1);
    }

    uart2Rasp *dato;
    for (;;) {
        // Lettura non bloccante, Consuma molta CPU, ma è prestante
//        if ((dato = uart->getLastRecive()) != nullptr){
//            UartDriver::serialPackDb(*dato);
//            std::cout << "\n";
//        }

        // Leggo ultimo dato, se non è arrivato il thread viene messo in wait, fino all'arrivo
        UartDriver::serialPackDb(*uart->getLastReciveWait());
        std::cout << "\n";
        uart->packSend(settingAsk, nullptr);
    }
    return 0;
}