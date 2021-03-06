/*
 * adcReader.cpp
 *				 Formule di Conversione:
 *
 * Sensitività in uscita: 0.140 V/A, dichiarata dall'VNH5019
 * Vref scelto tra Aref/1.1V/2.56V
 * ______________________________________________________________________
 * |			 Vref * ADC	 	|  |			Iread * 1024 * Vcs		|
 * |	Iread = --------------	|&&|	ADC = -----------------------	|
 * |			1024 * Vcs   	|  |				Vref				|
 * |____________________________|__|____________________________________|
 *  Created on: 22 mar 2019
 *      Author: alfy
 */

#include "adcReader.h"
// Essendo linkata nel ".project" di sloeber, gcc la vede nella sua vera posizione
#include "../../../Common-src/dataTransfertPrimitive/dataTransfert_AllInclude.h"

namespace InternalDevice {
    AdcDevice::AdcDevice (){
        AdcDevice(false, in1V1);
    }

    AdcDevice::AdcDevice (adcRef vRef){
        AdcDevice(false, vRef);
    }

    AdcDevice::AdcDevice (bool diff){
        AdcDevice(diff, in1V1);
    }

    AdcDevice::AdcDevice (bool diff, adcRef vRef){
        this->setDiffRead(diff);
        this->setVRefSource(vRef);
        this->historyClear();
        this->setUpADC();
    }

    void AdcDevice::setUpADC (){
        DIDR0 = 0x7F; //imposto tutti i pin da A0:A6 come pin di input analiogico

        // ADCSRB – ADC Control and Status Register B //
        ADCSRB &= 0xF8;    // Imposto la modalità di free running, e lascio inalterato il resto

        // ADCSRA – ADC Control and Status Register A //
        //A queste condizioni ho 125Khz di clock all'adc e una conversione ogni:
        //14*1/125KHz= 112us ~ 8,9Khz  (14 se letto in differential mode)
        //13*1/125KHz= 104us ~ 9,6Khz  (13 se letto in normal mode)
        ADCSRA = 0;
        ADCSRA |= (1 << ADEN) | (1 << ADATE); //Attiva ADC, Seleziona l'autoTrigger scelto in ADCSRB
        ADCSRA |= 0x7; //prescaler a 1/128 Clock

        this->pinSelect(Mot1); //imposto il primo pin da leggere per la lettura sporca
        ADCSRA |= (1 << ADSC);    //avvia 1° conversione
        // Prima lettura è sporca //
        while (ADCSRA & (1 << ADIF)); //wait first reading
        ADCSRA |= (1 << ADIE); //attiva l'interrupt
    }

    void AdcDevice::historyClear (){
        memset((void *) ampMot, 0, sizeof(mCurrent) * history); //pulisco la memoria
    }

    void AdcDevice::setVRefSource (adcRef vRef){
        this->vRef = vRef;
        //ADMUX – ADC Multiplexer Selection Register
        cbi(ADMUX, REFS1);
        cbi(ADMUX, REFS0);
        switch (this->vRef){
            case in1V1:
                ADMUX |= (0 << REFS0) | (1 << REFS1); // 1.1V Internal Arduino
                break;
            case in2V56:
                ADMUX |= (1 << REFS0) | (1 << REFS1); // 2.56V Internal Arduino
                break;
            case ext:
                ADMUX |= (0 << REFS0) | (0 << REFS1); // Ext Vref
                break;
            default:
                ADMUX |= (0 << REFS0) | (1 << REFS1); // 1.1V Internal Arduino
                break;
        }
    }

    adcRef AdcDevice::getVRefSource (){
        return this->vRef;
    }

    void AdcDevice::setDiffRead (bool active){
        this->diffRead = (!!active); //to be sure value is 0 or 1
    }

    bool AdcDevice::getDiffRead (){
        return this->diffRead;
    }

    int g;

