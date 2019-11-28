//
// Created by alfyhack on 12/11/19.
//

#ifndef PCLISTENUART_CONCRETEGETCOM_H
#define PCLISTENUART_CONCRETEGETCOM_H

#include <DataTransfert_AllInclude.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class GetCom_int {
public:
    //GetCom_int() {};
    //~GetCom_int() {};
    virtual EncoderMot &getEncoderConrete() = 0;
    virtual CurrentMot &getCurrentConrete() = 0;
//    virtual AllSensor &getSensorConrete() = 0;
    virtual SettingBoard_C &getSettingConrete() = 0;

};

#endif //PCLISTENUART_CONCRETEGETCOM_H
