#include "spisend.h"

SpiSend::SpiSend()
{

    this->fdSpi = open("/dev/spidev0.0", O_RDWR);

    //buffer setup
    this->size=std::max(sizeof(spiSend),sizeof(spiRet));
    printf("Size send is :%d\tSize recive is :%d\n",sizeof(spiSend),sizeof(spiRet));

    this->txbuf=(char *)malloc(this->size);
    this->rxbuf=(char *)malloc(this->size);
    memset(this->txbuf,0,this->size);
    memset(this->rxbuf,0,this->size);

    ioctl(this->fdSpi, SPI_MODE_0); //polarità e fase di default
    ioctl(this->fdSpi, SPI_IOC_WR_MAX_SPEED_HZ, &this->hzSpeed);
    ioctl(this->fdSpi, SPI_IOC_WR_BITS_PER_WORD, &this->bitWord);
    ioctl(this->fdSpi, SPI_IOC_RD_BITS_PER_WORD, &this->bitWord);
}
SpiSend::~SpiSend()
{
    free(this->txbuf);
    free(this->rxbuf);
}

/* struct spi_ioc_transfer - describes a single SPI transfer
 * @tx_buf: Holds pointer to userspace buffer with transmit data, or null.
 *          If no data is provided, zeroes are shifted out.
 * @rx_buf: Holds pointer to userspace buffer for receive data, or null.
 * @len: Length of tx and rx buffers, in bytes.
 * @speed_hz: Temporary override of the device's bitrate.
 * @bits_per_word: Temporary override of the device's wordsize.
 * @delay_usecs: If nonzero, how long to delay after the last bit transfer
 *          before optionally deselecting the device before the next transfer.
 * @cs_change: True to deselect device before starting the next transfer.
 */

void SpiSend::sendPack(SPIPACK *s)
{

    this->setMode(s->type);
    if(this->sizeTypePack(s)==0) return;
    if(this->sizeTypePack(s)==-1)
    {
        fprintf(stderr,"Pack type not recognize!!\n");
        return;
    }

    memset(this->txbuf,0,this->size);
    memset(this->rxbuf,0,this->size);

    memcpy(this->txbuf,&s->out.pack,sizeof(spiSend));  //imposto i bit utili da inviare


    printf("Byte send");
    for (int i = 0; i < this->sizeTypePack(s); ++i) {
        printf(" %d",txbuf[i]);
    }
    printf("\n");

    //flush_tlb_all();
    __builtin___clear_cache(this->txbuf,this->txbuf+this->size);

    struct spi_ioc_transfer spi;

    memset (&spi, 0, sizeof (spi));
    spi.tx_buf        = (unsigned long)this->txbuf;
    spi.rx_buf        = (unsigned long)this->rxbuf;
    spi.len           = this->sizeTypePack(s);

    usleep(200); //16

    ioctl (this->fdSpi, SPI_IOC_MESSAGE(1), &spi);      //1 è la dimensione del buffer SPI (nel nostro caso inviamo 1 pacchetto alla volta)

    __builtin___clear_cache(this->rxbuf,this->rxbuf+this->size);

    memcpy(&s->in,this->rxbuf,sizeof(spiRet));

    printf("Byte recive");
    for (int i = 0; i < this->sizeTypePack(s); ++i) {
        printf(" %d",this->rxbuf[i]);
    }
    printf("\n");


}

void SpiSend::setMode(char mode)
{
    char m=mode;
    struct spi_ioc_transfer spi;

    memset (&spi, 0, sizeof (spi));

    spi.tx_buf        = (unsigned long)&m;
    spi.rx_buf        = (unsigned long)NULL;
    spi.len           = 1;
    spi.bits_per_word = 8;

    ioctl (this->fdSpi, SPI_IOC_MESSAGE(1), &spi);
}
//enum modi {setPWM=0, getCurrent, getSetting, setSetting, goHome};
int SpiSend::sizeTypePack(SPIPACK *s)
{
    switch (s->type) {
    case setPWM:
        return std::max(sizeof(setPWMSend),sizeof(setPWMRet));
        break;
    case getCurrent:
        return sizeof(getCurrentRet);
        break;
    case getSetting:
        return sizeof(getSettingRet);
        break;
    case setSetting:
        return sizeof(setSettingSend);
        break;
    case goHome:
        return 0;
        break;
    }
    return -1;
}


