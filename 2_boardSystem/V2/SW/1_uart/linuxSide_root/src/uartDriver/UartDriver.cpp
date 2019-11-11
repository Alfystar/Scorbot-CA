//
// Created by alfyhack on 10/11/19.
//

#include "UartDriver.h"

namespace Uart {
    UartDriver::UartDriver(const std::string &device) {
        this->fd = open(device.c_str(), O_RDWR | O_NOCTTY);//| O_NDELAY
        if (fd == -1) {
            perror("failed to open port");
            throw UartExeption("Failed to open port and get FD", errno);
        }
        if (!isatty(fd)) {
            perror("Not Uart");
            throw UartExeption("Not Uart", errno);
        }
        if (tcgetattr(fd, &config)) {
            throw UartExeption("Impossibile leggere la configurazione", errno);
        }
        // Input flags - Turn off input processing
        config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
        // Output flags - Turn off output processing
        config.c_oflag = 0;
        // Output flags - Turn off output processing
        config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
        // Turn off character processing
        config.c_cflag &= ~(CSIZE | PARENB);
        config.c_cflag |= CS8;
        // One input byte is enough to return from read()
        // Inter-character timer off
        config.c_cc[VMIN] = 1;
        config.c_cc[VTIME] = 0;
        // Communication speed (simple version, using the predefined constants)
        if (cfsetispeed(&config, B115200) || cfsetospeed(&config, B115200)) {
            throw UartExeption("Impossibile Impostare velocità di cominicazione", errno);
        }
        // Finally, apply the configuration
        if (tcsetattr(fd, TCSAFLUSH, &config)) {
            throw UartExeption("Impossibile Impostare i parametri selezionati", errno);
        }

        ///##################################################################################################
        ///Internal structure initialize
        this->packAvailable = 0;
        this->potPackType = 0;
        this->potPackStart = 0;
        this->expettedEnd = 0;
        memset(reciveBuf, 0, sizeof(reciveBuf));
        this->cbByteRecive = new CircularBuffer<unsigned char>(reciveBuf, sizeof(reciveBuf));
        memset(cbReciveBuf, 0, sizeof(cbReciveBuf));
        this->cbRecive = new CircularBuffer<uart2Rasp>(cbReciveBuf, sizeof(cbReciveBuf));

//        memset(cbSendBuf, 0, sizeof(cbSendBuf));
//        this->cbSend = new CircularBuffer<uart2Ard>(cbSendBuf, sizeof(cbSendBuf));

        //pthread_t readerTh;
        //pthread_create(&readerTh, nullptr, this->uartReader, this);
        this->readerTh = new std::thread(this->uartReader, this);
    }

    size_t UartDriver::Available() {
        return this->packAvailable;
    }

    uart2Rasp *UartDriver::getLastRecive() {
        if (Available() > 0) {
            this->packAvailable--;
            return this->cbRecive->getPtr();
        }
        return nullptr;
    }

    std::mutex WriteUart_mutex;  // protects packSend from concurrency

    void UartDriver::packSend(uartPackType type, data2Rasp *pack) {
        size_t bWrite;
        char mexSize;
        char writeBuf[sizeof(data2Rasp) + 3];  //max data size + startCode+ End code + type;

        std::lock_guard<std::mutex> lock(WriteUart_mutex);
        // WriteUart_mutex is automatically released when lock goes out of scope

        mexSize = sizeMessage(type);
        writeBuf[0] = StartCode;
        writeBuf[1] = type;
        memcpy(&writeBuf[2], pack, mexSize);
        writeBuf[0] = EndCode;
        int i = 0;
        while (mexSize > 0) {
            bWrite = write(fd, &writeBuf[i], mexSize);
            if (bWrite < 0) {
                perror("Reading take error:");
                exit(-1);
            }
            i += bWrite;
            mexSize -= bWrite;
        }
    }

    size_t bRead;

    void UartDriver::uartReader(UartDriver *d) {
        std::cout << "uartReader Thread start\n";
        //UartDriver *d = (UartDriver *) data;
        for (;;) {
            bRead = read(d->fd, d->cbByteRecive->getHeadPtr(), d->cbByteRecive->linearEnd());
            //std::cout<<"uartReader read:"<< bRead<<"\n";
            if (bRead < 0) {
                perror("Reading take error:");
                exit(-1);
            }
            d->cbByteRecive->put_externalWrite(bRead);
            d->dataDiscover();
        }
    }

    unsigned char dato;

    size_t datoId;

