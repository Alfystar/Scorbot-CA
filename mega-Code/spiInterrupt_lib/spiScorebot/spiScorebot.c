void spiSetup() {
  pinMode(MISO, OUTPUT);
  memset(&reciveSpi, 0, sizeof(spiRecive) * 2);
  idTransf = 0;
  SPCR = (1 << SPIE) | (1 << SPE); //attiva spi e abilita interrupt
  SPDR = 0; //predispomgo che al primo invio invio 0
}

spiRecive* getLastRecive()
{
  return &reciveSpi[dirtyRecive];
}

byte spiAvailable()
{
  if(newRecive!=0){
    newRecive=0;
    return 1;
  }else return 0;
}

void isrFunxISP (){
  if (idTransf == 0) {
    reciveSpi[dirtyRecive].type = SPDR;
    preparaDati(reciveSpi[dirtyRecive].type);
    SPDR = *((char *)&_sendSpi + idTransf);
    idTransf++;
  } else if (idTransf < limitiDati(reciveSpi[dirtyRecive].type)) {
    //salva nuovo dato
    char *mem = ((char *)&reciveSpi[dirtyRecive] + idTransf);
    * mem = SPDR;
    SPDR = *((char *)&_sendSpi + idTransf);
    idTransf++;
  } else {
    //comunicazione all'ultimo byte
    char *mem = ((char *)&reciveSpi[dirtyRecive] + idTransf);
    * mem = SPDR;
    SPDR = *((char *)&_sendSpi + idTransf);
    idTransf = 0;
    dirtyRecive = !dirtyRecive;
    newRecive=1;
  }
}

void preparaDati(char type) {
  switch (type)
  {
    case setPWM:
      memcpy(&_sendSpi.pack.feedBack.encoder, hello, 32);
      break;
    case getSetting:
      break;
    case setSetting:
      break;
    case setHome:
      break;
    case goHome:
      break;
    default:
      break;
  }
}

int limitiDati(char type) {
  switch (type)
  {
    case setPWM:
      return 32;
      break;
    case getSetting:
      return 32;
      break;
    case setSetting:
      return 32;
      break;
    case setHome:
      return 32;
      break;
    case goHome:
      return 32;
      break;
    default:
      return 32;
      break;
  }
}
