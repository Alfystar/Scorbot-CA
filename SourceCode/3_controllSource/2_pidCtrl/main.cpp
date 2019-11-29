#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <PIDScorbot.h>
#include <DataTransfert_AllInclude.h>
#include <UartSubSystem.h>
#include <unistd.h>

PIDScorbot *pidM[nMot];
using namespace DataPrimitive;
using namespace DataManipolation;
ScorInterface *scorbot;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("inserire +/- per indicare obiettivo\n");
        exit(0);
    }

    /// Initialize board Comunication
    try {
        scorbot = &AdapterFactory::makeUart("/dev/ttyACM0", B921600);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }

    /// Creo i finiti riferimenti
//    int r[nMot];    //reference
    EncoderMot *ref = new EncoderMot();
    if (strcmp(argv[1], "+") == 0) {
        ref->enSet(Mot1, -5490);
        ref->enSet(Mot2, 2000);
        ref->enSet(Mot3, 4195);
        ref->enSet(Mot4, 2500);
        ref->enSet(Mot5, 2500);
        ref->enSet(Mot6, 1000);
//        r[Mot1] = -5490;
//        r[Mot2] = 2000;
//        r[Mot3] = 4195;
//        r[Mot4] = 2500;
//        r[Mot5] = 2500;
//        r[Mot6] = 1000;
    } else {
        ref->enSet(Mot1, 1666);
        ref->enSet(Mot2, 4000);
        ref->enSet(Mot3, -542);
        ref->enSet(Mot4, -240);
        ref->enSet(Mot5, -3533);
        ref->enSet(Mot6, 2500);
//        r[Mot1] = 1666;
//        r[Mot2] = 4000;
//        r[Mot3] = -542;
//        r[Mot4] = -240;
//        r[Mot5] = -3533;
//        r[Mot6] = 2500;
    }
    printf("Encoder Reference:\n");
    ref->printEncoder();
    pidM[Mot1] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, .8, 0.02);
    pidM[Mot2] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, 1.0, 0.02);
    pidM[Mot3] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, true, .8, 0.02);
    pidM[Mot4] = new PIDScorbot(0.00055, 0.0000000015, 10, 110, true, .8, 0.02);
    pidM[Mot5] = new PIDScorbot(0.00055, 0.0000000015, 10, 133, false, .8, 0.02);
    pidM[Mot6] = new PIDScorbot(0.00055, 0.0000000015, 10, 85, false, .8, 0.02);
    EncoderMot *enFeed; //Puntatore per i dati letti
    EncoderMot *refPid = new EncoderMot();

    SpeedMot *pwm = new SpeedMot();
    sleep(1);
    struct timespec startCalc, endCalc, ts, delay, sleepTime;   // avevano più senso con la SPI
    timeWriteSpec(&ts, 0, 10 * 1000000UL);    //10ms per il tempo di campionamento

    scorbot->setSampleTimeEn(ts.tv_nsec / 1000UL + ts.tv_sec * 1000000UL);

    /// Prendo la prima misura
    enFeed = scorbot->getEncoder();
    refPid->copyEn(*ref);
    while (true) {
        /// Passaggio dei parametri al pid e calcolo del corrispettivo pwm
//        clock_gettime(CLOCK_MONOTONIC_RAW,&startCalc);
        for (int i = Mot1; i < Mot4; i++) {
//            pwm->pwmSet((motCode)i, pidM[i]->motVal(r[i], enFeed->getEn((motCode)i)));
//            pwm->pwmSet((motCode) i, pidM[i]->pid(r[i], enFeed->getEn((motCode) i), &ts));
            pwm->pwmSet((motCode) i, pidM[i]->pid(refPid->getEn((motCode) i), enFeed->getEn((motCode) i), &ts));
            printf("mot[Mot%d]=%d\n\n", i + 1, pwm->getPwm((motCode) i));
        }
//        clock_gettime(CLOCK_MONOTONIC_RAW,&endCalc);

        /// Vado a dormire fino al successivo tempo di campionamento
//        timeraddSpec(&startCalc, &ts,&delay);       // momento della ninna
//        timersubSpec(&endCalc,&delay,&sleepTime);   // levo il tempo di calcolo
//        nanosleep(&sleepTime,&delay);   //se arrivasse un segnale in delay c'è il tempo mancante

        /// Invia il pacchetto il prima possibile
        scorbot->sendVel(*pwm);
        /// Pulisco la memoria e aspetto un nuovo pacchetto
        delete enFeed;
        enFeed = scorbot->getValidEncoderWait();
        printf("\n\n\n\n\n");
    }
    return 0;
}
