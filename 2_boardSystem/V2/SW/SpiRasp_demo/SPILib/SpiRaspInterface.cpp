#include "SpiRaspInterface.h"

namespace SpiRaspInterface {
    //initiaize static variables here
    ScorBoard *ScorBoard::instance = nullptr;
    std::mutex myMutex;

    ScorBoard &ScorBoard::getInstance() {
        std::lock_guard<std::mutex> myLock(myMutex);
        if (!ScorBoard::instance) {
            ScorBoard::instance = new ScorBoard();
        }
        return *ScorBoard::instance;
    }

    ScorBoard::ScorBoard() {
        printf("Data size:\n");
        printf("packType size : %d\n",sizeof(packType));
        printf("mEncoder size : %d\n",sizeof(mEncoder));
        printf("mCurrent size : %d\n",sizeof(mCurrent));
        printf("mAll size : %d\n",sizeof(mAll));
        printf("settingsBoard size : %d\n",sizeof(settingsBoard));
        printf("adcRef size : %d\n",sizeof(adcRef));
        printf("bool(diff read) size : %d\n",sizeof(bool));
        printf("pwmFreq size : %d\n",sizeof(pwmFreq));

        this->fdSpi = open("/dev/spidev0.0", O_RDWR);

        //buffer setup
        this->size = std::max(sizeof(spi2Rasp), sizeof(spi2Ard));
        //printf("Size send is :%d\tSize recive is :%d\n", sizeof(spi2Ard), sizeof(spi2Rasp));

        this->txbuf = (char *) malloc(this->size);
        this->rxbuf = (char *) malloc(this->size);
        memset(this->txbuf, 0, this->size);
        memset(this->rxbuf, 0, this->size);
        ioctl(this->fdSpi, SPI_MODE_0); //polarità e fase di default
        ioctl(this->fdSpi, SPI_IOC_WR_MAX_SPEED_HZ, &this->hzSpeed);
        ioctl(this->fdSpi, SPI_IOC_WR_BITS_PER_WORD, &this->bitWord);
        ioctl(this->fdSpi, SPI_IOC_RD_BITS_PER_WORD, &this->bitWord);

        //to expose the pin and not use root (wiringPiSetupSys)
        char gpioSys[128];
        sprintf(gpioSys,"gpio export %d OUTPUT",EnCom);
        system(gpioSys);
        wiringPiSetupSys();

        //wiringPiSetupGpio();    //need to be root
        pinMode(EnCom,OUTPUT);
        digitalWrite(EnCom,1);
    }

