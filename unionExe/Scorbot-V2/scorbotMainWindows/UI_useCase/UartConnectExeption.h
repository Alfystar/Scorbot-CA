//
// Created by alfyhack on 15/10/19.
//

#ifndef UART_CONNECT_EXEPTION_H
#define UART_CONNECT_EXEPTION_H

#include <exception>
#include <string>

//Exeption tree
class UartConnectExeption : public std::exception {
    std::string _msg;
public:
    UartConnectExeption(const std::string &msg) : _msg(msg) {}

    virtual const char *what() const noexcept override {
        std::string tipo = "UartConnectExeption";
        return tipo.append(_msg).c_str();
    }
};

#endif //UART_CONNECT_EXEPTION_H
