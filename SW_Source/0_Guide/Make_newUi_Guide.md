# Develop new Windows

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
