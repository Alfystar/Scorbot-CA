#include "Project-lib/globalDef.h"
#include "Project-lib/Motor/DCdriver.h"

#define timeOut 2000

extern Motor::DCdriverLimit *mot[nMot];
//<== Scadenze dinamiche dei pacchetti ==>
unsigned long time;
unsigned long nextEnSend = 0, nextCurSend = 0;    //time in microSecond (10^-6)
uint32_t enP = 10 * 1000UL; //default 100Hz
uint32_t curP = 20 * 1000UL; //default 50hz

mAll mAllTmp;
AllSensor *sAllSend;

void excutePack (uart2Ard &p){
    switch (p.type){
        case mSpeedData:{
            mSpeed &vel = p.pack.up.speed;
            for (byte i = 0; i < nMot; i++){
                switch (vel[Mot1 + i]){
                    case freeRun:
                        mot[Mot1 + i]->freeRun();
                        break;
                    case hardStop:
                        mot[Mot1 + i]->hard_stop(timeOut);
                        break;
                    case softStop:
                        mot[Mot1 + i]->soft_stop(timeOut);
                        break;
                    case ignore:
                        break;
                    default:
                        mot[Mot1 + i]->drive_motor(vel[Mot1 + i], timeOut);
                        break;
                }
            }
        }
            break;
        case settingBoardData:{
            settingsBoard &s = p.pack.up.prop;
            memorySave(s);
            Motor::setMotFreq(s.freq);
            adc->setDiffRead(s.diff);
            adc->setVRefSource(s.adcVref);
            break;
        }
        case sampleTimeEn:
            enP = p.pack.up.sampleEn;
            break;
        case sampleTimeCur:
            curP = p.pack.up.sampleCur;
            break;
        case goHomeUart:
            home();
            break;
        case settingAsk:
            uart->packSend(settingBoardData, (data2Linux *) &globSets);
            break;
        case RESEND:
            //todo inviare lastPack
            break;
        default:
            break;
    }
}

void initDataSend (){
    sAllSend = new AllSensor(mAllTmp);
    nextEnSend = micros();    //dall'accenzione almeno 5 secondi di pausa
    nextCurSend = nextEnSend;

    //Uso il Timer/Counter5 e il suo Overflow Flag (TOV5) per generare l'interrupt ogni ~4Kh
    //La modalità di default del timer 5 è in 8-bit phase correct pwm mode e prescaler a 64 bit
    //Mantengo utilizzabili i pin D44, D45 & D46 come normali PWM a 490.20 Hz)
    //TCCR5B = (TCCR5B & B11111000) | B00000010; // set timer 5 divisor to 64 for PWM frequency of 3921.16 Hz
    //TCCR5B = (TCCR5B & B11111000) | B00000001; // set timer  divisor to     1 for PWM frequency of 31372.55 Hz
    TCNT5 = 0;    //Resetto il timer
    TIMSK5 |= (1 << TOIE5);   // enable timer overflow interrupt

}

// Update che elimina il problema dell'overFlow (e normalmente 1 max 2 cicli)
#define whileUpdate(deadTime, time, step)    \
        while (deadTime < time)            \
            deadTime += step

void dataSend (){
    //todo: Rubare un timer e far chiamare ogni millisecondo la funzione
    time = micros();
    #ifdef DATA_SEND_DB
    //Db.println("[dataSend] Inside");
    #endif
    //To avow the overflow problem this is simple solution
    //https://www.norwegiancreations.com/2018/10/arduino-tutorial-avoiding-the-overflow-issue-when-using-millis-and-micros/
    // Si gioca sul fatto che una variabile UNSIGNED, ES a 4bit:
    // a = 0(16) e b = 14
    // a-b = -14 che letto come UNSIGNED è uguale a 2 !!!
    // (Algebra modulare di base 2^bit)
    // Nel nostro caso, l'eq di base è
    // nextRelase < time then ... end set new Release
    if (((long) (time - nextEnSend) > 0) && ((long) (time - nextCurSend) > 0)){
        sAllSend->copyEn(sFeed->captureEn());
        sAllSend->copyCur(adc->getLastCycle());
        uart->packSend(mAllData, (data2Linux *) &sAllSend->getSens());
        //nextEnSend += ((time-nextEnSend)/enP + 1) * enP;		// In case miss 1 or more deadline
        //nextCurSend += ((time-nextCurSend)/curP + 1) * curP;	// In case miss 1 or more deadline
        whileUpdate(nextEnSend, time, enP);
        whileUpdate(nextCurSend, time, curP);
        //nextEnSend += enP;
        //nextCurSend += curP;
        #ifdef DATA_SEND_DB
        Db.println("[dataSend] Serial send all");
        Db.print("[dataSend] Time = ");
        Db.println(time);
        Db.print("[dataSend] nextEnSend = ");
        Db.println(nextEnSend);
        Db.print("[dataSend] nextCurSend = ");
        Db.println(nextCurSend);
        #endif
        return;
    }
    if ((long) (time - nextEnSend) > 0){
        sAllSend->copyEn(sFeed->captureEn());
        uart->packSend(mEncoderData, (data2Linux *) &sAllSend->getEn());

        //nextEnSend += ((time-nextEnSend)/enP + 1) * enP;		// In case miss 1 or more deadline
        whileUpdate(nextEnSend, time, enP);
        //nextEnSend += enP;
        #ifdef DATA_SEND_DB
        Db.println("[dataSend] Serial send encoder");
        Db.print("[dataSend] Time = ");
        Db.println(time);
        Db.print("[dataSend] nextEnSend = ");
        Db.println(nextEnSend);
        #endif
        return;
    }
    if ((long) (time - nextCurSend) > 0){
        sAllSend->copyCur(adc->getLastCycle());
        uart->packSend(mCurrentData, (data2Linux *) &sAllSend->getCurrent());
        //nextCurSend += ((time-nextCurSend)/curP + 1) * curP;	// In case miss 1 or more deadline
        whileUpdate(nextCurSend, time, curP);
        //nextCurSend += curP;
        #ifdef DATA_SEND_DB
        Db.println("[dataSend] Serial send motor");
        Db.print("[dataSend] Time = ");
        Db.println(time);
        Db.print("[dataSend] nextCurSend = ");
        Db.println(nextCurSend);
        #endif
        return;
    }
}
