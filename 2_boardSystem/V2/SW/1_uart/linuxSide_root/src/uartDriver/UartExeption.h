//
// Created by alfyhack on 10/11/19.
//

#ifndef PCLISTENUART_UARTEXEPTION_H
#define PCLISTENUART_UARTEXEPTION_H

#include <exception>
#include <string>
#include <cstring>

//Exeption tree
namespace Uart {
    class UartExeption : public std::exception {
        std::string _msg;
    public:
        UartExeption(const std::string &msg) : _msg(msg) {}

        UartExeption(const std::string &msg, int errCode) {
            std::string err = "\nerrno:";
            err += strerror(errCode);
            this->_msg = msg + err;
        }

        virtual const char *what() const noexcept override {
            std::string tipo = "UartExeption";
            return tipo.append(_msg).c_str();
        }
    };
}
#endif //PCLISTENUART_UARTEXEPTION_H
