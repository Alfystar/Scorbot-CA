//
// Created by alfyhack on 27/11/19.
//

#include "freeMoveWindow.h"
#include "ui_source/ui_freeMoveWindow.h"

FreeMoveWindow::FreeMoveWindow (QWidget *parent) : QDialog(parent), ui(new Ui::FreeMoveWindow){
    ui->setupUi(this);
}

FreeMoveWindow::~FreeMoveWindow (){
}

void FreeMoveWindow::hideEvent (QHideEvent *){
    // 'false' means hidden..
    emit widgetVisibilityChanged(false);
}

void FreeMoveWindow::showEvent (QShowEvent *){
    // 'true' means visible..
    emit widgetVisibilityChanged(true);
}