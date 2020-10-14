//
// Created by alfyhack on 18/03/20.
//

#ifndef PCLISTENUART_OBSERVABLESCORBOT_H
#define PCLISTENUART_OBSERVABLESCORBOT_H

#include "ObserverScorbot.h"
#include <dataPrimitive.h>
#include <vector>

using namespace DataPrimitive;

class ObservableScorbot{
protected:
    std::vector <ObserverScorbot *> *settingBoardDataNotify;
    std::vector <ObserverScorbot *> *mEncoderDataNotify;
    std::vector <ObserverScorbot *> *mCurrentDataNotify;
public:
    ObservableScorbot (){
        settingBoardDataNotify = new std::vector <ObserverScorbot *>;
        mEncoderDataNotify = new std::vector <ObserverScorbot *>;
        mCurrentDataNotify = new std::vector <ObserverScorbot *>;
    }

    virtual void add (ObserverScorbot *ob, uartPackType wantedType){
        switch (wantedType){
            case settingBoardData:
                settingBoardDataNotify->push_back(ob);
                break;
            case mEncoderData:
                mEncoderDataNotify->push_back(ob);
                break;
            case mCurrentData:
                mCurrentDataNotify->push_back(ob);
                break;
            case mAllData:
                mEncoderDataNotify->push_back(ob);
                mCurrentDataNotify->push_back(ob);
                break;
            default:
                fprintf(stderr, "Notifica desiderata impossibile:%d\n", wantedType);
                break;
        }
    }

    //    void virtual remove(ObserverScorbot ob);

    void notifySettingBoard (){
        // Itera e stampa i valori del vector
        for (ObserverScorbot *ob : *settingBoardDataNotify){
            ob->updateSettingBoard();
        }
    }

    void notifyCurrentData (){
        // Itera e stampa i valori del vector
        for (ObserverScorbot *ob : *mCurrentDataNotify){
            ob->updateCurrentData();
        }
    }

    void notifyEncoderData (){
        // Itera e stampa i valori del vector
        for (ObserverScorbot *ob : *mEncoderDataNotify){
            ob->updateEncoderData();
        }
    }
};

#endif //PCLISTENUART_OBSERVABLESCORBOT_H
