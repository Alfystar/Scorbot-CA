//
// Created by alfyhack on 12/11/19.
//

#ifndef PCLISTENUART_SCORINTERFACE_H
#define PCLISTENUART_SCORINTERFACE_H

#include <DataTransfert_AllInclude.h>
#include <InfoExpPack.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class ScorInterface {
public:
    virtual ~ScorInterface() {};
    /// Set Data
    virtual void goHome();
    virtual void sendVel(SpeedMot &sp);
    virtual void setSetting(SettingBoard_C &set);
    virtual void setSampleTimeEn(int sEn);
    virtual void setSampleTimeCur(int sCur);

    /// Get data
    // Return the last recive value
    virtual EncoderMot &getEncoder();
    virtual CurrentMot &getCurrent();
    virtual AllSensor &getSensor();
    virtual SettingBoard_C &getSetting_local();     //last send board data
    virtual SettingBoard_C &getSetting_board();     //ask directly to board

    /// Valid question
    virtual bool isEncoderValid();      //true if Now <= LastPack+enSample
    virtual bool isCurrentValid();      //true if Now <= LastPack+curSample
    virtual bool isAllSensorValid();    //true if Encoder and Current in time

    /// Valid Get data
    // If sample time is out wait new data or ask for new data,
    // depend by comunication protocol implemented
    // other wise the thread are mooved on wait state
    virtual EncoderMot &getValidEncoder();
    virtual CurrentMot &getValidCurrent();
    virtual AllSensor &getValidSensor();
private:
    const InfoExpPack *exp;

};

#endif //PCLISTENUART_SCORINTERFACE_H
