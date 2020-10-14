# Script di Controllo
Tutto il sistema realizzato è da prendere come una black-box che gestisce i pacchetti e il sistema operativo, al controllista basterà andare a modificare solo i file:
- Scorbot-V2_UI/ctrlSrc/ctrlSource.cpp
- Scorbot-V2_UI/ctrlSrc/ctrlSource.h

Nella cartella che li contiene si può modificare tutto ECCETTO:
1. Il nome di questi due file (inclusi dal resto del codice)
2. Le 2 funzioni di base presenti:
    1. `void setup (ScorInterface *scorInterface)`
    2. `SpeedMot &loop (EncoderMot *refPid, EncoderMot *enFeed)`

Queste 2 Funzioni sono le 2 chiamate dal sistema.
Ovviamente il loro interno puù essere cambiato a piacere, ma soprattutto il loop, deve ritornare alla fine un pacchetto di tipo `SpeedMot`, il quale verrà copiato dal sistema e non più toccato.

## Setup

La funzione del setup viene chiamata all'inizio della vita del processo, e viene passato il riferimento all'oggetto che gestisce la seriale, è quindi possibile inviare tutti i comandi che si vuole e le impostazioni alla scheda nel setup, creare tutte le proprie variabili e cc..

Il setup non verrà mai più chiamato per tutta la vita del processo.

## Loop
Quando l'interfaccia grafica viene cliccato Free-move, Go-home, o Stop, il sistema non chiamerà il loop, poichè il controllo è dato all'operatore.
 
Il loop è abilitato se si è in modalità Controllo (cliccanto su "Send Reference").
La funzione è chiamata all'arrivo di un nuovo pacchetto (è possibile controllare il tempo di campionamento, e quindi controllo impostando la scheda nel setup).
Il sistema smette di chiamare chiamare il loop appena si ritorna a una modalità utente, ma appena verrà inserito un nuovo riferimento, il loop ricomincerà ad essere chiamato con il nuovo riferimento.

IL LOOP DEVE ESSERE IL PIÙ RAPIDO POSSIBILE E NON AVERE AL SUO INTERNO ALCUN RALLENTAMENTO

### I riferimenti
Per permettere la presenza di SW-Home, al controllo sono passati direttamente gli encoder Obiettivo, che sono il risultato della formula:
```
enObj = enRef + Offset`
```
Dove `Offset` è ottenuto nel 4° tab della interfaccia grafica e permette di impostare la posizione corrente o una posizione a piacere, la modifica ha effetto al SUCCESSIVO invio di riferimento (gli enRef non vengono riportati a 0).
    
