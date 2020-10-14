# Sloeber Install
Sloeber è un ide di sviluppo per le schede Arduino basato su Eclipse e scritto in Java.
Ergo, è nativamente compatibile con i vari sistemi operativi.
Cambia però il modo in cui si interfaccia con il SO per usare la seriale e comunicare con la scheda.

## !! QUESTA GUIDA è pensata per essere in Linux !!

## IDE Installing
Per installare l'ide bisogna andare a scaricare l'ultima versione dal sito:
http://eclipse.baeyens.it/stable.php?OS=Linux

Pre requisito è avere sulla propria macchina una macchina virtuale linux:
```
sudo apt install default-jdk default-jdk-doc                #java for sloebel
```

Una volta scaricato lo zip, estrarlo nella direcory che più vi piace ed eseguite l'eseguibile `sloeber-ide`.
Dopo il tempo di setup e download delle librerie, andate su:
Arduino -> Preferenze
E badate bene di aggiungere questa spunta:
<p align="center">
  <img src="SloeberInstallImg/Arduino-Board.png?raw=true">
</p>

Dopo avvenuto il download impostate la corretta scheda del progetto andando sulla cartella del progetto aperto, fare `Alt+Invio` o Destro -> Properties e andare:
<p align="center">
  <img src="SloeberInstallImg/SettingBoard.png?raw=true">
</p>
Dare l'Apply e provare a compilare cliccano sulla spunta blu (la freccia uploda)
Se il programma compila senza problemi è finita l'installazione di sloeber e siete pronti a partire

## Linux Add-on need
Provate a compilare il progetto, se non avrete errori tutto ok, altrimenti potreste aver bisogno di installare a parte la libreria avr sul sistema:

Per installare la suite di tool necessari alla compilazione e upload del compilato è necessario scaricare dal repository le seguenti librerie della avr (il chip dell'arduino)
```
sudo apt install gcc-avr binutils-avr avr-libc gdb-avr avrdude      #avr compiler for arduino
```
Dipendentemente dall'installazione e dal sistema operativo, potrebbe essere necessario andare sulle proprietà del compilato e modificare le variabili di env affinchè vada a cercare i comandi al path giusto.


Andando sulla cartella del progetto aperto, fare `Alt+Invio` o Destro -> Properties e andare:
<p align="center">
  <img src="SloeberInstallImg/Enviroment.png?raw=true">
</p>
E provate a trovare nel vostro caso la variabile che necessita di essere cambiata (spero non vi capiti)

## Serial Setup
Essendo Linux un sistema sicuro, l'accesso alle periferiche esterne (viste come "file" dentro /dev/) è permesso al root e a certi utenti in particolare.
Noi siamo interessati ad accedere alle tty*, che sono proprietà dell'utente/gruppo `dialout`.
Per permettere a sloeber e al programma GUI, di accedere alla seriale senza eseguire come root le strade percorribili sono 2:
1. Aggiungere il proprio utente al gruppo `dialout` (CONSIGLIATA)
2. Ogni volta modificare il proprietario della seriale

####  Aggiungere il proprio utente al gruppo `dialout`

Per aggiungersi con il proprio user al gruppo "dialout" da terminale:
```
    sudo usermod -a -G dialout <UserName>  # <UserName> utente attuale 
```
Per scoprire il proprio utente si puù usare da terminale `whoiam` o `id`

Quindi riavviare la macchina e il risultato sarà permanente.

#### Cambiare i diritti di accesso della Seriale
Per poter prendere possesso della seriale bisogna aggiungere la possibilità agli "other" di leggere scrivere ed eseguire sul file che rappresenta l'Arduino
Per iniziare bisogna trovare la ttyAMC* (o ttyUSB* o ecc.. dipende dal chip usato sull'arduino per gestire la seriale) che il SO ha assegnato all'Arduino:
```
cd /dev/
ls -l ttyAMC*
```
Riconosciuta quella giusta (probabilmente l'unica) è arrivato il momento di cambiare i diritti di accesso aggiungendo la possibilità di leggere, scrivere ed eseguire agli altri utenti. 
!!Attenzione che l'operazione andrà ripetuta ogni volta che si collega l'arduino!!

I comandi da eseguire che funzionano sempre sono:
```
cd /dev/
ls -l ttyAMC*
sudo chmod o+rwx ttyAMC* 
```
