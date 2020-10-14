# Linux Gui Compiling
Il codice è stato scritto usando come ide CLion della Jetbrains, in C++, per poter funzionare l'ide necessita dell'uso del Cmake, Il progetto possiede quindi tutto il necessario per funzionare subito con Cmake, è tuttavia possibile compilare da terminale tutto ed eseguirlo sulla macchina prescelta.

L'interfaccia grafica del progetto è stata realizzata in QT5.

## Tool necessari
Per compilare il sistema è necessari installare le seguenti pacchetti dal repository Linux della propria distro:

```
sudo apt install cmake, make, g++, build-essential, git     # Base Programs
sudo apt install qt5-default qt5-doc qt5-doc-html qtbase5-dev qtdeclarative5-dev qttools5-dev-tools   #qt
```

## Terminal Compiling
A questo punto, da dentro `SW_Source` per compilare i sorgenti ci basterà digitare:
```
mkdir build
cmake -s CMakeLists.txt -B build/ -DCMAKE_BUILD_TYPE=Release
cd build/
sudo make install -j 8   #for 8 thread, more if your system have more core
Scorbot-V2_UI		     # Ora presente dentro /usr/local/bin =>accessibile tramite path
```
Il risultato sarà che avremo installato l'eseguibile della Gui dentro `/usr/local/bin`

Arrivati a questo punto, dal terminale sarà possibile digitare `Scorbot-V2_UI`
E avviare così l'interfaccia grafica di controllo della scheda dello scorbot

### Develop new Windows

Per creare Nuove fineste grafiche la procedura è la seguente:
1. Disegnare con QT Designer la grafica (in quelle sviluppate fino ad ora si è forzato lo stile "fusion" da dentro il codice applicativo)
2. Salvare il file dentro:

`Scorbot-CA_Cleanup/SW_Source/Scorbot-V2_UI/qtScorbotUi/UI_useCase/scorbotUi/ui_source`

3. Generare una classe di controllo col medesimo nome, che la generalizzi e che includa il nameSpace di questa nuova classe.
(In QT, i file *.ui*, vengono convertiti in tempo di compilazione in classi, e le classi che le controllano altro non sono che classi figlie generalizzate che quindi possiedono tutti gli attributi grafici del padre, e aggiungono i segnali e gli eventi, e in caso di modifiche o aggiunte nel padre, continuano tranquillamente a funzionare)
4. Creare dentro

`SW_Source/Scorbot-V2_UI/qtScorbotUi/UI_useCase`

La classe che implementa gli UseCase desiderati se necessitano di conoscenze di altri sotto sistemi, altrimenti implementare lo useCase nella classe generata al punto 3.

Cercando di rispettare questa logica nell'aggiunta delle classi, è possibile mantenere una struttura e far si che ai livelli altri vi sia solo il codice necessario a far interagire sistemi diversi, mentre se un sistema è già in grado di svolgere tutto da solo , non pesa sugli altri che vedono la sua funzionalità in maniera trasparente.
