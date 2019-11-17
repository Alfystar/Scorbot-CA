//
// Created by alfyhack on 15/11/19.
//

#include "AdapterFactory.h"

ComUartAdapter &AdapterFactory::makeUart(const std::string &device) {
    return ComUartAdapter::getInstance(device);
}

ComUartAdapter &AdapterFactory::makeUart(const std::string &device, speed_t uartSpeed) {
    ComUartAdapter &p = ComUartAdapter::getInstance(device);
    p.changeDeviceVel(uartSpeed);
    return p;
}
