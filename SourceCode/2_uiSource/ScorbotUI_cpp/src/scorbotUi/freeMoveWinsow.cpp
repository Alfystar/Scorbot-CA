//
// Created by alfyhack on 27/11/19.
//

#include "freeMoveWinsow.h"
#include "ui_source/ui_freeMoveWindow.h"

FreeMoveWindow::FreeMoveWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::FreeMoveWindow) {
    ui->setupUi(this);

}

FreeMoveWindow::~FreeMoveWindow() {

}