    ScorBoard::~ScorBoard() {
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


    void ScorBoard::sendPack(Pack &p) {
        std::lock_guard<std::mutex> myLock(sentMutex);
        digitalWrite(EnCom,1);
        this->setMode(p.getPackType());
        if (p.sizePack() == 0) return;
        if (p.sizePack() == -1) {
            fprintf(stderr, "Pack type not recognize!!\n");
            return;
        }
        memset(this->txbuf, 0, this->size);
        memset(this->rxbuf, 0, this->size);
        memcpy(this->txbuf, p.getSPIPACK().forArd.buf, sizeof(spi2Ard));  //imposto i bit utili da inviare

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
        memcpy(p.getSPIPACK().forRasp.buf, this->rxbuf, sizeof(spi2Rasp));
        digitalWrite(EnCom,0);
        this->bytePrint(p);
    }

    void ScorBoard::bytePrint(Pack &p) {
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

    void ScorBoard::setMode(packType mode) {
        char m = mode;
        memset(&this->spi, 0, sizeof(spi_ioc_transfer));
        this->spi.tx_buf = (unsigned long) &m;
        this->spi.rx_buf = (unsigned long) NULL;
        this->spi.len = 1;
        this->spi.bits_per_word = 8;
        ioctl(this->fdSpi, SPI_IOC_MESSAGE(1), &this->spi);
    }

    void ScorBoard::goHomePack() {
        Pack p;
        p.setPackType(goHome);
        this->sendPack(p);
    }

    void ScorBoard::setSettingPack(Pack &p) {
        p.setPackType(SettingSet);
        this->sendPack(p);
    }

    void ScorBoard::setSettingPack(settingsBoard &s) {
        Pack p;
        p.setSetting(s, pack4Ard);
        this->setSettingPack(p);
    }

    void ScorBoard::getSettingPack(Pack &p) {
        p.clearPack();
        p.setPackType(SettingGet);
        this->sendPack(p);
    }

    settingsBoard *ScorBoard::getSettingPack() {
        Pack p;
        this->getSettingPack(p);
        settingsBoard *s = (settingsBoard *) (malloc(sizeof(settingsBoard)));
        memmove(s, &p.getSetting(pack4Rasp), sizeof(settingsBoard));
        return s;
    }

    void ScorBoard::setPwm_EnPack(Pack &p) {
        p.setPackType(PWMsend_EnRet);
        this->sendPack(p);
    }

    mEncoder *ScorBoard::setPwm_EnPack(mSpeed &ms) {
        Pack p;
        p.pwmSet(ms);
        this->setPwm_EnPack(p);
        mEncoder *me = (mEncoder *) (malloc(sizeof(mEncoder)));
        memmove(me, p.getEncoder(), sizeof(mEncoder));
        return me;
    }

    void ScorBoard::setPwm_CurPack(Pack &p) {
        p.setPackType(PWMsend_CurRet);
        this->sendPack(p);
    }

    mCurrent *ScorBoard::setPwm_CurPack(mSpeed &ms) {
        Pack p;
        p.pwmSet(ms);
        this->setPwm_CurPack(p);
        mCurrent *mc = (mCurrent *) (malloc(sizeof(mCurrent)));
        memmove(mc, p.getCurrent(), sizeof(mCurrent));
        return mc;
    }

    void ScorBoard::setPwm_AllPack(Pack &p) {
        p.setPackType(PWMsend_AllRet);
        this->sendPack(p);
    }

    mAll *ScorBoard::setPwm_AllPack(mSpeed &ms) {
        Pack p;
        p.pwmSet(ms);
        this->setPwm_CurPack(p);
        mAll *ma = (mAll *) (malloc(sizeof(mAll)));
        memmove(ma, &p.getSens(), sizeof(mAll));
        return ma;
    }

    void ScorBoard::getEnPack(Pack &p) {
        p.clearPack();
        p.pwmSet(ignore, ignore, ignore, ignore, ignore, ignore);
        this->setPwm_EnPack(p);
    }

    mEncoder *ScorBoard::getEnPack() {
        Pack p;
        p.pwmSet(ignore, ignore, ignore, ignore, ignore, ignore);
        this->setPwm_EnPack(p);
        mEncoder *me = (mEncoder *) (malloc(sizeof(mEncoder)));
        memmove(me, p.getEncoder(), sizeof(mEncoder));
        return me;
    }

    void ScorBoard::getCurrentPack(Pack &p) {
        p.clearPack();
        p.pwmSet(ignore, ignore, ignore, ignore, ignore, ignore);
        p.setPackType(PWMsend_CurRet);
        this->sendPack(p);
    }

    mCurrent *ScorBoard::getCurrentPack() {
        Pack p;
        this->getCurrentPack(p);
        mCurrent *mc = (mCurrent *) (malloc(sizeof(mCurrent)));
        memmove(mc, p.getCurrent(), sizeof(mCurrent));
        return mc;
    }

    void ScorBoard::getSensPack(Pack &p) {
        p.clearPack();
        p.pwmSet(ignore, ignore, ignore, ignore, ignore, ignore);
        p.setPackType(PWMsend_AllRet);
        this->sendPack(p);
    }

    mAll *ScorBoard::getSensPack() {
        Pack p;
        this->getSensPack(p);
        mAll *ma = (mAll *) (malloc(sizeof(mAll)));
        memmove(ma->cur, p.getCurrent(), sizeof(mCurrent));
        memmove(ma->en, p.getEncoder(), sizeof(mEncoder));
        return ma;
    }

    ///##########################################################################################
    ///############################## ScoreCalc Metod ###########################################
    ///##########################################################################################
    //initiaize static variables here
    float ScoreCalc::vRef = 1.1;
    float ScoreCalc::vCs = 0.14;

    ScoreCalc::ScoreCalc() {
        //default value
        ScoreCalc(0.14, 1.1);
    }

    ScoreCalc::ScoreCalc(float vR, float vC) {
        ScoreCalc::vRef = vR;
        ScoreCalc::vCs = vC;
    }

    float ScoreCalc::currentConvert(Pack &p, motCode nMot) {
        this->currentConvert(p.getCurrent()[nMot]);
        return 0;
    }

    float ScoreCalc::currentConvert(int c) {
        float iRead = (ScoreCalc::vRef * c) / (1024 * ScoreCalc::vCs);
        return 0;

    }

    void ScoreCalc::vRefSet(float v) {
        if (v == in2V56) v = 2.56;
        else if (v == in1V1) v = 1.1;
        else if (v < 0) v = 0.140;
        ScoreCalc::vRef = v;
    }

    float ScoreCalc::vRefGet() {
        return this->vRef;
    }

    void ScoreCalc::vCsSet(float v) {
        if (v < 0) v = 0.140;
        ScoreCalc::vCs = v;
    }

    float ScoreCalc::vCsGet() {
        return this->vCs;
    }


}
