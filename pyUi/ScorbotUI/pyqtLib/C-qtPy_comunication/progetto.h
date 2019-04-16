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

struct uten* inserisci_u(struct uten *testa,struct uten *mes);

struct uten* libera_m(struct uten *nodo);

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