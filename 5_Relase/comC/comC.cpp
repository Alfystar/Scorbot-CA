#include "comC.h"

struct uten *testa;  //testa della lista collegata
struct uten *coda; //coda della lista collegata

struct impostazioni *imp_ut;  //struttura che tiene traccia di tutte le impostazioni
bool newImpostaziono=false;

int stdInFake[2], stdOutFake[2];

//idee: creare semaforo che viene preso quando sto aspettando da python e rilasciato quando ho finito di ricevere
// in modo che si viene a sapere quando ho un cambio di encoder desiderati

void libera_u(struct uten *testa) {

    //testa e' il puntatore alla radice della lista collegata
    //libera la lista dalla memoria
    struct uten *aus;
    while (testa != NULL) {
        aus = testa->p;
        free(testa->data);
        free(testa);
        testa = aus;
    }
}

struct uten *inserisci_u(struct uten *testa, struct uten *mes) {
    //testa e' l' ultimo nodo della lista, mes il nodo da inserire
    //la funzione aggiorna il puntatore all' ultimo nodo con quello appena inserito
    if (testa == NULL) {
        testa = mes;
    } else {
        testa->p = mes;
        testa = mes;
    }
    return testa;
}

struct messaggio *getLast_m()
{
    /*ritorna l'ultimo messaggio e accorcia la coda*/
    if (testa==NULL)
        return NULL;
    struct messaggio * m;
    m=testa->data;
    testa=testa->p;
    return m;
}

void libera_m(struct uten *nodo) {
    //nodo e' il puntatore al nodo da liberare
    free(nodo->data);
    free(nodo);
}


int invia(struct messaggio *m, char *tipo) {
    //m e' il puntatore al messaggio da cui prendere i dati da inviare,tipo indica se si tratta di un messaggio encoder o di impostazioni
    //ritorna -1 se fallisce l' invio,1 altrimenti

    //PROBLEMA:se fallisce dire a python che l' invio e' fallito(o con un timer o inviando un carattere speciale tipo / o \ (se ho fallito l' invio pero' probabilmente non potro' inviarlo))

    int dim = sizeof(messaggio) + 130;
    char mes[dim];   //mes e' la stringa da inviare
    if (strcmp(tipo, "e") == 0) {
        sprintf(mes, "e|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d", m->enc[0], m->enc[1], m->enc[2], m->enc[3], m->enc[4],
                m->enc[5], m->cor[0], m->cor[1], m->cor[2], m->cor[3], m->cor[4], m->cor[5]);
    } else {
        sprintf(mes, "i|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d", m->imp->maxE[0], m->imp->maxE[1],
                m->imp->maxE[2], m->imp->maxE[3], m->imp->maxE[4], m->imp->maxE[5], m->imp->minE[0], m->imp->minE[1],
                m->imp->minE[2], m->imp->minE[3], m->imp->minE[4], m->imp->minE[5], m->imp->maxC[0], m->imp->maxC[1],
                m->imp->maxC[2], m->imp->maxC[3], m->imp->maxC[4], m->imp->maxC[5]);
    }


    int cor, pas; //byte correnti inviati, e byte inviati nel passato
    int size = strlen(mes);
    cor = dprintf(stdInFake[writeEnd], "%s\n", mes);
    if (cor < 0) {
        return -1;
    }
    pas = cor;
    while (pas < size) {
        cor = dprintf(stdInFake[writeEnd], "%s\n", &mes[pas]);
        if (cor < 0) {
            return -1;
        }
        pas = pas + cor;
    }

    return 1;
}

struct messaggio *parsing(char *text, char *p) {
    //text la stringa da dove fare il parsing e p il carattere di delimitazione
    //restituisce 1 se ho fatto il parsing delle impostazioni, il puntatore al nodo che memorizza gli encoder altrimenti
    char *buff;
    buff = strtok(text, p);
    if (strcmp(buff, "e") == 0) {   /** Ricevo encoder**/

        struct messaggio *m = (struct messaggio *)malloc(sizeof(struct messaggio));
        if (!m) {
            puts("Impossibile allocare risorse");
            exit(-1);
        }
        for (int i = 0; i < 6; i++) {
            buff = strtok(NULL, p);
            m->enc[i] = atoi(buff);
        }
        return m;
    } else if (strcmp(buff, "i") == 0) { /** Ricevo impostazioni da inviare all'arduino**/

        for (int i = 0; i < 6; i++) {
            buff = strtok(NULL, p);
            imp_ut->maxE[i] = atoi(buff);
        }
        for (int i = 0; i < 6; i++) {
            buff = strtok(NULL, p);
            imp_ut->minE[i] = atoi(buff);
        }

        for (int i = 0; i < 6; i++) {
            buff = strtok(NULL, p);
            imp_ut->maxC[i] = atoi(buff);
        }
        newImpostaziono=true;
        return NULL;
    } else {
        printf("Messaggio in ricezione da Python errato\n");
        exit(-1);
    }


}

