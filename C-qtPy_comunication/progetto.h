#ifndef PROGETTO_H
#define PROGETTO_H

struct impostazioni{
  int n;  //numero impostazioni
  char *imp1;  
  char *imp2;
}impostazioni;
 
struct messaggio{
  int enc[6];
  int cor[6];
  struct impostazioni *imp;
}messaggio;

struct uten{  //nodo della lista collegata
  struct messaggio *data; 
  struct uten *p;
};

struct uten* inserisci_u(struct uten *testa,struct uten *mes){
  //testa e' l' ultimo nodo della lista, mes il nodo da inserire
  //la funzione aggiorna il puntatore all' ultimo nodo con quello appena inserito
  if(testa==NULL){
    testa=mes;
  }else{
    testa->p=mes;
    testa=mes;
  }
  return testa;
}


struct uten* libera_m(struct uten *nodo){
  //nodo e' il puntatore al nodo da liberare
  //restituisce il puntatore al nuovo nodo della lista (e quindi alla nuova testa)
   struct uten* new;
   new=nodo->p;
   free(nodo->data);
   free(nodo);
   return new;
}

void libera_u(struct uten *testa);

struct uten* libera_m(struct uten *nodo);

void componi_mes(struct messaggio *mes,char* buffer);

int invia(char *mes);

void parsing(struct messaggio* m,char* text, char* p);

void *readerPipe ();

int main_com(char *file_p[]);



//controllore

void invia_cont(struct messaggio* m);

struct messaggio* ricevi_cont();

void invia_rs(struct messaggio *m);

struct messaggio* ricevi_rs();

void libera_semafori();

int inizializza_semafori();



#endif