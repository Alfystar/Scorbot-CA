#include <stdio.h>
#include <stdlib.h>
#include "comLib.cpp"

int main(int argc, char *argv[]) {
    printf("tentativo di esempio\n");
    if (argc != 2) {
        printf("Inserire il file python da eseguire\n");
        exit(-1);
    }
    main_com(argv);
    puts("oi");
    while (1) {}
}