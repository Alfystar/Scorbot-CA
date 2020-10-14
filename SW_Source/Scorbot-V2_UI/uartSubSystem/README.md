![](https://img.shields.io/github/stars/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/forks/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/tag/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/release/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/issues/Alfystar/Scorbot-CA) ![](https://img.shields.io/bower/v/editor.md.svg)

------------

# UartSubSystem for Linux

Sono qui presenti 

    .
    ├── AdapterClasses
    │   ├── ComUartAdapter.cpp
    │   ├── ComUartAdapter.h
    │   ├── ObservableScorbot.h
    │   └── ObserverScorbot.h
    ├── CMakeLists.txt
    ├── ConcreteObserver.cpp
    ├── ConcreteObserver.h
    ├── ScorInterface.h
    ├── UartSubSystem.h
    └── README.md


Il sotto sistema è descitto dal grafico UML:
<p align="center">
  <i>uartDrive</i>
  <img src="https://github.com/Alfystar/Scorbot-CA/blob/master/1_Doc/ScorBoard%20UML%20Diagrams/diagrams/Linux-Comunication%20Class%20Diagram.png?raw=true"> 
</p>

Gli utilizzatori di questo sotto sistema necessitano di istanziare attivamente "ComUartAdapter", ma successivamente gli conviene trattarlo come uno "ScorInterface" per avere una maggiore semplicità.
Se si fosse interessati ad essere notificati dell'arrivo di un nuovo pacchetto, basterà aggiungere la propria "customClass" di tipo "ObserverScorbot".
Viene fornita già funzionante la classe "ConcreteObserver" che aggiunge la funzionalità di leggere in maniera bloccante (e quindi evitando di pesare sul tempo di CPU) i dati appena pronti.