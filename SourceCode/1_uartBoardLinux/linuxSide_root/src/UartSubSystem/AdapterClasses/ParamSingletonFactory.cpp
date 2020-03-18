//
// Created by alfyhack on 15/11/19.
//

#include "ParamSingletonFactory.h"
#include "SingletonFactoryException.h"

//initiaize static variables here
ParamSingletonFactory *ParamSingletonFactory::instance = nullptr;
std::mutex myMutex;

ParamSingletonFactory &ParamSingletonFactory::getInstance() {
    std::lock_guard<std::mutex> myLock(myMutex);
    if (!ParamSingletonFactory::instance) {
        ParamSingletonFactory::instance = new ParamSingletonFactory();
    }
    return *ParamSingletonFactory::instance;
}

UartDriver *ParamSingletonFactory::getUartClass(const std::string &device) noexcept(false) {
    /// Search fase:
    for (int i = 0; i < lenUartList; ++i) {
        if (this->UartList[i].UartParams->compare(device) == 0) {  //Uart found
            return this->UartList[i].uart;
        }
    }
    /// No one found, create new uart:
    //Extend list size
    lenUartList++;
    this->UartList = (uartNode *) reallocarray(this->UartList, lenUartList, sizeof(uartNode));

    //Create the new device, if not create exeption continue
    this->UartList[lenUartList - 1].uart = new UartDriver(device);    /// Can create Exeption!!!
    this->UartList[lenUartList - 1].UartParams = new std::string(device);
    //this->UartList[lenUartList - 1].UartParams.assign(device);
    //Return the new device
    return this->UartList[lenUartList - 1].uart;
}

UartDriver *ParamSingletonFactory::getLastUartClass() noexcept(false) {
    if (lenUartList > 0)
        return this->UartList[lenUartList - 1].uart;
    else
        throw SingletonFactoryException("Non è presente ancora nessuan Uart installata!!");
}

ParamSingletonFactory::ParamSingletonFactory() {
    this->UartList = nullptr;
    this->lenUartList = 0;

}
