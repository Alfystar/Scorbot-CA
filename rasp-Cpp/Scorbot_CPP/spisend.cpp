#include "spisend.h"

SpiSend::SpiSend()
{

    this->fdSpi = open("/dev/spidev0.0", O_RDWR);

    //buffer setup
    this->size=std::max(sizeof(setPWMSend),sizeof(feedRet));
    printf("Size sen is :%d\n",this->size);
    //char *txbuf,*rxbuf;
    this->txbuf=(char *)malloc(this->size);
    this->rxbuf=(char *)malloc(this->size);
    memset(this->txbuf,0,this->size);
    memset(this->rxbuf,0,this->size);
}

SpiSend::~SpiSend()
{
    free(this->txbuf);
    free(this->rxbuf);
}

void SpiSend::hello()
{
    printf("hello word");
}

feedRet * SpiSend::sendPWM(setPWMSend *s)
{

    this->setMode(setPWM);

    feedRet *r=(feedRet *)malloc(sizeof(feedRet));
    struct spi_ioc_transfer spi;

    memset (&spi, 0, sizeof (spi));

    memcpy(this->txbuf,s,sizeof(setPWMSend));                                     //imposto i bit utili da inviare
    //memset (this->txbuf+sizeof(pwmSend), 0, this->size-sizeof(pwmSend));      //riempo a 0 i bit rimasti

    spi.tx_buf        = (unsigned long)this->txbuf;
    spi.rx_buf        = (unsigned long)this->rxbuf;
    spi.len           = size;
    spi.speed_hz      = 250000;

    usleep(16);

    ioctl (this->fdSpi, SPI_IOC_MESSAGE(1), &spi);      //1 è la dimensione del buffer SPI (nel nostro caso inviamo 1 pacchetto alla volta)

    memcpy(r,this->rxbuf,sizeof(feedRet));

    return r;
}

void SpiSend::setMode(char mode)
{

     struct spi_ioc_transfer spi;

     memset (&spi, 0, sizeof (spi));

     spi.tx_buf        = (unsigned long)&mode;
     spi.rx_buf        = (unsigned long)NULL;
     spi.len           = 1;

     ioctl (this->fdSpi, SPI_IOC_MESSAGE(1), &spi);
}