void SpiSend::printSPIPACK(SPIPACK *s){
    switch(s ->type){
    case setPWM:
        printf("Command 'setPWM'\n");
        printf("Sending actual speed:\n");
        printf("Vel:\t");

        for (int i = 0; i < nMot; i++){
            printf("%d)%hd\t",i+1,s->out.pack.speed.vel[cMot1 + i]);
        }

        printf("\nReciving actual encoder:\n");
        printf("En:\t");
        for (int i = 0; i < nMot; i++){
            printf("%d)%hd\t",i+1,s->in.pack.en.passi[cMot1 + i]);
        }
        break;

    case getCurrent:
        printf("Command 'getCurrent'\n");

        printf("Sending: no parameters\n");
        printf("Reciving actual currents:\n");
        printf("Curr:\t");
        for (int i = 0; i < nMot; i++){
            printf("%d)%hd\t",i+1,s->in.pack.cur.current[cMot1 + i]);
        }
        break;

    case getSetting:
        printf("Command 'getSetting'\n");
        printf("Sending: no parameters\n");
        printf("Reciving actual settings:\n");
        printf("maxEn:\t");

        for (int i = 0; i < nMot; i++){
            printf("%d)%hd\t",i+1,s->in.pack.prop.sets.maxEn[cMot1 + i]);
        }

        printf("\nminEn:\t");
        for (int i = 0; i < nMot; i++){
            printf("%d)%hd\t",i+1,s->in.pack.prop.sets.minEn[cMot1 + i]);
        }

        printf("\nmaxCurrMed:\t");
        for (int i = 0; i < nMot; i++){
            printf("%d)%hd\t",i+1,s->in.pack.prop.sets.maxCurrMed[cMot1 + i]);
        }
        break;

    case setSetting:
        printf("Command 'setSetting'\n");
        printf("Sending actual settings:\n");

        printf("maxEn:\t");
        for (int i = 0; i < nMot; i++){
            printf("%d)%hd\t",i+1,s->out.pack.prop.sets.maxEn[cMot1 + i]);
        }

        printf("\nminEn:\t");
        for (int i = 0; i < nMot; i++){
            printf("%d)%hd\t",i+1,s->out.pack.prop.sets.minEn[cMot1 + i]);
        }

        printf("\nmaxCurrMed:\t");
        for (int i = 0; i < nMot; i++){
            printf("%d)%hd\t",i+1,s->out.pack.prop.sets.maxCurrMed[cMot1 + i]);
        }

        printf("\nReciving: no parameters\n");
        break;

    case goHome:
        printf("Command 'goHome'\n");
        printf("Sending: no parameters\n");
        printf("Reciving: no parameters\n");
        break;
    }
    printf("\n-------------------------------------------------------\n");
}

SPIPACK *SpiSend::getEn(SPIPACK *p)
{
    setPWMSend enPack;
    this->fillPWMPACK(&enPack,ig,ig,ig,ig,ig,ig);
    return  this->pSetPWM(p,&enPack);
}


SPIPACK *SpiSend::pSetPWM(SPIPACK *p, setPWMSend *pwm)
{

    p->type=setPWM;
    memcpy(&p->out.pack.speed,pwm,sizeof(setPWMSend));

    this->sendPack(p);
    return p;
}


void fillmot(setPWMSend * pack,int mVal,int mNum)
{
    if(mVal==fr || mVal==hs || mVal==ss || mVal==ig || abs(mVal)<255)
         pack->vel[mNum]=mVal;
     else
         pack->vel[mNum]=ig;
}

setPWMSend *SpiSend::fillPWMPACK(setPWMSend * pack,int m1,int m2,int m3,int m4,int m5,int m6){
   fillmot(pack,m1,cMot1);
   fillmot(pack,m2,cMot2);
   fillmot(pack,m3,cMot3);
   fillmot(pack,m4,cMot4);
   fillmot(pack,m5,cMot5);
   fillmot(pack,m6,cMot6);
   return pack;
}


SPIPACK *SpiSend::pGetCurrent(SPIPACK *p)
{

    p->type=getCurrent;

    this->sendPack(p);
    return p;
}
SPIPACK *SpiSend::pGetSetting(SPIPACK *p)
{

    p->type=getSetting;

    this->sendPack(p);
    return p;
}
SPIPACK *SpiSend::pSetSetting(SPIPACK *p,setSettingSend *sets)
{

    p->type=setSetting;
    memcpy(&p->out.pack.prop,sets,sizeof(setSettingSend));

    this->sendPack(p);
    return p;
}

SPIPACK *SpiSend::pGoHome(SPIPACK *p)
{
    p->type=goHome;

    this->sendPack(p);
    return p;
}

SPIPACK *SpiSend::makeSPIPACK()
{
    SPIPACK *p = (SPIPACK *) malloc(sizeof(SPIPACK));
    memset(p,0,sizeof(SPIPACK));
    return p;
}

void SpiSend::freeSPIPACK(SPIPACK *p)
{
    free(p);
}

