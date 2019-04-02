#include "spisend.h"

SpiSend::SpiSend()
{

    this->fdSpi = open("/dev/spidev0.0", O_RDWR);

    //buffer setup
    this->size=std::max(sizeof(spiSend),sizeof(spiRet));
    printf("Size send is :%d\tSize recive is :%d\n",sizeof(spiSend),sizeof(spiRet));

    this->txbuf=(char *)malloc(sizeof(spiSend));
    this->rxbuf=(char *)malloc(sizeof(spiRet));
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

    this->setMode(s->out.type);
    if(this->sizeTypePack(s)==0) return;

    memset(this->txbuf,0,this->size);
    memset(this->rxbuf,0,this->size);

    memcpy(this->txbuf,&s->out.pack,sizeof(spiSend));  //imposto i bit utili da inviare


    printf("Byte send");
    for (int i = 0; i < this->sizeTypePack(s); ++i) {
        printf(" %d",txbuf[i]);
    }
    printf("\n");

    struct spi_ioc_transfer spi;

    memset (&spi, 0, sizeof (spi));
    spi.tx_buf        = (unsigned long)this->txbuf;
    spi.rx_buf        = (unsigned long)this->rxbuf;
    spi.len           = this->sizeTypePack(s);

    usleep(200); //16

    ioctl (this->fdSpi, SPI_IOC_MESSAGE(1), &spi);      //1 è la dimensione del buffer SPI (nel nostro caso inviamo 1 pacchetto alla volta)

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
    spi.bits_per_word =8;

    ioctl (this->fdSpi, SPI_IOC_MESSAGE(1), &spi);
}
//enum modi {setPWM=0, getCurrent, getSetting, setSetting, goHome};
int SpiSend::sizeTypePack(SPIPACK *s)
{
    switch (s->out.type) {
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
    return 0;
}



