# Scorbot-CA relase 0.1
Questa prima versione del codice unisce tutti i sotto sistemi sviluppati separatamente cercando di farli cooperare.

Sono presenti dei chiari limiti e problemi che per motivi temporali non sono stati risolti in tempo.

Risulta necessario riproggettare:
- Il metodo di invio dei riferimenti al controllore:
    Anche se la pipe riesce a leggere come si deve i dati dell'interfaccia grafica, il metodo rapido di darli in pasto al controllore ha dei chiari problemi, riproggettare il tutto con un array in mezzo che disaccoppi e contolli i parametri è auspicabile
- Il controllo necessita di essere sviluppato molto meglio.
    In primis è necessario di fermare i motori una volta raggiunta una posizione sufficentemente buona, tenere conto del movimento degli altri motori ecc..
    La taratura delle deadzone sembra essere buona
