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
#include <QtWidgets/QInputDialog>

/// SystemLib
#include <dataTransfert_AllInclude.h>
#include <ScorCalc.h>
#include <iostream>

namespace Ui {
    class SettingBoardWindow; //Nome del windget radice nel file ui
}
using namespace DataPrimitive;
using namespace DataManipolation;

class SettingBoardWindow : public QDialog{
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

    QSpinBox *enMin[nMot];
    QSpinBox *enMax[nMot];
    QDoubleSpinBox *CurMedMax[nMot];
    ScoreCalc *calc;
protected:
public:
    Ui::SettingBoardWindow *ui;
    SettingBoard_C *setting;
    explicit SettingBoardWindow (QWidget *parent = 0);
    ~SettingBoardWindow ();
    void settingShow (SettingBoard_C *s);
    ScoreCalc *getScorCalcSetuped ();

private slots:

    void updateSetting ();
    void scorParamReset_handler ();

private:
};

#endif //SCORBOTUI_DEMO_SETTINGBOARDWINDOW_H
