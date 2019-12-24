#include <QApplication>
#include "src/scorbotUi/mainwindow.h"
#include <iostream>
#include <unistd.h>
#include <DataTransfert_AllInclude.h>

//void controllRefInMoc(EncoderMot &en) {
//    en.printEncoder();
//}
//
//void settingSendMoc(SettingBoard_C &set) {
//    set.printSetting();
//}
//
//SettingBoard_C *p;
//
//SettingBoard_C &settingGetMoc() {
//    if (p)
//        p = new SettingBoard_C();
//
//    //Setting per ora di default
//    //curr neg => no limit
//    p->setMotorLimit(Mot1, 2160, 24300, -19450);
//    p->setMotorLimit(Mot2, 2960, 16200, -1000);
//    p->setMotorLimit(Mot3, 2960, 21900, -7300);
//    p->setMotorLimit(Mot4, 2160, 10000, -10000);
//    p->setMotorLimit(Mot5, 2400, 10000, -10000);
//    p->setMotorLimit(Mot6, 2160, 5770, -10);
//    p->setAdcDiff(false);
//    p->setAdcRef(in1V1);
//    p->setPWMfreq(hz4k);
//    return *p;
//}


int main(int argc, char *argv[]) {
    // Ne può esistere una per applicazione, le finestre si collegano a lei automaticamente
    QApplication a(argc, argv);

    // Compilo il "modulo" contenente le funzioni che verranno chiamate per interfacciarsi all'esterno
//    struct extFooCall extF;
//    extF.ctrlFunx = controllRefInMoc;
//    extF.setSendFunx = settingSendMoc;
//    extF.setGetFunx = settingGetMoc;
    // Genero la finestra principale "Main dell'interfaccia grafica"
    MainWindow &w = *new MainWindow(nullptr);
    w.show();   //visualizza gli estremi della finestra, ma non carica nulla.
    return a.exec(); //Avvia l'applicazione e il programma
}
