#include "SpiRaspInterface.h"

namespace SpiRaspInterface {
    //initiaize static variables here
    ScorBoard *ScorBoard::instance = nullptr;
    std::mutex myMutex;

    ScorBoard &ScorBoard::getInstance() {
        std::lock_guard <std::mutex> myLock(myMutex);
        if (!ScorBoard::instance) {
            ScorBoard::instance = new ScorBoard();
        }
        return *ScorBoard::instance;
    }

    ScorBoard::ScorBoard() {
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
        sprintf(gpioSys, "gpio export %d OUTPUT", EnCom);
        system(gpioSys);
        wiringPiSetupSys();

        //wiringPiSetupGpio();    //need to be root
        pinMode(EnCom, OUTPUT);
        digitalWrite(EnCom, 1);
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
        std::lock_guard <std::mutex> myLock(sentMutex);
        digitalWrite(EnCom, 1);
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
        digitalWrite(EnCom, 0);
        //this->bytePrint(p);
    }

    void ScorBoard::bytePrint(Pack &p) {
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
        p.setSetting(pack4Ard, s);
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
    int ScoreCalc::bitAdc = 10;

    ScoreCalc::ScoreCalc() {
        //default value
        ScoreCalc(ScoreCalc::vRef, ScoreCalc::vCs, ScoreCalc::bitAdc);
    }

    ScoreCalc::ScoreCalc(float vR, float vC, int bitAdc) {
        ScoreCalc::vRef = vR;
        ScoreCalc::vCs = vC;
        ScoreCalc::bitAdc = bitAdc;
    }

    void ScoreCalc::settingPrint()
    {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("ScoreCalc execute trasformation with:\n");
        printf("Vref:\t%.3fV\n",this->vRefGet());
        printf("vCs:\t%.3fV\n",this->vCsGet());
        printf("bitAdc:\t%dBit (range:%d)\n",this->bitAdcGet(),this->rangeAdcGet());
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }

    float ScoreCalc::vRefNeed(float Imax)
    {
        this->vRefNeed(Imax,this->vCsGet());
    }

    float ScoreCalc::vRefNeed(float Imax,float Vcs)
    {
        return Imax*Vcs;
    }

    void ScoreCalc::adc2curr(Pack &currPack)
    {
        if(currPack.getPackType()==PWMsend_CurRet || currPack.getPackType()==PWMsend_AllRet)
        {
            for(int i = Mot1;i<nMot;i++){
                printf("%d)%4.3fA\t", i + 1, this->adc2curr(currPack.getCurrent()[i]));
            }
            printf("\n");
        }else{
            printf("PACK type not correct!!!\n");
        }
    }

    float ScoreCalc::adc2curr(int adc) {
        return this->adc2curr(adc,this->vRefGet(),this->vCsGet(),this->bitAdcGet());
    }

    float ScoreCalc::adc2curr(int adc, float vRef, float vCs, int bitADC) {
        float iRead = (vRef * adc) / (pow(2,bitADC) * vCs);
        return iRead;
    }

    int ScoreCalc::curr2adc(float curr) {
        return this->curr2adc(curr,this->vRefGet(),this->vCsGet(),this->bitAdcGet());
    }

    int ScoreCalc::curr2adc(float curr, float vRef, float vCs, int bitADC) {
        int adcExpetted= (curr * pow(2,bitADC) * vCs) / (vRef);
        return adcExpetted;
    }

    void ScoreCalc::vRefSet(float v) {
        if (v < 0) v = 1.1;
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

    void ScoreCalc::bitAdcSet(int bit)
    {
        if (bit < 1) bit = 1;
        ScoreCalc::bitAdc = bit;
    }

    int ScoreCalc::bitAdcGet()
    {
        return ScoreCalc::bitAdc;
    }

    int ScoreCalc::rangeAdcGet()
    {
        return pow(2,ScoreCalc::bitAdc);
    }

}
