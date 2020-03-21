//
// Created by alfyhack on 20/03/20.
//

#ifndef SCORBOTUI_DEMO_UARTCHOISE_H
#define SCORBOTUI_DEMO_UARTCHOISE_H


/// Qt lib
#include <QDialog>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QRadioButton>
#include <QtWidgets/QMessageBox>

/// SystemLib
#include <DataTransfert_AllInclude.h>
#include <iostream>

namespace Ui {
    class UartChoise; //Nome del windget radice nel file ui
}
using namespace DataPrimitive;
using namespace DataManipolation;


class UartChoise : public QDialog {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

public:
    UartChoise(QWidget *parent);

signals:
    void uartChoised();
private slots:
    void acceptedParams();
void serialFind_handler();
protected:
    Ui::UartChoise *ui;


};

#endif //SCORBOTUI_DEMO_UARTCHOISE_H
