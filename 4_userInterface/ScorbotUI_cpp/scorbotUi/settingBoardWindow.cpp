//
// Created by alfyhack on 27/11/19.
//

#include "settingBoardWindow.h"
#include "ui_source/ui_settingBoardWindow.h"

SettingBoardWindow::SettingBoardWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SettingBoardWindow) {
    ui->setupUi(this);

}

SettingBoardWindow::~SettingBoardWindow() {

}
