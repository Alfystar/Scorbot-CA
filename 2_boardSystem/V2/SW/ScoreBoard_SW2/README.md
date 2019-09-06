# Arduino MEGA (atmega2560) Firmware
La libreria sviluppata è scritta in c++ ed è pensata per essere eseguita sull'arduino MEGA della board progettata in "eagle-brd".

MOLTO IMPORTANTE AGGIUNGERE ALLA FINE DEL COMPILATORE GCC IL DEFINE:
	-D ScorboarFirmware
serve per evitare di far includere librerie e codici che devo essere presenti solo nella versione Rapsberry

## Ide di sviluppo
Il codice è stato sviluppato usando come editor Sloebel, un tool open gratuito che si basa su di eclipse, è stato proggettato per essere compatibile con le schede arduino presenti in commercio, se caricate questo progetto con sloebel sicuramente lo riuscirà a leggere e successivamente a caricare sulla scheda.
### Windows user
Se siete su windows oltre la come e poche altri dettagli siete ready to go.

### Linux user
Su linux prima di caricare il codice dovete andare in :
    /dev/

Trovare la ttyAMC* che ha montato ora il vostro arduino, quindi cambiare i diritti di accesso aggiungendo oltre il root, anche la possibilità di leggere, scrivere ed eseguire agli altri utenti. 
!!Attenzione che l'operazione andrà ripetuta ogni volta che si collega l'arduino!!

I comandi da eseguire che funzionano sempre sono:

    cd /dev/
    ls -l ttyAMC*
    sudo chmod o+rwx ttyAMC* 

Con questi comandi sarete in grado di sapre su quale tty siete e metterla ad accesso libero. Fatto ciò sloebel certamente funzionerà


Sull'ide arduino questo codice non è stato provato, ma anche funzionasse non conviene usarlo essendo molto meno potente

## Lavori da miglorare
Attualmente il codice gestisce molto bene:
- Encoder
- Correnti
- Controllo motori (Tramite la classe)
- SPI

Risulta tuttavia necessario miglorare:
- Raggiungimento della home:
    Il codice per ora riesce ad ottenere una buona home per i giunti del braccio e della pinsa, ma a causa di dei falsi contatti o altro sulla base il raggiungimento della home non avviene sempre, è necessario mettersi a osservare per bene cosa succede e rendere più robusto il codice che cerca la home
- Limitazione dei motori:
    Ad ora l'unico controllo che viene fatto dalla scheda è se la corrente media supera quello di limite, si vorrebbe limitare anche gli encoder minimi e gli encoder massimi facendo ignorare all'arduino i pwm che portano a superare queste posizioni di sicurezza. Per farlo è necessario modificare la classe che gestisce i motori aggiungendo un parametro che dice se il motore per pwm POSITIVI fa anche crescere gli encoder o meno. Saputo ciò si puo far si che la classe ignori i sensi di marcia che portano a far crescere il numero degli encoder una volta che si è superato la soglia massima.
    La sogli è possibile vederla dalle impostazioni della boar, e la segnalazione che è stato superato il limite può avvenire dalla funzione "sanityCheck", che ad ora controlla ogno x millisecondi la sola corrente, con questa aggiunta si potrà superare questo limite.

