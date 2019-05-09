# Eagle File directory

la prima versione (1_scorBoardV1) possiede i seguenti errori:
- Il transistor di abilitazione elettrico del relè per i motori, attualmente è cortocircuitato poichè non funzionava.
La probabile causa di questo problema è che il carico è messo a emettitoere e non a colettore, rendendo il circuito adatto a un PNP e non a un NPN(che è stato progettato e comprato), in una versione successiva è necessario invertire il carico (la bobbina) con il relè.

- La piedinatura usata nell'alimentatore è errata rispetto a quella effettivamente presente, oltre ad alcuni errori che mi avevano fatto connettere 12V a 3.3V, sembra che non sia sufficente prendere la corrente da uno solo per volta di questi fili.
In una prossima versione andrebbero collegati tutti tra di loro già nella board, collegare bene i pin sbagliati e aggiungere un led di segnalazione sul filo dei 5V sempre presenti, poichè l'alimentatore anche se ha il cavo di enable(quello verde) cortocircuitato a massa, se non è assorbito un minimo di corrente cmq non si accende.
In generare riprogettare questo connettore vendendo gli infiniti schemi online e vedendo anche i fili saldati attualmente, che hanno corretto l'errore, quindi devono essere riportati sulla scheda.

- In questa scheda i 3.3V che dovevano andare al rapsberry sono stati tagliati, perchè all'inizio causavano il reset della board. Si è scoperto poi che i 3.3V erano quasi a 0 poichè cortocircuitati con 12V (evidentemente l'alimentatote andava in protezione), nella scheda successiva si può provare a collegarli quindi.

- Il Vref esterno a meno che non si prenda da meno di 1.1V è meglio levarlo potendo usare quello stabilizzato interno all'arduino

- Il connettore del Rapsberry è necessario ruotarlo di 180°, per permettere una comoda connessione con lo stesso, ovviamente così facendo bisogna rifare la strip ruotando uno dei 2 estremi, in generale controllare prima di collegare che i pin siano connessi bene

- Sempre al connettore collegare tutte le masse, i 5V e i 3.3V, così da massimizzare la potenza trasmessa

- Se si continua ad usare l'attuale relè, è necessario correggere il package della libreria da me scritta che così comè si monta all'indietro rispetto al desiderato.

- Sulla serigrafia aggiungere i sensori di corrente a quale motore fanno riferimento, per futuri debugging ad occhio

- Facilitate bypass del traslatore di livello, per leggere o annullarne la presenza (mettere una fila di pin uno per pin), e in generale spostarlo o dal lato accessibile o fuori

- Modificare la serigrafia per mettere dritto e più leggibile i loghi

Grazie per l'attenzione
