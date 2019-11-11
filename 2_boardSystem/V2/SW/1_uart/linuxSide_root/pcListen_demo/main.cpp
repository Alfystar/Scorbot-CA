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
    for (;;) {
        //std::cout<<"loop\n";
        if (uart->Available())
            UartDriver::serialPackDb(*uart->getLastRecive());
    }

    return 0;
}