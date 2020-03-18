//
// Created by alfyhack on 15/03/20.
//

#include "UartConnect.h"
#include "uiSrc/scorbotUi/ui_source/ui_mainwindow.h" //classe generata dal file di designer in automatico dal cmake

UartConnect::UartConnect(MainWindow *parent) : QObject(parent) {
    std::cout << "UartConnect constructor\n";
    this->win = parent;
    //this->ui->menuSerialPort->exec();
    connect(win->ui->menuSerialPort, SIGNAL (triggered(QAction * )), this, SLOT (serialPort_handler(QAction * )));
    connect(win->ui->actionSerial_Find, SIGNAL(triggered()), this, SLOT(serialSearch_handler()));
    connect(win->ui->actionConnection_Start, SIGNAL (triggered()), this, SLOT (serialConnect_handler()));
    connect(win->ui->actionClose_connection, SIGNAL (triggered()), this, SLOT (closeConnection_handler()));
    win->ui->actionClose_connection->setDisabled(true);
    connect(win->ui->actionReset_Board, SIGNAL (triggered()), this, SLOT (resetBoard_handler()));

}

UartConnect::~UartConnect() {

}


void UartConnect::serialPort_handler(QAction *action) {
    QList<QAction *> list = win->ui->menuSerialPort->actions();
    for (int i = 1; i < list.count(); i++) {
        if (list[i]->isChecked()) {
            uartPath = list[i]->text().toStdString();
            std::cout << "serialPort_handler:\n" << uartPath << "\n";
            break;
        }
    }
}

void UartConnect::serialSearch_handler() {
    std::cout << "serialSearch_handler" << "\n";
    //remove all list exept first
    QList<QAction *> list = win->ui->menuSerialPort->actions();
    for (int i = 1; i < list.count(); i++) {
        win->ui->menuSerialPort->removeAction(list[i]);
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
        newAct = new QAction(path);
        newAct->setCheckable(true);
        win->ui->menuSerialPort->addAction(newAct);
    }
    /* close */
    pclose(fp);
}

void UartConnect::serialConnect_handler() {
    std::cout << "serialConnect_handler : \n" << uartPath << "\n";

    /// Comunicazione avvio
    try {
        scorInterface = &AdapterFactory::makeUart(uartPath, B115200);

    } catch (const std::exception &e) {
        QMessageBox::warning(win, tr("Scorbot Connection"), tr(e.what()));
        return;
    }

    /// Controllo avvio
//    ctrl = new std::thread(ctrlTh, this);

    //Per ora li disattivo pechè una volta creata la seriale non posso ancora chiuderla e cambiarla
    win->ui->actionConnection_Start->setDisabled(true);
    win->ui->menuSerialPort->setDisabled(true);

}

void UartConnect::closeConnection_handler() {
    std::cout << "closeConnection_handler" << "\n";

}

void UartConnect::resetBoard_handler() {
    std::cout << "resetBoard_handler" << "\n";

}

ScorInterface *UartConnect::getScorInterface() {
    if (!scorInterface)
        throw new UartConnectExeption("scorInterface = null\nPlease connect the Scorbot\n");
    return scorInterface;
}
