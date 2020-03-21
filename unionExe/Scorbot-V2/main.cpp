//
// Created by alfyhack on 29/11/19.
//


#include <ScorbotMainWindows.h>
#include <QApplication>
#include <DataTransfert_AllInclude.h>

using namespace DataPrimitive;
using namespace DataManipolation;
/// Function to support Ui
ScorbotMainWindows *w;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    w = new ScorbotMainWindows(nullptr);
    w->show();   //visualizza gli estremi della finestra, ma non carica nulla.

    return a.exec(); //Avvia l'applicazione e il programma
}