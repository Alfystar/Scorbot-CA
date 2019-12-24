//
// Created by alfyhack on 29/11/19.
//


#include <ScorbotMainWindows.h>
#include <QApplication>
#include <DataTransfert_AllInclude.h>

using namespace DataPrimitive;
using namespace DataManipolation;

//ScorInterface *scorbot;
//
///// Function to support Controll
//
//PIDScorbot *pidM[nMot];
//EncoderMot *enFeed; //Puntatore per i dati letti
//EncoderMot *refPid;
//std::mutex refMutex;    //Per evitare cambio di riferimenti incontrollato
//SpeedMot *pwm;

//void updateRef(EncoderMot &m){
//    refMutex.lock();
//    refPid->copyEn(m);
//    refMutex.unlock();
//
//}
//
//void ctrlTh(){
//    refPid = new EncoderMot();
//    pwm = new SpeedMot();
//    refMutex.unlock();
//
//
//    pidM[Mot1] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, .8, 0.02);
//    pidM[Mot2] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, 1.0, 0.02);
//    pidM[Mot3] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, true, .8, 0.02);
//    pidM[Mot4] = new PIDScorbot(0.00055, 0.0000000015, 10, 110, true, .8, 0.02);
//    pidM[Mot5] = new PIDScorbot(0.00055, 0.0000000015, 10, 133, false, .8, 0.02);
//    pidM[Mot6] = new PIDScorbot(0.00055, 0.0000000015, 10, 85, false, .8, 0.02);
//
//    sleep(1);
//    struct timespec  tsEn, tsCur;   // Tempo di campionamento Encoder e Corrente
//    timeWriteSpec(&tsEn, 0, 10 * 1000000UL);    //10ms per il tempo di campionamento
//    scorbot->setSampleTimeEn(tsEn.tv_nsec / 1000UL + tsEn.tv_sec * 1000000UL);
//
//    timeWriteSpec(&tsCur, 0, 10 * 1000000UL);    //10ms per il tempo di campionamento
//    scorbot->setSampleTimeCur(tsCur.tv_nsec / 1000UL + tsCur.tv_sec * 1000000UL);
//
//    /// Prendo la prima misura
//    enFeed = scorbot->getEncoder();
//    while (true) {
//        refMutex.lock();
//        /// Passaggio dei parametri al pid e calcolo del corrispettivo pwm
//        for (int i = Mot1; i < Mot4; i++) {
//            pwm->pwmSet((motCode) i, pidM[i]->pid(refPid->getEn((motCode) i), enFeed->getEn((motCode) i), &tsEn));
//            printf("mot[Mot%d]=%d\n\n", i + 1, pwm->getPwm((motCode) i));
//        }
//        refMutex.unlock();
//
//        /// Invia il pacchetto il prima possibile
//        scorbot->sendVel(*pwm);
//        /// Pulisco la memoria e aspetto un nuovo pacchetto
//        delete enFeed;
//        enFeed = scorbot->getValidEncoderWait();
//        printf("\n\n\n\n\n");
//    }
//}
//
//
///// Function to support Ui
//ScorbotMainWindows *w;
////wrap to avoi function pointer problem
//void settingSend_ui(SettingBoard_C &set){
//    scorbot->setSetting(set);
//}
//////wrap to avoi function pointer problem
//SettingBoard_C &settingGet_ui(){
//    return *scorbot->getSetting_local();
//}
//
//void enUpdateTh(){
//    while (true){
//        //todo Ogni volta che arriva un nuovo dato lo invia all'interfaccia grafica
//        sleep(1);
//    }
//}
//
//void curUpdateTh(){
//    while (true){
//    //todo Ogni volta che arriva un nuovo dato lo invia all'interfaccia grafica
//        sleep(1);
//    }
//}

/// Function to support Ui
ScorbotMainWindows *w;

int main(int argc, char *argv[]) {

//    /// Comunicazione avvio
//    try {
//        scorbot = &AdapterFactory::makeUart("/dev/ttyACM0", B921600);
//    } catch (const std::exception &e) {
//        std::cerr << e.what() << std::endl;
//        exit(-1);
//    }
//
//    /// Controllo avvio
//    std::thread *ctrl = new std::thread(ctrlTh);
//


    /// Interfaccia grafica Avvio
    // Ne può esistere una per applicazione, le finestre si collegano a lei automaticamente
    QApplication a(argc, argv);

    // Compilo il "modulo" contenente le funzioni che verranno chiamate per interfacciarsi all'esterno
//    struct extFooCall extF;
//    extF.ctrlFunx = updateRef;
//    extF.setSendFunx = settingSend_ui;
//    extF.setGetFunx = settingGet_ui;
    // Genero la finestra principale "Main dell'interfaccia grafica"
    w = new ScorbotMainWindows(nullptr);
    w->show();   //visualizza gli estremi della finestra, ma non carica nulla.

//    std::thread *enUpdate = new std::thread(enUpdateTh);
//    std::thread *curUpdate = new std::thread(curUpdateTh);

    return a.exec(); //Avvia l'applicazione e il programma
}