#ifndef PROGETTO_H
#define PROGETTO_H
//todo : ridefinire i termini della comunicazione e aggiungere una leggenda
#include <DataPrimitive.h>
using namespace DataPrimitive;


struct impostazioni {
    int n;  //numero impostazioni
    int maxE[nMot];
    int minE[nMot];
    int maxC[nMot];
//massimo e minimo numero encoder(vettore da 6)
//massimo valore corrente(vettore da 6)
};


struct messaggio {
    int enc[6];
    int cor[6];
    //struct impostazioni *imp;
    settingsBoard *imp;
};



struct uten {  //nodo della lista collegata
    struct messaggio *data;
    struct uten *p;
};

struct uten *inserisci_u(struct uten *testa, struct uten *mes);

struct uten *libera_m(struct uten *nodo);

void libera_u(struct uten *testa);

struct uten *libera_m(struct uten *nodo);

int invia(struct messaggio *m, char *tipo);

struct messaggio *parsing(char *text, const char *p);

void *readerPipe(void *);

int main_com(char *file_p[]);



//controllore
void invia_cont(struct messaggio *m);
struct messaggio *ricevi_cont();
void invia_rs(struct messaggio *m);
struct messaggio *ricevi_rs();
void libera_semafori();
int inizializza_semafori();
#endif