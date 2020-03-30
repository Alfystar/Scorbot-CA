#include <QApplication>
#include "src/scorbotUi/mainwindow.h"
#include "src/scorbotUi/uartChoise.h"
#include <iostream>
#include <unistd.h>
#include <DataTransfert_AllInclude.h>

int main(int argc, char *argv[]) {
    // Ne può esistere una per applicazione, le finestre si collegano a lei automaticamente
    QApplication a(argc, argv);
    // Genero la finestra principale "Main dell'interfaccia grafica"
    MainWindow &w = *new MainWindow(nullptr);
    w.show();   //visualizza gli estremi della finestra, ma non carica nulla.
    return a.exec(); //Avvia l'applicazione e il programma
}
