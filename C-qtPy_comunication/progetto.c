#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
//pipefd[0] refers to the read end of the  pipe.
//pipefd[1] refers to the write end of the pipe
#define writeEnd 1
#define readEnd 0
//idee: creare semaforo che viene preso quando sto aspettando da python e rilasciato quando ho finito di ricevere
// in modo che si viene a sapere quando ho un cambio di encoder desiderati
//semaforo per l' invio? se nessuno invia io posso inviare. (inutile penso)


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

void libera_u(struct uten *testa){
  //testa e' il puntatore alla radice della lista collegata
  //libera la lista dalla memoria
  struct uten* aus;
  while(testa!=NULL){
    aus=testa->p;
    free(testa->data); 
    free(testa);
    testa=aus;
  }
}

struct uten* libera_m(struct uten *nodo){//controllare se e' giusto
  //nodo e' il puntatore al nodo da liberare
  //restituisce il puntatore al nuovo nodo della lista (e quindi alla nuova testa)
   struct uten* new;
   new=nodo->p;
   free(nodo->data);
   free(nodo);
   return new;
}

struct uten *testa;  //testa della lista collegata
struct impostazioni *imp_ut;  //struttura che tiene traccia di tutte le impostazioni
struct uten *coda; //coda della lista collegata

int stdInFake[2], stdOutFake[2];
/*
 * write on stdIn to talk c --> py
 *
 * read from stdOut to listen c <-- py
 *
 */

void componi_mes(struct messaggio *mes,char* buffer){
  //mes e' il puntatore al messaggio da cui prendere i dati da inviare, buffer la stringa in cui ritornare il messaggio standardizzato(pronto per essere inviato)
 //standard del messaggio da inviare. Potrei definire la dimensione di impostazioni in modo dinamico con n che mi traccia il numero di stringhe e fare in un for tante sprintf quanto n
 sprintf(buffer,"%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%s|%s",mes->enc[0],mes->enc[1],mes->enc[2],mes->enc[3],mes->enc[4],mes->enc[5],mes->cor[0],mes->cor[1],mes->cor[2],mes->cor[3],mes->cor[4],mes->cor[5],mes->imp->imp1,mes->imp->imp2);
}

int invia(char *mes){
  //mes e' la stringa da inviare
  //ritorna -1 se fallisce l' invio,1 altrimenti
  //se fallisce dire a python che l' invio e' fallito
 int cor,pas; //byte correnti inviati, e byte inviati nel passato
 int size=strlen(mes);
 cor=dprintf(stdInFake[writeEnd],"%s\n",mes);
 if(cor<0){
     return -1;
 }
 pas=cor;
 while(pas<size){
   cor=dprintf(stdInFake[writeEnd],"%s\n",&mes[pas]);
   if(cor<0){
     return -1;
   }
   pas=pas+cor;
 }
 printf("\nInvio: %s\n",mes);  
          
 return 1;
}

void parsing(struct messaggio* m,char* text, char* p){
  //m e' il messaggio dove inserire i dati, text la stringa da dove fare il parsing e p il carattere di delimitazione
  char *buff;
  buff=strtok(text,p);
  m->enc[0]=atoi(buff);
  for(int i=1;i<6;i++){
   buff=strtok(NULL,p);
   m->enc[i]=atoi(buff);
  }
  
  for(int i=0;i<6;i++){
   buff=strtok(NULL,p);
   m->cor[i]=atoi(buff);
  }
  
   buff=strtok(NULL,p);
   //m->imp->imp1=buff; //se si vuole prevedere di salvare in memoria anche le impostazioni(cosi' da errore perche' devo allocare memoria per imp1 ed imp2)
   imp_ut->imp1=buff;
   buff=strtok(NULL,p);
   imp_ut->imp2=buff;
   //m->imp->imp2=buff;
  //aggiungere eventuali impostazioni
}

void *readerPipe ()
{//ricevi da Python
    int size=sizeof(char);
    int size2=sizeof(messaggio)+15;
    char text[size2];
    testa=NULL;
    coda=NULL;
    int cor,pas;
    int ver;
  
    while (1)
    {//non va bene perche' non so la size a prescindere del messaggio
      pas=0;
      ver=1; //variabile di controllo
      while(ver){
        cor=read(stdOutFake[readEnd],&text[pas],size);
        if(cor<0){
          exit(-2);
        }
        if(text[pas]=='\n'){
          ver=0;
        }
        pas+=cor;
      } 
       printf("Leggo: %s",text);
        
        struct messaggio *m_ric=malloc(sizeof(struct messaggio));
         if(!m_ric){
           puts("Impossibile allocare risorse");
           exit(-1);
        }
        //parsing 
        parsing(m_ric,text,"|");
        //allocazione del dato in memoria
        struct uten *nodo=malloc(sizeof(struct uten));
        if(!nodo){
           puts("Impossibile allocare risorse");
           exit(-1);
        }
        nodo->data=m_ric;
        nodo->p=NULL;
        if(testa==NULL){
          testa=nodo;
        }
        coda=inserisci_u(coda,nodo); 
      //stampa per la prova
        struct uten* aus;
        struct uten* aus2;
        aus2=testa;
        int i=0;
        while(testa!=NULL){
          i+=1;
          aus=testa->p;
          printf("\nLeggo%d: %d %d %d %d %d %d %d %d %d %d %d %d\n",i,testa->data->enc[0],testa->data->enc[1],testa->data->enc[2],testa->data->enc[3],testa->data->enc[4],testa->data->enc[5],testa->data->cor[0],testa->data->cor[1],testa->data->cor[2],testa->data->cor[3],testa->data->cor[4],testa->data->cor[5]);  
          testa=aus;
        }
        testa=aus2;
    }
}

