//
// Created by alfyhack on 18/03/20.
//

#ifndef PCLISTENUART_OBSERVERSCORBOT_H
#define PCLISTENUART_OBSERVERSCORBOT_H

class ObserverScorbot{
public:
    virtual void updateSettingBoard () = 0;
    virtual void updateCurrentData () = 0;
    virtual void updateEncoderData () = 0;
};

#endif //PCLISTENUART_OBSERVERSCORBOT_H
