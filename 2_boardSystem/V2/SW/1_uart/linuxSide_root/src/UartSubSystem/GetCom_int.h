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
    virtual ~GetCom_int() {};
    virtual EncoderMot &getEncoterConrete();
    virtual CurrentMot &getCurrentConrete();
    virtual AllSensor &getSensorConrete();
    virtual SettingBoard_C &getSettingConrete();

};

#endif //PCLISTENUART_CONCRETEGETCOM_H
