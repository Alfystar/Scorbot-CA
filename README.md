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


Il progetto è attualmente portato avanti da Emanuele Alfano con la licenza [GPLv3](LICENSE "GPLv3")
<p align="center">
  <img src="license.png?raw=true">
  <br>  
  <img src="1_Doc/Slide%20show%20develop/Presentazione%20Scorbot%20low%20level/Hardware/Frontale%20sistema.png?raw=true">
</p>

## Download/Cloning Repository
Per poter avere i sorgenti sul proprio computer, basterà usare git da terminale per clonare il Repository sulla propria macchina: 
A questo punto, compiliamo i sorgenti e installiamoli dentro /usr/local/bin
```
sudo apt install git    # Per poter scaricare i sorgenti
cd ~/Documents          # Directory di salvataggio dei sorgenti
git clone https://github.com/Alfystar/Scorbot-CA.git
```
Per vedere i sorgenti e relative guide di Compilazione andare [Qui](SW_Source/README.md)
    

## Documentazione
Per la realizzazione della documentazione del software si è usata la versione Comunity di Visual Paradigm.
Le classi non sono state documentate tutte al massimo dettaglio, mettendo invece enfasi sull'interconnessione, i pattern e la gerarchia delle classi presente.
er i dettagli implementativi il codice


## ScoreBoard
La scheda di controllo dello Scorbot è pensata per essere un ponte tra la meccanica del robot, e il sistema di controllo integrato all'interno di un computer Linux.
[![SubSystem-structure](1_Doc/Media/ScorBoard-idea.png?raw=true "SubSystem-structure")](1_Doc/ScorBoard_v2-MANUAL.pdf "SubSystem-structure")

Il manuale di questo sotto sistema è trovabile [qui](1_Doc/ScorBoard_v2-MANUAL.pdf "qui").

### Eagle Board
There are 2 version of the board.
Each one have his firmware and his library.
They are drawing using EAGLE 9.4.2 Educetional.
View this project on [CADLAB.io](https://cadlab.io/project/1649). 

#####  Board V1:
In questa prima versione si sono utilizzati dei ponti H L298, e per leggere gli ACS712.
La scheda soffriva di vari problemi di connessioni tra i pin in fase di progetto, le quali sono tutte risolvibili a mano.
La scheda possiede un firmware di controllo che parla al Rapsberry Py per mezzo di una comunicazione SPI. Di questa prima vesione è stata scritta una [presentazione del progetto](1_Doc/ProjectPresentation-V1.pdf) ai fini dell'esame.

#####  Board V2:
In questa seconda scheda il cambio più evidente è nel driver motori che adesso è diventato un VNH5019, il quale ha integrato dentro una misura di corrente già scalata e non necessita di letture esterne, di questa scheda è presente anche un [**Manuale**](1_Doc/ScorBoard_v2-MANUAL.pdf "qui")., che descrive nel dettaglio i vari punti del progetto.
<p align="center">
  <i>Top Face</i>
  <img src="HW_Source/ScoreBoard-V2/GerberFile/ScoreBoard-V2_top.png?raw=true"> 
  <br>
  <img src="HW_Source/ScoreBoard-V2/GerberFile/ScoreBoard-V2_bot.png?raw=true"> 
  <i>Bottom Face</i>
</p>


#### UART Comunication Arduino <--> Linux:
La scheda comunica con un computer mediante collegamento UART, qui è stata sviluppata una libreria per la comunicazione con un processo Linux (testata su Mint e KDE NEON, in generale ubunto based)

# QT Gui
Per controllare il Robot in maniera intuitiva si è pensato di usare un interfaccia grafica scritta in QT5, la quale permette di controllare il robot sia direttamente che per mezzo di un PID
<p align="center">
  <i>Main Window</i>
    <br>
  <img src="1_Doc/Media/ScorInterface%20main.png?raw=true"> 
  <br>
    <i>Uart Select</i>
	  <br>
  <img src="1_/Doc/Media/ScorInterface%20uartSelect.png?raw=true"> 
    <br>
    <i>Setting Board Window</i>
	  <br>
  <img src="1_Doc/Media/ScorInterface%20settings.png?raw=true"> 
    <br>
    <i>Free Move Window</i>
	  <br>
  <img src="1_Doc/Media/ScorInterface%20freeMove.png?raw=true"> 

</p>

Per graficare i dati ricevuti è stata usata la libreria [qcustomplot](https://www.qcustomplot.com/index.php/introduction)

