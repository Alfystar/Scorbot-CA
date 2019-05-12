# Scorbot-CA relase 0.1
Questa prima versione del codice unisce tutti i sotto sistemi sviluppati separatamente cercando di farli cooperare.

Sono presenti dei chiari limiti e problemi che per motivi temporali non sono stati risolti in tempo.

Risulta necessario riproggettare:
- Il metodo di invio dei riferimenti al controllore:
    Anche se la pipe riesce a leggere come si deve i dati dell'interfaccia grafica, il metodo rapido di darli in pasto al controllore ha dei chiari problemi, riproggettare il tutto con un array in mezzo che disaccoppi e contolli i parametri è auspicabile
- Il controllo necessita di essere sviluppato molto meglio.
    In primis è necessario di fermare i motori una volta raggiunta una posizione sufficentemente buona, tenere conto del movimento degli altri motori ecc..
    La taratura delle deadzone sembra essere buona


###  Interfaccia grafica

Le caratteristiche da migliorare sono:
- Inserire grafici matlab nelle prime tre schermate
- Studio dei punti ammissibili nello spazio per lo scorbot
- inserimento dei valori corretti quando aggiorno la home falsa(quando aggiorno la home i valori delle varie label o spinbox rimangono settati con i valori corrispondenti alla home settata precedentemente e non rispetto a quella nuova appena settata)
- aggiungere eventuali semafori per la scrittura sulle Qlabel
- aggiungere piu' cifre decimali ai parametri di conversione encoder-angoli(alfa,beta,gamma,delta)


###  Comunicazione Raspberry-Python

Le caratteristiche da migliorare sono:
- C (funzione invia):
    - rendere automatica la creazione del messaggio(un ciclo for con sprintf piuttosto un %d statico per ogni encoder/corrente o impostazione)
    - se fallisce l' invio per Python comunicare a quest' ultimo che l' invio e' fallito(se al posto di ritornare -1 si chiudesse l' applicazione il problema sarebbe risolto a condizione di gestione dei segnali(**))
- (**)chiudere C se si chiude python e viceversa (gestione dei segnali e usando kill sapendo il nome del processo)
