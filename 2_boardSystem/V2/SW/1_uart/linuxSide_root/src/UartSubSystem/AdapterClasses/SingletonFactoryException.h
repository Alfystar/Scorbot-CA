//
// Created by alfyhack on 10/11/19.
//

#ifndef SINGLETONFACTORYEXC_H
#define SINGLETONFACTORYEXC_H

#include <exception>
#include <string>
#include <cstring>

#define excType "SingletonFactoryExepion :"

//Exeption tree
class SingletonFactoryException : virtual public std::exception {
    const std::string _msg;
public:
    SingletonFactoryException(const std::string &msg) : _msg(std::string(excType).append(msg)) {}

    virtual ~SingletonFactoryException() noexcept {}

    const char *what() const noexcept override {
        //std::cout<<"dentro what\n"<< tipo.append(_msg).c_str();
        return _msg.c_str();
    }
};

#endif //SINGLETONFACTORYEXC_H
