//
// Created by alfyhack on 27/11/19.
//

#ifndef SCORBOTUI_DEMO_FREEMOVEWINSOW_H
#define SCORBOTUI_DEMO_FREEMOVEWINSOW_H

/// Qt lib
#include <QDialog>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QRadioButton>

/// SystemLib
#include <DataTransfert_AllInclude.h>
#include <iostream>

namespace Ui {
    class FreeMoveWindow; //Nome del windget radice nel file ui
}
using namespace DataPrimitive;
using namespace DataManipolation;

class FreeMoveWindow : public QDialog {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

public:
    explicit FreeMoveWindow(QWidget *parent = 0);

    ~FreeMoveWindow();
//private: slots

    Ui::FreeMoveWindow *ui;

    void hideEvent(QHideEvent *);

    void showEvent(QShowEvent *);

signals:

    void widgetVisibilityChanged(bool);

};


class freeMoveWindow {

};

#endif //SCORBOTUI_DEMO_FREEMOVEWINSOW_H
