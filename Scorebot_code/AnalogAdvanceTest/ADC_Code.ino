//NEED TO BE in the HEAD of Code
//enum currentPin {cMot1=0, cMot2, cMot3, cMot4, cMot5, cMot6};

/*
 * Questo script permette di avviare la lettura dei sensori di corrente dei motori.
 * La lettura prosegue in interrupt, e aggiorna in automatico l'array.
 * Sul pin A1 si immette la tensione da sottrarre, e leggendo i valori nell'array
 * si ottiene il risultato del comparatore con tutti i bit di precisioni scelti.
 * E necessario quindi tarare il voltaggio in ingresso sul pin A1, affinchè renda il
 * più vicini possibili tutti i sensori a 0 senza diventare negativi però, in tal caso
 * la sottrazione fa si che il risultato riparta da 1023 rendendo vana la lettura. 
 */

volatile int ampMot[6];
volatile byte cicleEnd=0; //todo, variabile che viene messa a 1 quando si termina un ciclo di scansione 
void setUpADC()
{
  memset(ampMot, 0, sizeof(int) * 6); //pulisco la memoria

  //ADMUX – ADC Multiplexer Selection Register
  //Vref=5V of board, Lettura in uscita standard
  ADMUX = (1 << REFS0);
  DIDR0 = 0x7F; //imposto tutti i pin da A0:A6 come pin di input analiogico

  /* ADCSRB – ADC Control and Status Register B
    Imposto la modalità di free running, e lascio inalterato il resto
  */
  ADCSRB &= 0xF8;

  difPinSelect(cMot1);  //imposto il primo pin da leggere per la lettura sporca

  /* ADCSRA – ADC Control and Status Register A
    accende l'ADC, Avvia la conversione,abilita l'impostazione del trigger scelto in ADCSRB(free running),
    e in fine imposta il prescaler a 1/128
    A queste condizioni ho 125Khz di clock all'adc e una conversione
    ogni 14*1/125KHz= 112us ~ 8,9Khz  (14 perchè letto in differential mode)
  */
  ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | 0x7; //avvia la prima conversione
  //prima lettura è sporca
  while (ADCSRA & (1 << ADIF)); //wait first reading
  ADCSRA = ADCSRA; //clear the interrupt flag
  ADCSRA |= (1 << ADIE); //attiva l'interrupt
}

int getAmpMot(int m)
{
  //enum currentPin {cMot1=0, cMot2, cMot3, cMot4, cMot5, cMot6};
  int g = ampMot[m];
  ampMot[m] = 0;
  return g;
}

int *getAmpMots()
{
  return ampMot;
}

/*
  MUX5:0  +    -   G
  010000 ADC0 ADC1 1×   Corrente mot 1
  010001 ADC1 ADC1 1×   XXXXXX----NON IN USO
  010010 ADC2 ADC1 1×   Corrente mot 2
  010011 ADC3 ADC1 1×   Corrente mot 3
  010100 ADC4 ADC1 1×   Corrente mot 4
  010101 ADC5 ADC1 1×   Corrente mot 5
  010110 ADC6 ADC1 1×   Corrente mot 6
  010111 ADC7 ADC1 1×
*/
int difPinSelect(int p)
{
  byte val = ADMUX & 0xE0; //Cancello il precedente vale selezionato, mantenendo le impostazioni
  switch (p)
  {
    case cMot1:
      val |= 0x10;
      break;
    case cMot2:
      val |= 0x12;
      break;
    case cMot3:
      val |= 0x12;
      break;
    case cMot4:
      val |= 0x14;
      break;
    case cMot5:
      val |= 0x15;
      break;
    case cMot6:
      val |= 0x17;
      break;
    default:
      return -1;
      break;
  }
  ADMUX =  val; //imposto il nuovo canale
  return 0;
}

//start value
volatile byte newRead = cMot1;
volatile byte oldRead = cMot1;
ISR(ADC_vect) {
  // Must read low first
  ampMot[oldRead] = ADCL | (ADCH << 8);
  oldRead = newRead;
  newRead = (newRead + 1) % 6;
  difPinSelect(newRead);
  
}


