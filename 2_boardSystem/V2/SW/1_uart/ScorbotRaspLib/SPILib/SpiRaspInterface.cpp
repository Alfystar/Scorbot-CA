#include "SpiRaspInterface.h"

namespace SpiRaspInterface {
    //initiaize static variables here
    Spi_ScorBoard *Spi_ScorBoard::instance = nullptr;
    std::mutex myMutex;

    Spi_ScorBoard &Spi_ScorBoard::getInstance() {
        std::lock_guard <std::mutex> myLock(myMutex);
        if (!Spi_ScorBoard::instance) {
            Spi_ScorBoard::instance = new Spi_ScorBoard();
        }
        return *Spi_ScorBoard::instance;
    }

    Spi_ScorBoard::Spi_ScorBoard() {
        this->fdSpi = open("/dev/spidev0.0", O_RDWR);

        //buffer setup
        this->size = std::max(sizeof(data2Rasp), sizeof(data2Ard));
        //printf("Size send is :%d\tSize recive is :%d\n", sizeof(data2Ard), sizeof(data2Rasp));

        this->txbuf = (char *) malloc(this->size);
        this->rxbuf = (char *) malloc(this->size);
        memset(this->txbuf, 0, this->size);
        memset(this->rxbuf, 0, this->size);
        ioctl(this->fdSpi, SPI_MODE_0); //polarità e fase di default
        ioctl(this->fdSpi, SPI_IOC_WR_MAX_SPEED_HZ, &this->hzSpeed);
        ioctl(this->fdSpi, SPI_IOC_WR_BITS_PER_WORD, &this->bitWord);
        ioctl(this->fdSpi, SPI_IOC_RD_BITS_PER_WORD, &this->bitWord);
#ifdef ONLYRaspCompiling
        //to expose the pin and not use root (wiringPiSetupSys)
        char gpioSys[128];
        sprintf(gpioSys, "gpio export %d OUTPUT", EnCom);
        system(gpioSys);
        wiringPiSetupSys();

        //wiringPiSetupGpio();    //need to be root
        pinMode(EnCom, OUTPUT);
        digitalWrite(EnCom, 1);
#endif
    }

