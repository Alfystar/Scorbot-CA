# Rapsberry spi driver, 
Il codice è stato scritto in c++ e documentata con UML, la struttura della libreria è:

[![SubSystem-structure](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/SpiLib_Rasp.png?raw=true "SubSystem-structure")]("SPI raps-structure")


La Demo presente serve a comandare il robot ed esegue tutti i comandi prefissi dall'interfaccia in ricezione codificata sopra l'arduino, visibile dentro "Scorebot_code".


L'attuale demo dovrebbe comprendere tutti i comandi fino ad ora disponivili e non sono presenti particolari problemi, può essere visto come un esempio di integrazione delle librerie in un generico progetto c++.

La libreria per la gestione della spi è quella integrata nel kernel linux chiamata: 
#include <linux/spi/spidev.h>

Se si fosse interessati ad altre informazioni cercate di lei.

Da notare che ora nel codice è scritto che la frequenza di comunicazione è 50khz, ma nella verità è circa 30.5 kHz poichè il prescaler dentro il rapsberry, muovendosi di potenze di 2 ha come valore più vicino di comunicazione questo.

        cdiv    speed
        2        125.0  MHz
        4        62.5   MHz
        8        31.2   MHz
        16       15.6   MHz
        32       7.8    MHz
        64       3.9    MHz
        128      1953   kHz
        256      976    kHz
        512      488    kHz
        1024     244    kHz
        2048     122    kHz
        4096     61     kHz
        8192     30.5   kHz
        16384    15.2   kHz
        32768    7629   Hz

 
 Una buona documentazione per la struct di comunucazione col kernel la si può trovare qui:
 https://docs.huihoo.com/doxygen/linux/kernel/3.7/structspi__ioc__transfer.html

Sito dove viene spiegato il problema della memory cache coerence :
https://community.arm.com/developer/ip-products/processors/b/processors-ip-blog/posts/caches-and-self-modifying-code
