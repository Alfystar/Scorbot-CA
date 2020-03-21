//
// Created by alfyhack on 21/03/20.
//

#include "DataShow.h"
#include "uiSrc/scorbotUi/ui_source/ui_mainwindow.h"      //classe generata dal file di designer in automatico dal cmake

DataShow::DataShow(MainWindow *parent): QObject(parent){
    this->win = parent;

    this->scorInterface = &ComUartAdapter::getInstance();
    this->obs = new ConcreteObserver(scorInterface);

    updateEnTh = new std::thread(this->updateThEnMain, this);
    updateCurTh = new std::thread(this->updateThCurMain, this);
}

void DataShow::updateThEnMain(DataShow *d) {
    while (!d->scorInterface->isConnect())
        sleep(1);
    d->obs->enableEncoderData(true);
    EncoderMot *enRecive;
    while (true){
        enRecive = d->obs->getValidEncoderWait();
        d->win->encoderShow(enRecive);
    }
}

void DataShow::updateThCurMain(DataShow *d) {
    while (!d->scorInterface->isConnect())
        sleep(1);
    d->obs->enableCurrentData(true);
    CurrentMot *curRecive;
    while (true){
        curRecive = d->obs->getValidCurrentWait();
        d->win->currentShow(curRecive);
    }
}
