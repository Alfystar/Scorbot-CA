//
// Created by alfyhack on 15/11/19.
//
// Questa classe ha la responsabilità di istanziare 1 sola classe di comunicazione per porta seriale.
// Essendo possibile avere diverse porte seriali con la stessa procedura, la responsabilità di sitanziazione
// ricade su questa classe che di ogni parametro ne crea solo 1 e poi ricondivide il puntatore, per la teoria vedere:
// http://www.jot.fm/issues/issue_2007_03/column2/

#ifndef PCLISTENUART_PARAMSINGLETONFACTORY_H
#define PCLISTENUART_PARAMSINGLETONFACTORY_H

#include <string>
#include <UartDriver.h>
#include <mutex>
#include "SingletonFactoryException.h"

using namespace Uart;

struct uartNode {
    UartDriver *uart;
    std::string *UartParams;

};

class ParamSingletonFactory {
public:
    static ParamSingletonFactory &getInstance();

    // Generate 1 class for device
    UartDriver *getUartClass(const std::string &device) noexcept(false);
    UartDriver *getLastUartClass() noexcept(false);
    //todo: destroy node

private:
    static ParamSingletonFactory *instance;
    int lenUartList;
    uartNode *UartList; //for now static, in general should encrease and reduce
    //uartNode UartList[10]; //for now static, in general should encrease and reduce

    ParamSingletonFactory();

};

#endif //PCLISTENUART_PARAMSINGLETONFACTORY_H
