#include "Arduino.h"
#include "Project-lib/globalDef.h"

// <== Global Pointer of OBJ ==>
settingsBoard globSets;            // Current settings of the board
UartDriver *uart;                // Uart pack MGT obj
uart2Ard *r;                    // Last Command reciver
AdcDevice *adc;                    // ADC MGT obj
MotFeed *sFeed;                    // Endoder & Switch MGT obj
Motor::DCdriverLimit *mot[nMot];// Motor Class objs

// <== DB_PRINT_SENSOR Define/Variable ==>
#ifdef DB_PRINT_SENSOR
#define newPrintDelay 1000    //delay tra un debug print e l'altro
unsigned long timePrint;	//time to next debug print
#endif

// <== Sanity check Define/Variable ==>
#define sanityDelay 1000        //tempo ms di attesa prima di ri-scansionare se il robot è ok

void setup (){
    #ifdef DB_TERMINAL
    Db.begin(DbVel);
    Db.println("\n##### Start Db #####");
    Db.println("\n##### Start Setup #####");
    delay(250);
    #endif
    cli();

    //==========================================
    #ifdef DB_TERMINAL
    Db.println("\tLoad Settings from Memory");
    #endif
    memoryLoad();
    //==========================================
    #ifdef DB_TERMINAL
    Db.println("\tMotor Setup");
    #endif
    motSetup();
    //==========================================
    #ifdef DB_TERMINAL
    Db.flush();
    Db.println("\tSetUp Scorbot Sensors");
    #endif
    sFeed = new MotFeed();
    //==========================================
    #ifdef DB_TERMINAL
    Db.flush();
    Db.println("\tSetUp ADC");
    #endif
    adc = new AdcDevice(globSets.diff, globSets.adcVref);
    //==========================================
    #ifdef DB_TERMINAL
    Db.flush();
    Db.println("\tSetUp CMD Serial");
    #endif
    uart = new UartDriver(&Cmd, CmdVel);

    //Cmd.println("Programma sviluppato da:\n\t\tEmanuele Alfano\n\t\talfystar1701@gmail.com");
    //Cmd.println("Project repository:\n\thttps://github.com/Alfystar/Scorbot-CA");
    //Cmd.println("Firmware version scorBoard:\n\t\t\tV1.0");
    //Cmd.println("Protocollo di Comunicazione:\n\t\t\tV1.0");
    initDataSend();

    //==========================================

    sei();
    #ifdef DB_TERMINAL
    Db.println("\tGlobal Interrupt Enable");
    Db.println("End Setup");
    #endif

    //==========================================
    #ifdef MOVE_CHECK
    #ifdef DB_TERMINAL
    Db.println("MOVE_CHECK Enable, test motors:");
    #endif
    for (byte i = Mot1; i < nMot; i++){
        #ifdef DB_TERMINAL
        Db.print("\nCheck mot[");
        Db.print(i);
        Db.println("]");
        #endif
        mot[i]->drive_motor(150);
        delay(1500);
        mot[i]->drive_motor(-150);
        delay(1500);
        mot[i]->freeRun();
        delay(1500);
    }
    #ifdef DB_TERMINAL
    Db.println("End MOVE_CHECK");
    #endif
    #endif
}//Setup end

void loop (){
    //Sensor update
    sFeed->updateStepEn();
    if (Cmd.available()){
        uart->serialIsr();
    }
    //==========================================

    //Serial command read
    if (uart->Available()){
        r = uart->getData();
        excutePack(*r);
    }


    //Internal state update
    motorStateMachine();
    #ifdef MOTOR_LIMIT_ENABLE
    sanityChek(sanityDelay);
    #endif
    //==========================================

    #ifdef DB_PRINT_SENSOR
    //Debug Serial zone
    if (millis() > timePrint + newPrintDelay) {
        adc->debugPrintAdc();
        sFeed->dSubDebug();
        sFeed->printSteps();
        Pack::printSetting(globSets);
        Db.println();
        timePrint = millis();
    }
    #endif
}//Loop end


// <====== ADC INTERRUPT SERVICE ======>
// Si attiva ad ogni fine conversione, e immediatamente si avvia la successiva
// (con i valori presenti nel registro alla ricezione dell'interrupt)
// la routine salva il valore convertito e imposta i registri per la lettura successiva
ISR(ADC_vect) {
        adc->isrFunxAdc();
}
// <====== Timer/Counter5 Overflow Flag (TOV5) ======>
// Ogni ~490.5hz Verifico se campionare
ISR(TIMER5_OVF_vect) {
        //Db.println("Timer5 overflow");
        dataSend();
        uart->serialTrySend();
        //==========================================
}

// <====== PCINT INTERRUPT SERVICE ======>
// Al Cambio di uno dei pin degli Encoder, li salva tutti in memoria su un buffer circolare
// per elaborare lo stato in un momento successivo durante il programma

ISR(PCINT0_vect) {
        sFeed->isrFunxEN();
}
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect)
); // @suppress("Unused function declaration")