    Spi_ScorBoard::~Spi_ScorBoard() {
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

    std::mutex sentMutex;


    void Spi_ScorBoard::sendPack(Pack &p) {
        std::lock_guard <std::mutex> myLock(sentMutex);
        this->setMode(p.getPackType());
#ifdef ONLYRaspCompiling
        digitalWrite(EnCom, 1);
#endif

        if (p.sizePack() == 0) return;
        if (p.sizePack() == -1) {
            fprintf(stderr, "Pack type not recognize!!\n");
            return;
        }
        memset(this->txbuf, 0, this->size);
        memset(this->rxbuf, 0, this->size);
        memcpy(this->txbuf, p.getSPIPACK().forArd.buf, sizeof(data2Ard));  //imposto i bit utili da inviare

        //memory cache coerence Problem
        __builtin___clear_cache(this->txbuf, this->txbuf + this->size);
        memset(&this->spi, 0, sizeof(spi));
        this->spi.tx_buf = (unsigned long) this->txbuf;
        this->spi.rx_buf = (unsigned long) this->rxbuf;
        this->spi.len = p.sizePack();

        //attendo per dare ulteriore tempo all'arduino di caricare i dati prima dell'inizio della trasmissione
        usleep(200); //16

        ///*************************************
        ///Avvio della trasmissione
        //1 è il numero di "spi_ioc_transfer" che si vuole inviare
        ioctl(this->fdSpi, SPI_IOC_MESSAGE(1), &this->spi);

        //memory cache coerence Problem
        __builtin___clear_cache(this->rxbuf, this->rxbuf + this->size);
        memcpy(p.getSPIPACK().forRasp.buf, this->rxbuf, sizeof(data2Rasp));
#ifdef ONLYRaspCompiling
        digitalWrite(EnCom, 0);
#endif
        //this->bytePrint(p);
    }

    void Spi_ScorBoard::bytePrint(Pack &p) {
        printf("p.sizePack()=%d\n", p.sizePack());
        printf("Byte send\t");
        for (int i = 0; i < p.sizePack(); ++i) {
            printf(" %d", p.getSPIPACK().forArd.buf[i]);
        }
        printf("\n");
        printf("Byte recive\t");
        for (int i = 0; i < p.sizePack(); ++i) {
            printf(" %d", p.getSPIPACK().forRasp.buf[i]);
        }
        printf("\n");

    }

    void Spi_ScorBoard::setMode(packType mode) {
        char m = mode;
        memset(&this->spi, 0, sizeof(spi_ioc_transfer));
        this->spi.tx_buf = (unsigned long) &m;
        this->spi.rx_buf = (unsigned long) NULL;
        this->spi.len = 1;
        this->spi.bits_per_word = 8;
        ioctl(this->fdSpi, SPI_IOC_MESSAGE(1), &this->spi);
    }

    void Spi_ScorBoard::goHomePack() {
        Pack p;
        p.setPackType(goHome);
        this->sendPack(p);
    }

    void Spi_ScorBoard::setSettingPack(Pack &p) {
        p.setPackType(SettingSet);
        this->sendPack(p);
    }

    void Spi_ScorBoard::setSettingPack(settingsBoard &s) {
        Pack p;
        p.setting(pack4Rasp).copyPack(s);
        this->setSettingPack(p);
    }

    void Spi_ScorBoard::getSettingPack(Pack &p) {
        p.clearPack();
        p.setPackType(SettingGet);
        this->sendPack(p);
    }

    settingsBoard *Spi_ScorBoard::getSettingPack() {
        Pack p;
        this->getSettingPack(p);
        settingsBoard *s = (settingsBoard *) (malloc(sizeof(settingsBoard)));
        memmove(s, &p.setting(pack4Rasp).getSetting(), sizeof(settingsBoard));
        return s;
    }

    void Spi_ScorBoard::setPwm_EnPack(Pack &p) {
        p.setPackType(PWMsend_EnRet);
        this->sendPack(p);
    }

    mEncoder *Spi_ScorBoard::setPwm_EnPack(mSpeed &ms) {
        Pack p;
        p.speed().copyPack(ms);
        this->setPwm_EnPack(p);
        mEncoder *me = (mEncoder *) (malloc(sizeof(mEncoder)));
        memmove(me, p.encoder().getEn(), sizeof(mEncoder));
        return me;
    }

    void Spi_ScorBoard::setPwm_CurPack(Pack &p) {
        p.setPackType(PWMsend_CurRet);
        this->sendPack(p);
    }

    mCurrent *Spi_ScorBoard::setPwm_CurPack(mSpeed &ms) {
        Pack p;
        p.speed().copyPack(ms);
        this->setPwm_CurPack(p);
        mCurrent *mc = (mCurrent *) (malloc(sizeof(mCurrent)));
        memmove(mc, p.current().getCurrent(), sizeof(mCurrent));
        return mc;
    }

    void Spi_ScorBoard::setPwm_AllPack(Pack &p) {
        p.setPackType(PWMsend_AllRet);
        this->sendPack(p);
    }

    mAll *Spi_ScorBoard::setPwm_AllPack(mSpeed &ms) {
        Pack p;
        p.speed().copyPack(ms);
        this->setPwm_CurPack(p);
        mAll *ma = (mAll *) (malloc(sizeof(mAll)));
        memmove(ma, &p.allSens().getSens(), sizeof(mAll));
        return ma;
    }

    void Spi_ScorBoard::getEnPack(Pack &p) {
        p.clearPack();
        p.speed().pwmSet(ignore, ignore, ignore, ignore, ignore, ignore);
        this->setPwm_EnPack(p);
    }

    mEncoder *Spi_ScorBoard::getEnPack() {
        Pack p;
        p.speed().pwmSet(ignore, ignore, ignore, ignore, ignore, ignore);
        this->setPwm_EnPack(p);
        mEncoder *me = (mEncoder *) (malloc(sizeof(mEncoder)));
        memmove(me, p.encoder().getEn(), sizeof(mEncoder));
        return me;
    }

    void Spi_ScorBoard::getCurrentPack(Pack &p) {
        p.clearPack();
        p.speed().pwmSet(ignore, ignore, ignore, ignore, ignore, ignore);
        p.setPackType(PWMsend_CurRet);
        this->sendPack(p);
    }

    mCurrent *Spi_ScorBoard::getCurrentPack() {
        Pack p;
        this->getCurrentPack(p);
        mCurrent *mc = (mCurrent *) (malloc(sizeof(mCurrent)));
        memmove(mc, p.current().getCurrent(), sizeof(mCurrent));
        return mc;
    }

    void Spi_ScorBoard::getSensPack(Pack &p) {
        p.clearPack();
        p.speed().pwmSet(ignore, ignore, ignore, ignore, ignore, ignore);
        p.setPackType(PWMsend_AllRet);
        this->sendPack(p);
    }

    mAll *Spi_ScorBoard::getSensPack() {
        Pack p;
        this->getSensPack(p);
        mAll *ma = (mAll *) (malloc(sizeof(mAll)));
        memmove(ma, &p.allSens().getSens(), sizeof(mAll));
        return ma;
    }
}
