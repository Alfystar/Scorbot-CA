#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>

#include "progetto.h"

#include "progetto.c"

int main(int argc,char* argv[]){
 printf("tentativo di esempio\n");
 if(argc!=2){
   printf("Inserire il file python da eseguire\n");
   exit(-1);
 }
 main_com(argv);
 puts("oi");
 while(1){}
/* struct uten* ciao=malloc(sizeof(struct uten));
 ciao->data=malloc(sizeof(struct messaggio));
 ciao->data->cor[0]=3;
 ciao->data->enc[0]=1;
 ciao->data->cor[1]=3;
 ciao->data->enc[0]=1;
 ciao->data->imp=malloc(sizeof(impostazioni));
 ciao->data->imp->imp1="ciao";
 ciao->data->imp->imp2="o";
 
 char buff[128];

 componi_mes(ciao->data,buff);
 puts(buff);
 printf("%d",ciao->data->cor[0]);
 free(ciao->data->imp);
 free(ciao->data);
 free(ciao) ;
 */
}