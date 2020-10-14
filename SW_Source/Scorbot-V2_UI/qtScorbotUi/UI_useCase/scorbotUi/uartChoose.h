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
#include <dataTransfert_AllInclude.h>
#include <iostream>

namespace Ui {
    class UartChoose; //Nome del windget radice nel file ui
}
using namespace DataPrimitive;
using namespace DataManipolation;

class UartChoose : public QDialog{
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

public:
    UartChoose (QWidget *parent);

signals:
    void uartChoised ();
private slots:
    void acceptedParams ();
    void serialFind_handler ();
protected:
    Ui::UartChoose *ui;
};

#endif //SCORBOTUI_DEMO_UARTCHOISE_H
