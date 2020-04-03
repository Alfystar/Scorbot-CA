![](https://img.shields.io/github/stars/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/forks/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/tag/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/release/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/issues/Alfystar/Scorbot-CA) ![](https://img.shields.io/bower/v/editor.md.svg)

------------

# Common_src Arduino uart <--> Linux uart

Sono qui presenti 

    .
    ├── circularBuffer              // Libreria template per il buffer circolare dei pacchetti
    ├── DataTransfertPackge         // typeDef dei pacchetti scambiabili tra i sistemi
    ├── timeOp                      // Raccolta di macro per gestire comodamente il tempo in Linux
    ├── uartDriver                  // Classi sia per linux che per arduino che realizzano la cominicazione tra le schede
    ├── CMakeLists.txt
    └── README.md

## uartDriver
Vale la pena approfondire la cartella "uartDriver":
Essa al suo interno contiene l'implementazioni delle classi che realizzano il "Transport Layer" di questa applicazione:
il diagramma UML di questa classe spiega meglio come si compongono:

<p align="center">
  <i>uartDrive</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard%20UML%20Diagrams/diagrams/SerialDrives%20Class%20Diagram.png?raw=true"> 
</p>

Le 2 classi gestiscono solo i tipi "uart2Ard" e "uart2Linux".
Questi pacchetti sono approfonditi nel sotto sistema DataTransfertPackge:

<p align="center">
  <i>DataTransfertPackge</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard%20UML%20Diagrams/diagrams/Data-structures%20Class%20Diagram.png?raw=true"> 
</p>

Essendo delle union si potrebbe pensare che si inviino molti più byte del necessario, in realtà, sapendo il tipo, si inviano il numero di byte esatto per ogni pacchetto, e il ricevente sapendo il tipo dal primo campo, è in grado di leggere quanto basta.

Allo stato attuale un limite della libreria è che se si accorge che un pacchetto è arrivato male, attende direttamente l'inizio di una nuova trasmissione invece di cercare nel passato se era già arrivato uno "StartCode".
Ad ora un simile schema si è rivelato ampiamente più che sufficiente per i casi in esame, ma nulla vieta in futuro di migliorare il protocollo.