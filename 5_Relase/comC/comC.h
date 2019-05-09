#ifndef COMPY_H
#define COMPY_H
#define nMot 6

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include "SPILib/spisend.h"


//pipefd[0] refers to the read end of the  pipe.
//pipefd[1] refers to the write end of the pipe
#define writeEnd 1
#define readEnd 0

struct impostazioni{
  int maxE[nMot];
  int minE[nMot];
  int maxC[nMot];
//massimo e minimo numero encoder(vettore da 6)
//massimo valore corrente(vettore da 6)
};

struct messaggio{
  int enc[6];
  int cor[6];
  struct impostazioni *imp;
};

struct uten{  //nodo della lista collegata
  struct messaggio *data; 
  struct uten *p;
};

extern struct uten *testa;  //testa della lista collegata
extern struct uten *coda; //coda della lista collegata

extern struct impostazioni *imp_ut;  //struttura che tiene traccia di tutte le impostazioni
extern bool newImpostaziono;

extern int stdInFake[2], stdOutFake[2];
/*
 * write on stdIn to talk c --> py
 *
 * read from stdOut to listen c <-- py
 *
 */

struct uten* inserisci_u(struct uten *testa,struct uten *mes);

struct messaggio* getLast_m();

void libera_m(struct uten *nodo);

void libera_u(struct uten *testa);

int invia(struct messaggio *m,char *tipo);

struct messaggio* parsing(char* text, char* p);

void *readerPipe (void *);

int main_com(char *dirPy[],char *pathPy);



//controllore

void invia_cont(struct messaggio* m);

struct messaggio* ricevi_cont();

void invia_rs(struct messaggio *m);

struct messaggio* ricevi_rs();

void libera_semafori();

int inizializza_semafori();


#endif