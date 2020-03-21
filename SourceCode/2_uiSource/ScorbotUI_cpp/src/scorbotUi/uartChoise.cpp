//
// Created by alfyhack on 20/03/20.
//

#include "uartChoise.h"
#include "ui_source/ui_uartChoise.h"

UartChoise::UartChoise(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::UartChoise) {
    ui->setupUi(this);
    connect(ui->serial_find, SIGNAL (clicked()), this, SLOT (serialFind_handler()));

    connect(ui->buttonBox, SIGNAL (accepted()), this, SLOT (acceptedParams()));
}

void UartChoise::acceptedParams() {
    if(!ui->uartFind->currentText().toStdString().empty()){
        emit uartChoised();
        this->hide();
    } else{
        QMessageBox msgWarning;
        msgWarning.setText("WARNING!\nSelect UartPort");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
    }

}

void UartChoise::serialFind_handler() {
    std::cout << "serialFind_handler" << "\n";
    //remove all list exept first
    QList<QAction *> list = ui->uartFind->actions();
    for (int i = 1; i < list.count(); i++) {
        ui->uartFind->removeAction(list[i]);
    }
    FILE *fp;
    char path[4066];

    /* Open the command for reading. */
    fp = popen("realpath /dev/serial/by-id/*  2>/dev/null", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(-1);
    }
    /* Read the output a line at a time - output it. */
    QAction *newAct;
    std::string s;
    while (fgets(path, sizeof(path), fp) != NULL) {
        //remove new line from return
        for (char *i = path; *i != 0; ++i) {
            if (*i == '\n') *i = 0;
        }
        std::cout << path <<"\n";
        newAct = new QAction(path);
        newAct->setCheckable(true);
        ui->uartFind->addItem(path);
    }
    /* close */
    pclose(fp);
}

