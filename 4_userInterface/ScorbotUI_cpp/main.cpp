#include <QApplication>
#include "scorbotUi/mainwindow.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Ne può esistere una per applicazione, le finestre si collegano a lei automaticamente
    QApplication a(argc, argv);
    MainWindow w;
    w.show();   //visualizza gli estremi della finestra, ma non carica nulla.
    return a.exec(); //Avvia l'applicazione e il programma
}
