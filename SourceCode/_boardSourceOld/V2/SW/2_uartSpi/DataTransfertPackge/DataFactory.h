//
// Created by alfyhack on 15/10/19.
//

#ifndef SPIRASP_TERMINAL_DATAFACTORY_H
#define SPIRASP_TERMINAL_DATAFACTORY_H

#include "DataPrimitive.h"
#include "DataManipolation/CurrentMot.h"
#include "DataManipolation/EncoderMot.h"
#include "DataManipolation/AllSensor.h"
#include "DataManipolation/SpeedMot.h"
#include "DataManipolation/SettingBoard_C.h"
#include "DataManipolation/Pack.h"

namespace dataFactory {
    using namespace DataPrimitive;
    using namespace DataManipolation;
/// Primitive factory
    mSpeed &makeMSpeed();
    void freeMSpeed(mSpeed *p);

    settingsBoard &makeSettingBoard();
    void freeSettingBoard(settingsBoard *p);

    mCurrent &makeMCurrent();
    void freeMCurrent(mCurrent *p);

    mEncoder &makeMEncoder();
    void freeMEncoder(mEncoder *p);

    mAll &makeMAll();
    void freeMAll(mAll *p);

    SPIPACK &makeSPIPACK();
    void freeSPIPACK(SPIPACK *p);

    uart2Ard &makeUart2Ard();
    void freeUart2Ard(uart2Ard *p);

    uart2Rasp &makeUart2Rasp();
    void freeUart2Rasp(uart2Rasp *p);
};
#endif //SPIRASP_TERMINAL_DATAFACTORY_H
