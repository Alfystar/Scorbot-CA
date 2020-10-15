# Linux Gui Compiling
Il codice è stato scritto usando come ide CLion della Jetbrains, in C++, per poter funzionare l'ide necessita dell'uso del Cmake, Il progetto possiede quindi tutto il necessario per funzionare subito con Cmake, è tuttavia possibile compilare da terminale tutto ed eseguirlo sulla macchina prescelta.

L'interfaccia grafica del progetto è stata realizzata in QT5.

## Tool necessari
Per compilare il sistema è necessari installare le seguenti pacchetti dal repository Linux della propria distro:

```
sudo apt install cmake make g++ build-essential git     # Base Programs
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

## UI Lenta
Sul rapsberry pi o altri computer particolarmente modesti, il graficare il grafico può
avere l'effetto di freezzare il sistema. In tal caso la soluzione è non graficare le correnti...
Triste ma giusto, per realizzare ciò da dentro la cartella `build`:
```
cmake .. -DPLOT_ENABLE=False
sudo make install -j 8   #for 8 thread, more if your system have more core
Scorbot-V2_UI		     # Ora presente dentro /usr/local/bin =>accessibile tramite path
```
