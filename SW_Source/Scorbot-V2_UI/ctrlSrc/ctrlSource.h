//
// Created by alfystar on 11/10/20.
// Qui va definita e codificata la funzione di controllo automatica dello scorbot
//

#ifndef SCORBOTTERMINAL_CTRLSOURCE_H
#define SCORBOTTERMINAL_CTRLSOURCE_H

#include <dataTransfert_AllInclude.h>
#include <uartSubSystem.h>
#include <PIDScorbot.h>

namespace CTRL {
    void setup (ScorInterface *scorInterface);
    SpeedMot &loop (EncoderMot *refPid, EncoderMot *enFeed);
}


#endif //SCORBOTTERMINAL_CTRLSOURCE_H