    void AdcDevice::isrFunxAdc (){
        g = (int) ADCL;
        g |= (int) ADCH << 8;
        this->ampMot[indexADC][oldReadId] = g; //((int) ADCL | ((int) ADCH << 8));
        oldReadId = newReadId;    //la lettura che è già partita in automatico
        if (oldReadId == 0){        //finito un ciclo di lettura avanza con i buffer della storia
            /*
            Db.flush();
            mCurrent &c = this->ampMot[indexADC];
            Db.println("Sended Current Value:");
            for (byte i = Mot1; i < nMot; i++) {
                Db.print("\tcur[Mot");
                Db.print(i+1);
                Db.print("]:");
                Db.println(c[i]);
            }
            */
            indexADC = (indexADC + 1) % history;
        }
        newReadId = (motCode) ((newReadId + 1) % nMot);    //il prossimo pin da impostare nei registri
        this->pinSelect(
                newReadId);    //imposto i registri, verranno usati al successivo interrupt per il Free-running dell'ADC
    }

    /* Tabella Codice/significato dei mux
     MUX5:0  +    -   G
     000000 ADC0 ADC1 1×   Corrente mot 1
     000001 ADC1 ADC1 1×   XXXXXX----NON IN USO
     000010 ADC2 ADC1 1×   Corrente mot 2
     000011 ADC3 ADC1 1×   Corrente mot 3
     000100 ADC4 ADC1 1×   Corrente mot 4
     000101 ADC5 ADC1 1×   Corrente mot 5
     000110 ADC6 ADC1 1×   Corrente mot 6
     000111 ADC7 ADC1 1×
     //###### 4° bit ON ######//
     010000 ADC0 ADC1 1×   Corrente mot 1 - Offset
     010001 ADC1 ADC1 1×   XXXXXX----NON IN USO
     010010 ADC2 ADC1 1×   Corrente mot 2 - Offset
     010011 ADC3 ADC1 1×   Corrente mot 3 - Offset
     010100 ADC4 ADC1 1×   Corrente mot 4 - Offset
     010101 ADC5 ADC1 1×   Corrente mot 5 - Offset
     010110 ADC6 ADC1 1×   Corrente mot 6 - Offset
     010111 ADC7 ADC1 1×
     */
    byte AdcDevice::pinSelect (motCode mot){
        byte val = ADMUX & 0xE0; //mantenengo le impostazioni
        switch (mot){
            case Mot1:
                val |= 0x0;
                break;
            case Mot2:
                val |= 0x2;
                break;
            case Mot3:
                val |= 0x3;
                break;
            case Mot4:
                val |= 0x4;
                break;
            case Mot5:
                val |= 0x5;
                break;
            case Mot6:
                val |= 0x6;
                break;
            default:
                return -1;
                break;
        }
        //Il 4°bit attiva la lettura Diffenrenziale
        val |= (this->diffRead) << 4;
        ADMUX = val;
        return 0;
    }

    //puntatore di ritorno FERMO per ~1ms (
    mCurrent &AdcDevice::getLastCycle (){
        return this->ampMot[((indexADC - 1) + history) % history];
    }

    short AdcDevice::getCurrentSum (motCode mot){
        this->sumCur = 0;
        for (byte j = 0; j < history; j++)
            this->sumCur += this->ampMot[j][mot];
        return this->sumCur;
    }

    #ifdef ADC_DB
    mCurrent *m;
    void AdcDevice::debugPrintAdc (){
        m = &this->getLastCycle();
        Db.flush();
        Db.println("Last cycle:");
        for (byte i = 0; i < nMot; i++){
            Db.print("Cur[");
            Db.print(i + 1);
            Db.print("] = ");
            Db.println(*m[Mot1]);
            delay(1);
        }
        if (this->diffRead)
            Db.println("Lettura differenziale ON");
        else
            Db.println("Lettura differenziale OFF");
    }
    #endif
} //END namespace InternalDevice