void *readerPipe(void *) {//ricevi da Python

    int size = sizeof(char);
    int size2 = sizeof(messaggio) + 130;
    char text[size2];
    testa = NULL;
    coda = NULL;
    int cor, pas;
    int ver;

    while (1) {
        pas = 0;
        ver = 1; //variabile di controllo
        while (ver) {
            cor = read(stdOutFake[readEnd], &text[pas], size);
            if (cor < 0) {
                printf("ERRORE");
                exit(-2);
            }
            if (text[pas] == '\n') {
                ver = 0;
            }
            pas += cor;
        }

        struct messaggio *m_ric;
        //parsing 
        m_ric = parsing(text, "|");
        if (m_ric != NULL) {
            //allocazione del dato in memoria
            struct uten *nuovo = (struct uten *)malloc(sizeof(struct uten));
            if (!nuovo) {
                printf("Impossibile allocare risorse");
                exit(-1);
            }
            nuovo->data = m_ric;
            nuovo->p = NULL;
            if (testa == NULL) {
                testa = nuovo;
            }
            coda = inserisci_u(coda, nuovo);
        }
    }
}

int main_com(char *dirPy[],char *pathPy) {

    pipe(stdInFake);
    pipe(stdOutFake);

    //creo una struttura impostazioni e l'assegno al globale
    imp_ut = (struct impostazioni *)malloc(sizeof(struct impostazioni));
    memset(imp_ut,0,sizeof(struct impostazioni));

    int pid = fork();
    if (pid) //dad
    {
        pthread_t tid;
        pthread_create(&tid, NULL, readerPipe, NULL);

    } else //son
    {
        chdir(pathPy);
        //override stdin and stdout
        dup2(stdInFake[readEnd], 0);
        dup2(stdOutFake[writeEnd], 1);
        //exec python programs
        //if(execvp("python3", argv))
        char *argvExec[2];
        char padding[8];
        char argvPy[128];
        //strncpy(argvPy,dirPy,128);

        argvExec[0]=padding;
        argvExec[1]=argvPy;

        if (execvp("python3", dirPy)) {
            perror("execlp fail :");
            exit(0);
        }
    }
}


sem_t *sem;  //semaforo per il main e per il controllo
sem_t *sem2; //semaforo per il main e per il controllo
struct messaggio *i_con; //variabile globale dove i dati vengono immessi per il controllo
struct messaggio *i_main; //variabile globale dove i dati vengono immessi per il main
#define base "s_invio_ard"
#define ricev "s_ric_ard"


void invia_cont(struct messaggio *m) {
    //m e' il puntatore alla struttura dove ho inserito i dati da inviare al controllo
    //il semaforo_a deve essere gia' suo(a 1)
    i_con = m;
    sem_post(sem);
}

struct messaggio *ricevi_cont() {
    //ritorna il puntatore alla struttura dove sono inseriti i dati inviati dal controllo(la usa il main)
    sem_wait(sem2);
    return i_main;
}

void invia_rs(struct messaggio *m) {
    //m e' il puntatore alla struttura dove ho inserito i dati da inviare al main
    //il semaforo_b deve essere gia' suo(a 1)
    i_main = m;
    sem_post(sem2);
}


struct messaggio *ricevi_rs() {
    // ritorna il puntatore alla struttura dove sono inseriti i dati inviati dal main(la usa il controllo)
    sem_wait(sem);
    return i_con;
}

void libera_semafori() {//libera i semafori
    sem_unlink(base);
    sem_destroy(sem);
    sem_unlink(ricev);
    sem_destroy(sem2);
}

int inizializza_semafori() {
    //ritorna -1 se e' fallita la creazione dei semafori, 1 altrimenti
    sem = sem_open(base, O_CREAT, 0666, 1);
    sem2 = sem_open(ricev, O_CREAT, 0666, 1);
    if (sem == NULL || sem2 == NULL) {
        printf("Errore apertura semaforo");
        return -1;
    }
    return 1;
}