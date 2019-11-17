#include "Arduino.h"
#include "Project-lib/globalDef.h"

//#define DB_PRINT 1    //attiva/disattiva compilazione del codice per printare in Dbe informazioni aggiungtive
//#define DB_PRINT_SENSOR 1 //attiva/disattiva compilazione del codice per printare i sensori ogni "newPrintDelay"
#define CMD_PRINT 1            //attiva/disattiva compilazione del print del pacchetto spi

//#define MOVE_CHECK 1 		//attiva/disattiva compilazione del codice che muove tutti i motori per test
#define MOTOR_LIMIT_ENABLE 1    //attiva/disattiva compilazione del codice che sceglie la classe da istaziare per i motori
settingsBoard globSets;
SpiDevice *spi;
UartDriver *uart;
AdcDevice *adc;
ScorFeed *sFeed;
using namespace Motor;
DCdriverLimit *mot[nMot];
#ifdef DB_PRINT_SENSOR
unsigned long timePrint;	//time to next debug print
#endif
#define sanityDelay 1000        //tempo ms di attesa prima di ri-scansionare se il robot è ok
#define newPrintDelay 1000    //delay tra un debug print e l'altro
unsigned long sanityTime = 0;

//The setup function is called once at startup of the sketch
void setup() {
    Db.begin(DbVel);
    Db.println("\n##### Start Db #####");
    cli();
    Db.println("\n##### Start Setup #####");
    delay(250);
    memoryLoad();
    Db.flush();
    Db.println("\tLoad Settings from Memory");
    motSetup();
    Db.flush();
    Db.println("\tMotor Setup");
    sFeed = new ScorFeed();
    Db.flush();
    Db.println("\tSetUp Scorbot Sensors");
    adc = new AdcDevice(globSets.diff, globSets.adcVref);
    Db.flush();
    Db.println("\tSetUp ADC");

    //spi = new SpiDevice();
    uart = new UartDriver(&Cmd, CmdVel);
    initDataSend();
    Db.flush();
    Db.println("\tSetUp CMD Serial");
    sei();
    Db.println("\tGlobal Interrupt Enable");
    Db.println("End Setup");
#ifdef MOVE_CHECK
    for (byte i=Mot1;i<nMot;i++)
    {
        delay(3000);
        mot[i]->drive_motor(150);
        delay(3000);
        mot[i]->drive_motor(-150);
        delay(3000);
        mot[i]->freeRun();
    }
#endif

}

uart2Ard *r;

//tempi in micro secondi, dopo ~ 70 min in overflow, gestito
unsigned long nextEnSend = 0, nextCurSend = 0;
//unsigned short enP = 1000, curP = 2000;	//di default 1Kh e 0.5Khz
uint32_t enP = 10 * 1000UL, curP = 20 * 1000UL;    //di default 100Hz e 50hz
//500000
unsigned long timeOverflow[200];
int timeOverflowId = 0;

void loop() {
    //Sensor update
    sFeed->updateStepEn();
    if (Cmd.available())
        uart->serialIsr();
    //Serial command read
    if (uart->Available()) {
        r = uart->getData();
        excutePack(*r);
#ifdef CMD_PRINT
        Cmd.println("Printo pacchetto ricevuto:");
        UartDriver::serialPackDb(*r);
#endif
    }
    dataSend();
    uart->serialTrySend();

    //Internal state update
    motorStateMachine();
    sanityChek(sanityDelay);


    //Debug Serial zone
#ifdef DB_PRINT_SENSOR
    if (millis() > timePrint + newPrintDelay) {
        adc->debugPrintAdc();
        //sFeed->dSubDebug();
        sFeed->printSteps();
        //Pack::printSetting(globSets);
        Db.println();
        timePrint = millis();
    }
#endif
}

void sanityChek(int wait) {
    if (millis() > sanityTime + wait) {
        sanityTime = millis();
        for (byte i = 0; i < nMot; i++) {
            if (globSets.maxCurrMed[i] < 0)
                continue;
            if (globSets.maxCurrMed[i] < adc->getCurrentSum((motCode) i)) {
                mot[i]->freeRun();
#ifdef DB_PRINT
                Db.print("nMot[");
                Db.print(i + 1);
                Db.print("] overcurrent: ");
                Db.print(globSets.maxCurrMed[i]);
                Db.print(" > ");
                Db.println(adc->getCurrentSum((motCode) i));
#endif
            }
            if (((globSets.maxCurrMed[i] * 3) / 2)
                < adc->getCurrentSum((motCode) i)) {    // WARNING
                digitalWrite(MotEn, 0);
#ifdef DB_PRINT
                Db.print("nMot[");
                Db.print(i + 1);
                Db.print("] High-overcurrent: ");
                Db.print(globSets.maxCurrMed[i]);
                Db.print(" > ");
                Db.println(adc->getCurrentSum((motCode) i));
#endif
            }
            if ((globSets.maxCurrMed[i] / 4)
                < adc->getCurrentSum((motCode) i)) { // Current problem came back
                digitalWrite(MotEn, 1);
            }

        }
    }
}

//## SPI INTERRUPT SERVICE ##//
//Si attiva alla ricezione di ogni byte (8 bit)
//(e si ha tempo per eseguire la funzione solo fino al successivo!!)
/*
 ISR(SPI_STC_vect) {
 cli(); //disable global interrupt
 spi->isrFunxISP();
 sei(); //enable global interrupt
 //Db.print("spi");
 }
 */



//## ADC INTERRUPT SERVICE ##//
//Si attiva ad ogni fine conversione, e immediatamente si avvia la successiva
//(con i valori presenti nel registro alla ricezione dell'interrupt)
//la routine salva il valore convertito e imposta i registri per la lettura successiva
ISR(ADC_vect) {
        //Db.print("adc");
        adc->isrFunxAdc();
}

//## Timer/Counter5 Overflow Flag (TOV5)
//Ogni ~4Khz aggiorno la lettura degli encoder così da non
//perdermi mai un passo (freq massima misurata 2khz)

ISR(TIMER5_OVF_vect) {
        sFeed->isrFunxEN();
        //sFeed->dSubDebug();

}

//## PCINT INTERRUPT SERVICE ##//
//Al Cambio di uno dei pin degli Encoder, li salva tutti in memoria su un buffer circolare
//per elaborare lo stato in un momento successivo durante il programma

ISR(PCINT0_vect) {
        sFeed->isrFunxEN();
        //sFeed->dSubDebug();
}
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect)
); // @suppress("Unused function declaration")

