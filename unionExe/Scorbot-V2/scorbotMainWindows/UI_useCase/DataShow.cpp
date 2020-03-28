//
// Created by alfyhack on 21/03/20.
//

#include "DataShow.h"
#include "uiSrc/scorbotUi/ui_source/ui_mainwindow.h"      //classe generata dal file di designer in automatico dal cmake

DataShow::DataShow(MainWindow *parent) : QObject(parent) {
    this->win = parent;

    this->scorInterface = &ComUartAdapter::getInstance();
    this->obs = new ConcreteObserver(scorInterface);

    this->enOffset = new EncoderMot();

    connect(win->ui->scorSwHome, SIGNAL(clicked()), this, SLOT(swHome_handler()));
    for (int i = 0; i < nMot; ++i) {
        connect(win->enHome[i], SIGNAL(valueChanged(int)), this, SLOT(setHome_handler()));
    }
    updateEnTh = new std::thread(this->updateThEnMain, this);
    updateCurTh = new std::thread(this->updateThCurMain, this);
}

void DataShow::updateThEnMain(DataShow *d) {
    while (!d->scorInterface->isConnect())
        sleep(1);
    d->obs->enableEncoderData(true);
    EncoderMot *enRecive;
    while (true) {
        enRecive = d->obs->getValidEncoderWait();
        d->win->encoderShow(enRecive, d->enOffset);
    }
}

void DataShow::updateThCurMain(DataShow *d) {
    while (!d->scorInterface->isConnect())
        sleep(1);
    d->obs->enableCurrentData(true);
    CurrentMot *curRecive;
    while (true) {
        curRecive = d->obs->getValidCurrentWait();
        d->win->currentShow(curRecive);
    }
}

void DataShow::setHome_handler() {
    for (int i = 0; i < nMot; ++i) {
        enOffset->enSet((motCode) i, win->enHome[i]->value());
    }

}

void DataShow::swHome_handler() {
    enOffset->copyEn(win->feedBack->getEn());   // Ricarico uno degli ultimi pacchetti inviati
    for (int i = 0; i < nMot; ++i) {
        win->enHome[i]->blockSignals(true);
        win->enHome[i]->setValue(enOffset->getEn((motCode) i));
        win->enHome[i]->blockSignals(false);
    }
}