int main(int argc, char *argv[]) {
  if (argc < 2)
    {
        printf("Need Program to execute!!\n <Path_Program>\n");
        exit(0);
    }

    pipe(stdInFake);
    pipe(stdOutFake);
    
    struct impostazioni i_ut;
    i_ut.imp1="NULLO";
    i_ut.imp2="NULLO";
    imp_ut=&i_ut;  //creo una struttura impostazioni e l'assegno al globale
    
    int pid = fork();
    if (pid) //dad
    {
         
     pthread_t tid;
     pthread_create(&tid,NULL,readerPipe,NULL);
     
    } else //son
    {

        //override stdin and stdout
        dup2(stdInFake[readEnd], 0);
        dup2(stdOutFake[writeEnd], 1);
        printf("Figlio, dup eseguite");
        //exec python programs
        if(execvp("python3", argv))
        {
            perror("execvp fail :");
            exit(0);
        }
    }
    
    //esempio
    
    struct messaggio nodo;
    nodo.enc[0]=10;
    nodo.enc[1]=5;
    nodo.enc[2]=15;
    nodo.enc[3]=10;
    nodo.enc[4]=10;
    nodo.enc[5]=10;
    
    nodo.cor[0]=20;
    nodo.cor[1]=20;
    nodo.cor[2]=20;
    nodo.cor[3]=20;
    nodo.cor[4]=20;
    nodo.cor[5]=20;
    
    nodo.imp=imp_ut;
        
    int size=sizeof(messaggio)+130;
    char buffer[size];
    
    componi_mes(&nodo,buffer);
    invia(buffer);
    sleep(10);
    nodo.enc[0]=20;
    nodo.enc[1]=15;
    nodo.enc[2]=25;
    nodo.enc[3]=130;
    nodo.enc[4]=103;
    nodo.enc[5]=101;
    componi_mes(&nodo,buffer);
    invia(buffer);
    sleep(10);
    
    nodo.cor[0]=20;
    nodo.cor[1]=120;
    nodo.cor[2]=520;
    nodo.cor[3]=320;
    nodo.cor[4]=120;
    nodo.cor[5]=220;
    
    componi_mes(&nodo,buffer);
    invia(buffer);
    sleep(10);
    libera_u(coda);
    while(1){}
    return 0;
}


sem_t *sem;  //semaforo per il main e per il controllo
sem_t *sem2; //semaforo per il main e per il controllo
struct messaggio* i_con; //variabile globale dove i dati vengono immessi per il controllo
struct messaggio* i_main; //variabile globale dove i dati vengono immessi per il main
#define base "s_invio_ard"  
#define ricev "s_ric_ard"



void invia_cont(struct messaggio* m){
  //m e' il puntatore alla struttura dove ho inserito i dati da inviare al controllo
  //il semaforo_a deve essere gia' suo(a 1)
  i_con=m;
  sem_post(sem);
}

struct messaggio* ricevi_cont(){
  //ritorna il puntatore alla struttura dove sono inseriti i dati inviati dal controllo(la usa il main)
  sem_wait(sem2);
  return i_main;
}

void invia_rs(struct messaggio *m){
  //m e' il puntatore alla struttura dove ho inserito i dati da inviare al main
  //il semaforo_b deve essere gia' suo(a 1)
  i_main=m;
  sem_post(sem2);
}


struct messaggio* ricevi_rs(){
  // ritorna il puntatore alla struttura dove sono inseriti i dati inviati dal main(la usa il controllo)
  sem_wait(sem);
  return i_con;
}

void libera_semafori(){//libera i semafori
 sem_unlink(base);
 sem_destroy(sem);
 sem_unlink(ricev);
 sem_destroy(sem2);
}

int inizializza_semafori(){
  //ritorna -1 se e' fallita la creazione dei semafori, 1 altrimenti
  sem=sem_open(base,O_CREAT,0666,1);
  sem2=sem_open(ricev,O_CREAT,0666,1);
  if(sem==NULL || sem2==NULL){
    printf("Errore apertura semaforo");
    return -1;
  }
  return 1;
}