# Arduino MEGA (atmega2560) Firmware
La libreria sviluppata è scritta in c++ ed è pensata per essere eseguita sull'arduino MEGA della board progettata in "eagle-brd".

MOLTO IMPORTANTE AGGIUNGERE ALLA FINE DEL COMPILATORE GCC IL DEFINE:
	-D ScorboarFirmware
serve per evitare di far includere librerie e codici che devo essere presenti solo nella versione Rapsberry

La documentazione del codice è stata con UML ed è trovabile qui https://github.com/Alfystar/Scorbot-CA/tree/master/1_Doc

Le classi cooperanti al funzionamento del firmware sono:
[![SubSystem-structure](https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/Spi_ScorBoard%20Object.png?raw=true "SubSystem-structure")]("SPI raps-structure")


## Ide di sviluppo
Il codice è stato sviluppato usando come editor Sloebel, un tool open gratuito che si basa su di eclipse, è stato proggettato per essere compatibile con le schede arduino presenti in commercio, se caricate questo progetto con sloebel sicuramente lo riuscirà a leggere e successivamente a caricare sulla scheda.
### Windows user
Se siete su windows oltre la come e poche altri dettagli siete ready to go.

## Lavori da miglorare
Attualmente il codice gestisce molto bene:
- Encoder
- Correnti
- Controllo motori (Tramite la classe)
- UART

I diagrammi che descrivono i sotto sistemi sono:
<p align="center">
  <i>ADC Current reading</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard%20UML%20Diagrams/diagrams/AdcLib.png?raw=true"> 
  <br>
  <i>ADC Free running timing</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard%20UML%20Diagrams/diagrams/ADC%20free-runnig.png?raw=true"> 
  <br>
  <i>Motor Driver</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard%20UML%20Diagrams/diagrams/Motor%20Driver.png?raw=true"> 
  <br>
  <i>Motor Driver State Machine</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard%20UML%20Diagrams/diagrams/Motor%20State%20Machine.png?raw=true"> 
  <br>
  <i>Encoder Reading</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard%20UML%20Diagrams/diagrams/ScoreBot%20Feedback%20Sensor.png?raw=true"> 
  <br>
  <i>System Entity</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard%20UML%20Diagrams/diagrams/ScorBoard%20Object.png?raw=true"> 
</p>


Risulta tuttavia necessario miglorare:
- Raggiungimento della home:
    Il codice per ora riesce ad ottenere una buona home per i giunti del braccio e della pinsa, ma a causa di dei falsi contatti o altro sulla base il raggiungimento della home non avviene sempre, è necessario mettersi a osservare per bene cosa succede e rendere più robusto il codice che cerca la home
    
