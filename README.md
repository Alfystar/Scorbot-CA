![](https://img.shields.io/github/stars/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/forks/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/tag/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/release/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/issues/Alfystar/Scorbot-CA) ![](https://img.shields.io/bower/v/editor.md.svg)

------------

# Scorbot-CA (Controlli Automatici)
Progetto inizialmente portato avanti nell'ambito del corso di Controlli Automatici tenuto a Tor-Vergata nell'anno 2019
- Sviluppato da studenti del 3° Ing. Informatica
- Corso tenuto dal Professor: Daniele Carnevale

I componenti del gruppo originario erano:
- Emanuele Alfano
- Davide Antonini
- Del Papa Nicolò
- Francesco Ferrò
- Ilaria Angeloni
- Alberto Menichelli


Il progetto è attualmente portato avanti da Emanuele Alfano con la licenza [GPLv3](https://github.com/Alfystar/Scorbot-CA/blob/master/LICENSE "GPLv3")
<p align="center">
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/license.png?raw=true">
  <br>  
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/Slide%20show%20develop/Presentazione%20Scorbot%20low%20level/Hardware/Frontale%20sistema.png?raw=true">
</p>

## Installation Guide

Per poter scaricare e installare con successo il programma, bisogna prima di tutto possedere un sistema linux, lo sviluppo fatto fino ad ora è debian/ubunto base, ma le system call usate dovrebbero essere comuni a qualsiasi distribuzione linux.
Per prima cosa sarà necessario installare i seguenti paccheti (qui con sintassi apt, da derivare in caso in base alla distribuzione in uso):
    
    sudo apt install qt5-d* qtbase5-dev qtdeclarative5-dev qttools5-dev-tools

Per poter sia avere le librerie grafiche qt, che gli strumenti di sviluppo se si desiderasse potenziare il progetto.
A questo punto, compiliamo i sorgenti e installiamoli dentro /usr/local/bin
    
    cd unionExe
    cmake
    sudo make install
    
Arrivati a questo punto, dal terminale sarà possibile digitare 
    
    ScorbotTerminal

e si avvierà l'interfaccia grafica di controllo della scheda dello scorbot (sviluppata sempre in questo progetto e presente nel repository, vedi sotto)
    
### Develope setup

#### File System Structure
Se invece si volesse continuare lo sviluppo del progetto è necessario sapere qualche dettaglio:
Tenendo presente la struttura del progetto:

    .
    ├── 0__oldProject
    ├── 1_Doc
    │   ├── Datascheet
    │   ├── General Documentation
    │   ├── Manuale di avvio dello Scorbot per la MakerFaire.docx
    │   ├── Manuale di avvio dello Scorbot per la MakerFaire.pdf
    │   ├── Media
    │   ├── ProjectPresentation-V1.pdf
    │   ├── ProjectPresentation-V1.pptx
    │   ├── ScorBoard UML Diagrams
    │   ├── ScorBoard_v2-MANUAL.docx
    │   ├── ScorBoard_v2-MANUAL.pdf
    │   ├── ScorBoardV2.png
    │   └── Slide show develop
    ├── 2_controllStudio
    ├── HW_Source
    │   ├── Eagle-LibScorbot
    │   ├── part-list.txt
    │   └── ScoreBoard-V2
    ├── license.png
    ├── LICENSE.txt
    ├── README.md
    ├── SourceCode
    │   ├── 1_uartBoardLinux
    │   ├── 2_uiSource
    │   └── 3_controllSource
    └── unionExe
        └── Scorbot-V2

Abbiamo che in:
    
    .
    ├── SourceCode
    │   ├── 1_uartBoardLinux
    │   ├── 2_uiSource
    │   └── 3_controllSource
    └── unionExe
        └── Scorbot-V2

si concentrano tutti i sorgenti dei programmi, sia firmware della scheda che controllore PID, che interfaccia grafica.

##### Linking file

Durante lo sviluppo è stata seguita una linea di sviluppo test-driven, e si è andato avanti costruendo sui successi precedenti.
Per evitare di copiare innumerevoli volte i file, oltre che rischiare di avere file aggiornati a  a versioni differenti, si è pensato di creare dei collegamenti simbolici a cartelle di interesse dentro la propria cartella (questo perchè cmake supporta l'aggiunta di sole SOTTO-cartelle).
Un esempio importante è visibile dentro "1_uartBoardLinux":

    .
    ├── Common-src                 //File comuni
    ├── linuxSide_root               //Sorgenti driver di comunicazione seriale LINUX
    └── ScoreBoard_Uart         //Sorgenti Firmware della scheda

Sia  "linuxSide_root" "ScoreBoard_Uart" al loro interno possiedono dei collegamenti ai file presenti dentro "Common-src", questo fa sì che le modifiche fatte per necessità (aggiunta di un nuovo tipo di pacchetto, creazione di una classe, typedef di un dato, ecc...) vengano fatti dentro un unico file che venendo incluso da entrambi mantiene sempre la compatibilità 1:1.

Lì dove fosse necessario differenziare i codici per l'uno o per l'altro sono state usate le macro
	#define ScorboarFirmware
	#define linuxSide
Aggiunta dentro Sloebel per la compilazione del Firmware, e all'interno dei CMakeList.txt interessati per la compilazione su linux.

Seguendo questa Filosofia viene da se che la cartella unionExe, contiene l'eseguibile con l'interfaccia grafica e tanti link ai sorgenti.
Ne segue che se si volesse rinominare una cartella, sarà successivamente neccessario ricreare i collegamenti che si andranno a perdere, idem se la si dovesse spostare

#### Editor utilizzati
Per tutte le parti del codice, dopo un primo approccio con python, si è passati all'uso pesante e totale di C/C++ sia per l'arduino che per il programma linux, si sono utilizzate varie librerie e vari pacchetti, che in teoria dovrebbero essere presenti nella maggior parte delle distribuzioni Linux.

##### Linux
Per la parte linux, si è usato come editor CLion, e conseguentemente come tool per tenere traccia del codice, cmake
In caso si volesse usare un altro editor, si consiglia l'uso di uni che supporti i cmake.
##### Firmware
Per il firmware invece, al posto della classica interfaccia di arduino, si è usato come IDE Sloeber, IDE opensource, basato su eclipse, e già compatibile con molte schede Arduino.

#### Documentazione
Per la documentazione, anche se non è stata completata in dettaglio, ma sono presenti i legami fondamentali, è stata usata la versione Comunity di Visual Paradigm.
Le classi non vengono documentate nel dettaglio, ma sono presenti le idee di interconnessione, i pattern utilizzati e la gerarchia delle classi. Per i dettagli implementativi il codice

#### Creazione di un controllo
In un ottica di controllista, si vorrebbe migliorare/sviluppare dei sistemi di controllo superiori al PID implementato sulle schede, per poterlo attuare ecco dove andare a guardare:
##### Demo da terminale
Il file:

	SourceCode/3_controllSource/2_pidCtrl/main.cpp

contiene un demo-main per il controllore PID, che fissati i riferimenti, usa una classe PID sviluppata dal lavoro visto in classe di Controlli Automatici, e che leggendo il feedback calcola l'output e lo invia.
Il sistema a contorno viene già impostato in questo main, e da questo come base, si può benissimo sviluppare un applicativo da terminale per il controllo dello scorbot.

##### Demo interfaccia grafica
Il medesimo tipo di controllo è presente nel sistema con interfaccia grafica dentro il file:

	unionExe/Scorbot-V2/scorbotMainWindows/UI_useCase/MotorCTRL.cpp (in particolare alla riga 134)
	
Come nel caso precedente, tutto il resto del sistema viene già impostato, e anzi qui è anche già presente un sistema di immissione dei parametri che è da interfaccia grafica, oltre che la possibilità di stoppare il controllo e attivare la modalità free-move, per portare il robot in posizioni particolari.
Il vantaggio nell'usare l'interfaccia grafica, sta che si può interrompere il conrollo quando si va in freeMove, e il poter leggere graficamente i parametri di ritorno.
Resta in oltre possibile, a patto di studiare come si crea un interfaccia grafica in QT5, la possibilità di generare una nuova Form grafica per il Tuning del controllo usato, il tutto usano il software "qt Designer" e assegnando come si deve segnali, slot e metodi, è così possibile modificare in real-time i parametri del controllore

### Creazione di nuove finestre

Per creare Nuove fineste grafiche la procedura è la seguente:
1. Disegnare con QT Designer la grafica (in quelle sviluppate fino ad ora si è forzato lo stile "fusion" da dentro il codice applicativo)
2. Salvare il file dentro:

    SourceCode/2_uiSource/ScorbotUI_cpp/src/scorbotUi/ui_source

3. Generare una classe di controllo col medesimo nome, che la generalizzi e che includa il nameSpace di questa nuova classe.
(In QT, i file *.ui*, vengono convertiti in tempo di compilazione in classi, e le classi che le controllano altro non sono che classi figlie generalizzate che quindi possiedono tutti gli attributi grafici del padre, e aggiungono i segnali e gli eventi, e in caso di modifiche o aggiunte nel padre, continuano tranquillamente a funzionare)
4. Creare dentro

	unionExe/Scorbot-V2/scorbotMainWindows/UI_useCase
	
La classe che implementa gli UseCase desiderati se necessitano di conoscenze di altri sotto sistemi, altrimenti implementare lo useCase nella classe generata al punto 3.

Cercando di rispettare questa logica nell'aggiunta delle classi, è possibile mantenere una struttura e far si che ai livelli altri vi sia solo il codice necessario a far interagire sistemi diversi, mentre se un sistema è già in grado di svolgere tutto da solo , non pesa sugli altri che vedono la sua funzionalità in maniera trasparente.

## ScoreBoard
La scheda di controllo dello Scorbot è pensata per essere un ponte tra la meccanica del robot, e il sistema di controllo integrato all'interno di un computer Linux.
[![SubSystem-structure](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/Media/ScorBoard-idea.png?raw=true "SubSystem-structure")](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard_v2-MANUAL.pdf "SubSystem-structure")

Il manuale di questo sotto sistema è trovabile [qui](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard_v2-MANUAL.pdf "qui").

### Eagle Board
There are 2 version of the board.
Each one have his firmware and his library.
They are drawing using EAGLE 9.4.2 Educetional.
View this project on [CADLAB.io](https://cadlab.io/project/1649). 
#####  Board V1:
In questa prima versione si sono utilizzati dei ponti H L298, e per leggere gli ACS712.
La scheda soffriva di vari problemi di connessioni tra i pin in fase di progetto, le quali sono tutte risolvibili a mano.
La scheda possiede un firmware di controllo che parla al Rapsberry Py per mezzo di una comunicazione SPI. Di questa prima vesione è stata scritta una [presentazione del progetto](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ProjectPresentation-V1.pdf) ai fini dell'esame.

#####  Board V2:
In questa seconda scheda il cambio più evidente è nel driver motori che adesso è diventato un VNH5019, il quale ha integrato dentro una misura di corrente già scalata e non necessita di letture esterne, di questa scheda è presente anche un [**Manuale**](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard_v2-MANUAL.pdf "qui")., che descrive nel dettaglio i vari punti del progetto.
<p align="center">
  <i>Top Face</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/HW_Source/ScoreBoard-V2/GerberFile/ScoreBoard-V2_top.png?raw=true"> 
  <br>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/HW_Source/ScoreBoard-V2/GerberFile/ScoreBoard-V2_bot.png?raw=true"> 
  <i>Bottom Face</i>
</p>


#### UART Comunication Arduino <--> Linux:
La scheda comunica con un computer mediante collegamento UART, qui è stata sviluppata una libreria per la comunicazione con un processo Linux (testata su Mint e KDE NEON, in generale ubunto based)

# QT Gui
Per controllare il Robot in maniera intuitiva si è pensato di usare un interfaccia grafica scritta in QT5, la quale permette di controllare il robot sia direttamente che per mezzo di un PID
<p align="center">
  <i>Main Window</i>
    <br>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/Media/ScorInterface%20main.png?raw=true"> 
  <br>
    <i>Uart Select</i>
	  <br>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/Media/ScorInterface%20uartSelect.png?raw=true"> 
    <br>
    <i>Setting Board Window</i>
	  <br>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/Media/ScorInterface%20settings.png?raw=true"> 
    <br>
    <i>Free Move Window</i>
	  <br>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/Media/ScorInterface%20freeMove.png?raw=true"> 

</p>

Per graficare i dati ricevuti è stata usata la libreria [qcustomplot](https://www.qcustomplot.com/index.php/introduction)

# Controllability Study
Lo studio è stato svolto per mezzi teorici, con un modello ottenuto dal professore, con l'intento di trovare i prametri da applicare a un PID.