//
// Created by alfyhack on 29/11/19.
//


#include <QtScorbotUi.h>
#include <QApplication>
#include <dataTransfert_AllInclude.h>

using namespace DataPrimitive;
using namespace DataManipolation;
/// Function to support Ui
QtScorbotUi *w;

int main (int argc, char *argv[]){

    // se si vogliono prendere dei parametri da linea di comando, devono essere catturati qui
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");

    w = new QtScorbotUi(nullptr);
    w->show();   //visualizza gli estremi della finestra, ma non carica nulla.
    return a.exec(); //Avvia l'applicazione e il programma
}