    void UartDriver::dataDiscover() {
        std::cout << "dataDiscover:\n";
        while (!cbByteRecive->empty()) {
            datoId = cbByteRecive->getTail();
            dato = cbByteRecive->get();
            std::cout << "\tdatoId = " << datoId << "  dato = " << (int) dato << "\n";
            switch (this->stateUart) {
                default:
                case waitStart:
                    //verifico che se è l'inizio di un pacchetto
                    if (dato == StartCode)
                        this->stateUart = waitType;
                    break;
                case waitType:
                    //ho letto uno start, se anche il type è compatibile allora probabilmente è un pacchetto
                    this->potPackStart = datoId; //se è buono salvo l'inizio del pacchetto (type compreso), altrimenti non da fastidio
                    this->potPackType = dato;
                    //se tra  mSpeedData <--> mEncoderData è un pacchetto con una dimensione
                    if ((potPackType >= uartPackType::mSpeedData)
                        && (potPackType <= uartPackType::RESEND)) { //valid type
                        this->stateUart = waitEnd;
                        //l'end sarà alla dimensione del messaggio +1
                        this->expettedEnd = 1 + this->sizeMessage((uartPackType) potPackType);
                    } else //altrimenti torno ad aspettare nuovi dati
                        this->stateUart = waitStart;
                    break;
                case waitEnd:
                    this->expettedEnd--;    //manca ogni volta un pacchetto in meno
                    if (this->expettedEnd == 0) {
                        if (dato == EndCode) {
                            //Aggiungo esternamente a cbRecive il pacchetto ricevuto
                            cbByteRecive->writeMemOut((unsigned char *) this->cbRecive->getHeadPtr(), potPackStart,
                                                      this->sizeMessage((uartPackType) potPackType));
                            //aggiorno il buffer dei pacchetti aggiungendone 1
                            this->cbRecive->put_externalWrite();
                            this->packAvailable++;
                        } else {    //ho atteso per nulla, non è la fine corretta
                            //todo per ora se non trovo il pacchetto ignoro e vado al prossimo, in futuro può cercare nell'intervallo tra
                            //potentialPackStart ed head se esiste un altro start e poi type e ricomincio la macchina a stati da lì
                            this->stateUart = waitStart;
                        }
                    }
                    break;
            }//End switch
        }//End while
    }

    //mSpeedData=1,settingBoardData, mCurrentData, mAllData, mEncoderData, sampleTimeEn , sampleTimeCur, goHomeUart, settingAsk, RESEND
    char UartDriver::sizeMessage(uartPackType t) {
        switch (t) {
            case mSpeedData:
                return sizeof(mSpeed);
            case settingBoardData:
                return sizeof(settingsBoard);
            case mCurrentData:
                return sizeof(mCurrent);
            case mAllData:
                return sizeof(mAll);
            case mEncoderData:
                return sizeof(mEncoder);
            case sampleTimeEn:
            case sampleTimeCur:
                return sizeof(short);
            case goHomeUart:
            case settingAsk:
            case RESEND:
            default:
                return 0;
                break;
        }
    }

    void UartDriver::serialPackDb(uart2Ard &p) {
        std::cout << "serialPackDb(uartRecivePack):" << &p << "\n";
        switch (p.type) {
            case mSpeedData:
                SpeedMot::printSpeed(p.pack.up.speed);
                break;
            case settingBoardData:
                SettingBoard_C::printSetting(p.pack.up.prop);
                break;
            case sampleTimeEn:
                std::cout << "Data Recive: sampleTimeEn:" << (p.pack.up.sampleEn);
                break;
            case sampleTimeCur:
                std::cout << "Data Recive: sampleTimeCur:" << (p.pack.up.sampleCur);
                break;
            default:
                std::cout << "Dentro Default!! type=" << p.type << "\n";
                break;
        }
    }

    void UartDriver::serialPackDb(uart2Rasp &p) {
        std::cout << "serialPackDb(uartSendPack):" << &p << "\n";
        switch (p.type) {
            case mEncoderData:
                EncoderMot::printEncoder(p.pack.up.en);
                break;
            case mCurrentData:
                CurrentMot::printCurrent(p.pack.up.cur);
                break;
            case mAllData:
                AllSensor::printAll(p.pack.up.sens);
                break;
            case settingBoardData:
                SettingBoard_C::printSetting(p.pack.up.prop);
                break;
            default:
                std::cout << "Dentro Default!! type=" << p.type << "\n";
                break;
        }
    }
}