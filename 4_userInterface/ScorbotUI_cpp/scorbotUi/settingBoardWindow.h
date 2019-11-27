//
// Created by alfyhack on 27/11/19.
//
#ifndef SCORBOTUI_DEMO_SETTINGBOARDWINDOW_H
#define SCORBOTUI_DEMO_SETTINGBOARDWINDOW_H



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
    class SettingBoardWindow; //Nome del windget radice nel file ui
}
using namespace DataPrimitive;
using namespace DataManipolation;

class SettingBoardWindow : public QDialog {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

public:
    explicit SettingBoardWindow(QWidget *parent = 0);
    ~SettingBoardWindow();
//private: slots

private:
    Ui::SettingBoardWindow *ui;


};

#endif //SCORBOTUI_DEMO_SETTINGBOARDWINDOW_H
