//
// Created by alfyhack on 21/03/20.
//

#include "SetupBoard.h"
#include "scorbotUi/ui_source/ui_settingBoardWindow.h"

SetupBoard::SetupBoard (MainWindow *parent) : QObject(parent){
    win = parent;
    connect(win->setBoardWin->ui->buttonBox, SIGNAL(accepted()), this, SLOT(settingBoardSend()));
    connect(win->setBoardWin->ui->loadSetting, SIGNAL(clicked()), this, SLOT(settingBoardLoad()));
    connect(win->setBoardWin->ui->restoreSetting, SIGNAL(clicked()), this, SLOT(settingBoardRestored()));

    scorInterface = &ComUartAdapter::getInstance();
}

void SetupBoard::settingBoardSend (){
    if (!scorInterface->isConnect())
        return;
    scorInterface->setSetting(*win->setBoardWin->setting);
    std::cout << "[SetupBoard::settingBoardSend] Sending to board the params:" << std::endl;
    win->setBoardWin->setting->printSetting();
}

void SetupBoard::settingBoardLoad (){
    if (!scorInterface->isConnect())
        return;
    win->setBoardWin->setting->copyPack(*scorInterface->getSetting_board());
    //Visualizzo sulla finestra, e aggiorno ScoreCalc
    win->setBoardWin->settingShow(win->setBoardWin->setting);
}

void SetupBoard::settingBoardRestored (){
    win->setBoardWin->setting->setMotorLimit(Mot1, 24000, -19000, 4168);
    win->setBoardWin->setting->setMotorLimit(Mot2, 16000, -500, 4168);
    win->setBoardWin->setting->setMotorLimit(Mot3, 20000, -8000, 4168);
    win->setBoardWin->setting->setMotorLimit(Mot4, 10000, -10000, 4168);
    win->setBoardWin->setting->setMotorLimit(Mot5, 10000, -10000, 4168);
    win->setBoardWin->setting->setMotorLimit(Mot6, 10000, -10000, 4168);

    //    win->setBoardWin->setting->setMotorLimit(Mot1, 2160, 24300, 4168);
    //    win->setBoardWin->setting->setMotorLimit(Mot2, 2960, 16200, 1040);
    //    win->setBoardWin->setting->setMotorLimit(Mot3, 2960, 21900, 4168);
    //    win->setBoardWin->setting->setMotorLimit(Mot4, 2160, 10000, 4168);
    //    win->setBoardWin->setting->setMotorLimit(Mot5, 2400, 10000, 4168);
    //    win->setBoardWin->setting->setMotorLimit(Mot6, 2160, 5770, 208);
    win->setBoardWin->setting->setAdcDiff(false);
    win->setBoardWin->setting->setAdcRef(in1V1);
    win->setBoardWin->setting->setPWMfreq(hz4k);
    //Visualizzo sulla finestra, e aggiorno ScoreCalc
    win->setBoardWin->settingShow(win->setBoardWin->setting);
}
