//
// Created by alfyhack on 27/11/19.
//

#include "settingBoardWindow.h"
#include "ui_source/ui_settingBoardWindow.h"

SettingBoardWindow::SettingBoardWindow (QWidget *parent) : QDialog(parent), ui(new Ui::SettingBoardWindow){
    ui->setupUi(this);
    calc = new ScoreCalc();
    setting = new SettingBoard_C();
    enMin[Mot1] = ui->en1Min;
    enMin[Mot2] = ui->en2Min;
    enMin[Mot3] = ui->en3Min;
    enMin[Mot4] = ui->en4Min;
    enMin[Mot5] = ui->en5Min;
    enMin[Mot6] = ui->en6Min;
    enMax[Mot1] = ui->en1Max;
    enMax[Mot2] = ui->en2Max;
    enMax[Mot3] = ui->en3Max;
    enMax[Mot4] = ui->en4Max;
    enMax[Mot5] = ui->en5Max;
    enMax[Mot6] = ui->en6Max;
    CurMedMax[Mot1] = ui->curM1;
    CurMedMax[Mot2] = ui->curM2;
    CurMedMax[Mot3] = ui->curM3;
    CurMedMax[Mot4] = ui->curM4;
    CurMedMax[Mot5] = ui->curM5;
    CurMedMax[Mot6] = ui->curM6;
    connect(ui->restoreSetting, SIGNAL(clicked()), this, SLOT(scorParamReset_handler()));
    scorParamReset_handler();
    settingShow(setting);

    for (int i = Mot1; i < nMot; ++i){
        connect(enMin[i], SIGNAL(valueChanged(int)), this, SLOT(updateSetting()));
        connect(enMax[i], SIGNAL(valueChanged(int)), this, SLOT(updateSetting()));
        connect(CurMedMax[i], SIGNAL (valueChanged(double)), this, SLOT (updateSetting()));
    }
    connect(ui->in1V1, SIGNAL(clicked()), this, SLOT(updateSetting()));
    connect(ui->in2V56, SIGNAL(clicked()), this, SLOT(updateSetting()));
    connect(ui->ext, SIGNAL(clicked()), this, SLOT(updateSetting()));
    connect(ui->offsetChose, SIGNAL(activated(int)), this, SLOT(updateSetting()));
    connect(ui->motFreqChose, SIGNAL(activated(int)), this, SLOT(updateSetting()));
}

SettingBoardWindow::~SettingBoardWindow (){
}

void SettingBoardWindow::settingShow (SettingBoard_C *s){
    setting->copyPack(*s);

    for (int i = Mot1; i < nMot; ++i){
        enMin[i]->blockSignals(true);
        enMax[i]->blockSignals(true);
        CurMedMax[i]->blockSignals(true);
    }
    ui->in1V1->blockSignals(true);
    ui->in2V56->blockSignals(true);
    ui->ext->blockSignals(true);
    ui->offsetChose->blockSignals(true);
    ui->motFreqChose->blockSignals(true);

    switch (setting->getSetting().adcVref){
        case in1V1:
            ui->in1V1->setChecked(true);
            calc->vRefSet(1.1);
            break;
        case in2V56:
            ui->in2V56->setChecked(true);
            calc->vRefSet(2.56);
            break;
        case ext:
            ui->ext->setChecked(true);
            //Se sono qua, inserirò a mano o è già stato inserito il valore correto
            break;
    }
    ui->offsetChose->setCurrentIndex((int) setting->getSetting().diff);
    ui->motFreqChose->setCurrentIndex(setting->getSetting().freq);
    for (int i = Mot1; i < nMot; ++i){
        enMin[i]->setValue(setting->getSetting().minEn[i]);
        enMax[i]->setValue(setting->getSetting().maxEn[i]);
        //Conversione per portarlo da somma di otto valori di adc, a una corrente in mA
        CurMedMax[i]->setValue(calc->adc2curr(setting->getSetting().maxCurrMed[i] / 8) * 1000);
    }

    for (int i = Mot1; i < nMot; ++i){
        enMin[i]->blockSignals(false);
        enMax[i]->blockSignals(false);
        CurMedMax[i]->blockSignals(false);
    }
    ui->in1V1->blockSignals(false);
    ui->in2V56->blockSignals(false);
    ui->ext->blockSignals(false);
    ui->offsetChose->blockSignals(false);
    ui->motFreqChose->blockSignals(false);
}

ScoreCalc *SettingBoardWindow::getScorCalcSetuped (){
    return this->calc;
}

void SettingBoardWindow::updateSetting (){
    if (ui->in1V1->isChecked())
        setting->setAdcRef(in1V1);
    else if (ui->in2V56->isChecked())
        setting->setAdcRef(in2V56);
    else if (ui->ext->isChecked()){
        setting->setAdcRef(ext);
        double volt = QInputDialog::getDouble(this, "Voltage Trim Reference", "External Voltage Reference Read:");
        calc->vRefSet(volt);    // Imposto il vRef della scheda
    }
    setting->setAdcDiff(ui->offsetChose->currentIndex() == 1);
    setting->setPWMfreq((pwmFreq) ui->motFreqChose->currentIndex());
    for (int i = Mot1; i < nMot; ++i){
        setting->setMinEn((motCode) i, (short) enMin[i]->value());
        setting->setMaxEn((motCode) i, (short) enMax[i]->value());
        //Conversione per portarlo da una corrente in mA nella somma di otto valori di adc,
        setting->setMaxCurrentMed((motCode) i, (short) calc->curr2adc(CurMedMax[i]->value() / 1000.0) * 8);
    }
    setting->printSetting();
}

void SettingBoardWindow::scorParamReset_handler (){
    // todo: Funzione mock presente per far succeder qualcosa a seriale scollegata, da togliere
    //Setting per ora di default
    //curr neg => no limit
    setting->setMotorLimit(Mot1, 24300, 2160, 4168);
    setting->setMotorLimit(Mot2, 16200, 2960, 1040);
    setting->setMotorLimit(Mot3, 21900, 2960, 4168);
    setting->setMotorLimit(Mot4, 10000, 2160, 4168);
    setting->setMotorLimit(Mot5, 10000, 2400, 4168);
    setting->setMotorLimit(Mot6, 5770, 2160, 208);
    setting->setAdcDiff(false);
    setting->setAdcRef(in1V1);
    setting->setPWMfreq(hz4k);
    this->settingShow(setting);
}