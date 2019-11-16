//
// Created by alfyhack on 15/11/19.
//

#ifndef PCLISTENUART_ADAPTERFACTORY_H
#define PCLISTENUART_ADAPTERFACTORY_H

#include <string>
#include <AdapterClasses/ComUartAdapter.h>

class AdapterFactory {  //abstract class
public:
    static ComUartAdapter &makeUart(const std::string &device) noexcept(false);
    static ComUartAdapter &makeUart(const std::string &device, int uartSpeed) noexcept(false);

    AdapterFactory() = delete;
};

#endif //PCLISTENUART_ADAPTERFACTORY_H
