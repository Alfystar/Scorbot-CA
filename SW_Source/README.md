# Scorbot-CA (Controlli Automatici)
In questa direcotry è sono contenuti i sorgenti:
- Gui linux
- Firmware Scorboard_V2 (UART version)
- Common-src (librerie comuni alle 2, reso compatibile mediante #ifdef)

## Gui linux
Scritta usando la liberia QT in c++.
La guida alla sua compilazione ed esecuzione (e possibile aggiunta di una nuova finestra) è reperibile [qui](0_Guide/UI_Compiling_Guide.md)

Dentro [uartSubSystem](Scorbot-V2_UI/uartSubSystem/uartSubSystem_demo) è presente una piccola demo che mette in esercizio tutto il sotto sistema di smistamento dei pacchetti.

## Firmware Scorboard_V2
Firmware, basato sulle librerie Arduino, ma usando l'editor SLOEBER
La guida è reperibile [qui](0_Guide/SloeberInstall.md)

## Common-src
Librerie comuni alle 2 (in particolare la libreria SERIALE e i Tipi comuni)
Si è optato per questa struttura per garantire la binary coherency dei 2 compilati

Dentro [uartDriver](Common-src/uartDriver/pcListen_demo) è presente una piccola demo che ascolta la seriale e printa i pacchetti ricevuti.

## Controll Scritp
Per scrivere lo script di controllo del robot, visionare [questa guida](0_Guide/WriteControllScript.md)
