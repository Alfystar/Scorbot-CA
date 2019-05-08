La libreria sviluppata qui è scritta in c++ ed è pensata per essere eseguita sull'arduino MEGA.

è stata sviluppata usando come editor Sloebel, un tool open gratuito che si basa su di eclipse, è stato proggettato per essere compatibile con le schede arduino presenti in commercio, se caricate questo progetto con sloebel sicuramente lo riuscirà a leggere e successivamente a caricare sulla scheda.

Se siete su windows oltre la come e poche altri dettagli siete ready to go.

Su linux prima di caricare il codice dovete andare in :
/dev/

Trovare la ttyAMC* che ha montato ora il vostro arduino, quindi con
chmod o+rwx ttyAMC* 
per cambiare i diritti di accesso e mettere oltre il root, anche gli altri utenti.

in generale i comandi da eseguire che funzionano sempre sono:

cd /dev/
ls -l ttyAMC*
sudo chmod o+rwx ttyAMC* 

Con questi comandi sarete in grado di sapre su quale tty siete e metterla ad accesso libero. Fatto ciò sloebel certamente funzionerà


Sull'ide arduino questo codice non è stato provato, ma anche funzionasse non conviene usarlo essendo molto meno potente

