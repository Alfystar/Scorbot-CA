#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include "progetto.h"
//pipefd[0] refers to the read end of the  pipe.
//pipefd[1] refers to the write end of the pipe
#define writeEnd 1
#define readEnd 0
//idee: creare semaforo che viene preso quando sto aspettando da python e rilasciato quando ho finito di ricevere
// in modo che si viene a sapere quando ho un cambio di encoder desiderati

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



int invia(struct messaggio *m,char *tipo){
  //m e' il puntatore al messaggio da cui prendere i dati da inviare,tipo indica se si tratta di un messaggio encoder o di impostazioni
  //ritorna -1 se fallisce l' invio,1 altrimenti
 
  //PROBLEMA:se fallisce dire a python che l' invio e' fallito(o con un timer o inviando un carattere speciale tipo / o \ (se ho fallito l' invio pero' probabilmente non potro' inviarlo))
 
 int dim=sizeof(messaggio)+130;
 char mes[dim];   //mes e' la stringa da inviare
 if(strcmp(tipo,"e")==0){
   sprintf(mes,"e|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d",m->enc[0],m->enc[1],m->enc[2],m->enc[3],m->enc[4],m->enc[5],m->cor[0],m->cor[1],m->cor[2],m->cor[3],m->cor[4],m->cor[5]);
 }else{
   sprintf(mes,"i|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d",m->imp->maxE[0],m->imp->maxE[1],m->imp->maxE[2],m->imp->maxE[3],m->imp->maxE[4],m->imp->maxE[5],m->imp->minE[0],m->imp->minE[1],m->imp->minE[2],m->imp->minE[3],m->imp->minE[4],m->imp->minE[5],m->imp->maxC[0],m->imp->maxC[1],m->imp->maxC[2],m->imp->maxC[3],m->imp->maxC[4],m->imp->maxC[5]); 
 }


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

struct messaggio* parsing(char* text, char* p){
  //text la stringa da dove fare il parsing e p il carattere di delimitazione
  //restituisce 1 se ho fatto il parsing delle impostazioni, il puntatore al nodo che memorizza gli encoder altrimenti
  char *buff;
 
  buff=strtok(text,p);
  if(strcmp(buff,"e")==0){
    
    struct messaggio* m=malloc(sizeof(struct messaggio));
    if(!m){
       puts("Impossibile allocare risorse");
       exit(-1);
   }
   for(int i=0;i<6;i++){
    buff=strtok(NULL,p);
    m->enc[i]=atoi(buff);
   }
   return m;
  } 
  else if(strcmp(buff,"i")==0){
   
   for(int i=0;i<6;i++){
    buff=strtok(NULL,p);
    imp_ut->maxE[i]=atoi(buff);
   }
   for(int i=0;i<6;i++){
    buff=strtok(NULL,p);
    imp_ut->minE[i]=atoi(buff);
   }
   for(int i=0;i<6;i++){
    buff=strtok(NULL,p);
    imp_ut->maxC[i]=atoi(buff);
   }

   //m->imp->imp1=buff; //se si vuole prevedere di salvare in memoria anche le impostazioni(cosi' da errore perche' devo allocare memoria per imp1 ed imp2)
  
   //m->imp->imp2=buff;
  //aggiungere eventuali impostazioni
    return 1;
  }
  else{
    puts("Messaggio in ricezione da Python errato\n");
    exit(-1);
  }
  
  
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
    { 
      pas=0;
      ver=1; //variabile di controllo
      while(ver){
        
  
        cor=read(stdOutFake[readEnd],&text[pas],size);
        if(cor<0){
          puts("ERRORE");
          exit(-2);
        }
  
      
        if(text[pas]=='\n'){
          ver=0;
        }
        pas+=cor;
      } 
      
    puts("Eccomi");
  

      puts("\nLeggo: ");
      puts(text);
        struct messaggio *m_ric;
        //parsing 
        m_ric=parsing(text,"|");
        
        if(m_ric!=1){
         //allocazione del dato in memoria
         struct uten *nuovo=malloc(sizeof(struct uten));
         if(!nuovo){
           puts("Impossibile allocare risorse");
           exit(-1);
         }
         nuovo->data=m_ric;
         nuovo->p=NULL;
         if(testa==NULL){
          testa=nuovo;
         }
         coda=inserisci_u(coda,nuovo); 
        }
        
      //stampa per la prova
      /* 
       if(m_ric!=1){
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
       }else{
         puts(imp_ut->imp1);
         puts(imp_ut->imp2);
       }
        */
    }
}

int main_com(char *file_p[]) {
  

    pipe(stdInFake);
    pipe(stdOutFake);
    struct impostazioni i_ut;
    for(int i=0;i<nMot;i++){
      i_ut.maxE[i]=i+100;
      i_ut.minE[i]=-100;
      i_ut.maxC[i]=5000;
    }
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
        //exec python programs
        //if(execvp("python3", argv))
        if(execvp("python3", file_p))
        {
            perror("execlp fail :");
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
    invia(&nodo,"e");
    sleep(10);
    invia(&nodo,"i");
    sleep(10);

    nodo.enc[0]=20;
    nodo.enc[1]=15;
    nodo.enc[2]=25;
    nodo.enc[3]=130;
    nodo.enc[4]=103;
    nodo.enc[5]=101;
      
     
    invia(&nodo,"e");
    sleep(10);
    nodo.cor[0]=20;
    nodo.cor[1]=120;
    nodo.cor[2]=520;
    nodo.cor[3]=320;
    nodo.cor[4]=120;
    nodo.cor[5]=220;


    invia(&nodo,"i");
    sleep(10);

    invia(&nodo,"e");
    sleep(10);

    
    for(int i=0;i<nMot;i++){
     imp_ut->maxE[i]=i+1000;
     imp_ut->minE[i]=-1000;
     imp_ut->maxC[i]=i+10;
   }
    
    invia(&nodo,"i");
    sleep(10);
    
    libera_u(testa);
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