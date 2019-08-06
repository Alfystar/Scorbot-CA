![](https://img.shields.io/github/stars/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/forks/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/tag/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/release/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/issues/Alfystar/Scorbot-CA) ![](https://img.shields.io/bower/v/editor.md.svg)

------------

# Scorbot-CA (Controlli Automatici)
Progetto inizialmente portato avanti nell'ambito del corso di Controlli Automatici tenuto a Tor-Vergata nell'anno 2019
- Sviluppato da studenti del 3° Ing. Informatica
- Corso tenuto dal Professor: Daniele Carnevale

Il progetto è attualmente portato avanti da Emanuele Alfano con la licenza [GPLv3](https://github.com/Alfystar/Scorbot-CA/blob/master/LICENSE "GPLv3")
<p align="center">
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/license.png?raw=true">
  
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/Slide%20show%20develop/Presentazione%20Scorbot%20low%20level/Hardware/Frontale%20sistema.png?raw=true">
</p>

## ScoreBoard
La scheda di controllo dello Scorbot è pensata per essere un ponte tra la meccanica del robot, e il controllo progammato dentro il Rapsberry Py.
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
######  Eagle Draw Developer:
 - Emanuele Alfano

###### Arduino mega Code Developers:
- Emanuele Alfano
- Davide Antonini
- Del Papa Nicolò

###### SPI Serial Comunication Arduino <--> Rapsberry Py Developers:
- Emanuele Alfano
- Davide Antonini
- Del Papa Nicolò

[*ScorBoard-V1 repository*](https://github.com/Alfystar/Scorbot-CA/tree/master/2_boardSystem/V1 "ScorBoard-V1 repository")



#####  Board V2:
In questa seconda scheda il cambio più evidente è nel driver motori che adesso è diventato un VNH5019, il quale ha integrato dentro una misura di corrente già scalata e non necessita di letture esterne, di questa scheda è presente anche un [**Manuale**](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard_v2-MANUAL.pdf "qui")., che descrive nel dettaglio i vari punti del progetto.
######  Eagle Draw Developer:
 - Emanuele Alfano

###### Arduino mega Firmware Developer:
- Emanuele Alfano

###### SPI Serial Comunication Arduino <--> Rapsberry Py Developer:
- Emanuele Alfano

[*ScorBoard-V2 repository*](https://github.com/Alfystar/Scorbot-CA/tree/master/2_boardSystem/V2 "ScorBoard-V2 repository")


# Rapsberry Py Gui controll
Per controllare il Robot in maniera intuitiva si è pensato di usare un interfaccia grafica scritta in python usando la libreria grafica PyQT5, la quale per mezzo di delle pipe parlava con il processo C++ che si occupava del controllo del robot.
Una sintesi di questo lavoro è stata scritta nella [presentazione del progetto](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ProjectPresentation-V1.pdf).
## C++ core Process of Rapsberry Py Developers:
- Francesco Ferrò
- Emanuele Alfano

## Python User Interface Developers:
- Ilaria Angeloni
- Alberto Menichelli
- Emanuele Alfano

# Controllability Study
Lo studio è stato svolto per mezzi teorici, con un modello ottenuto dal professore, con l'intento di applicare un PID.
Una sintesi di questo lavoro è stata scritta nella [presentazione del progetto](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ProjectPresentation-V1.pdf).
## Matlab Math Controll Developers
- Alessandro Cosentini
- Fabio Di Vincenzo
- Emanuele Alfano
