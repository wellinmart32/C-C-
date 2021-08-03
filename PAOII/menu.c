#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define NOM_TOM "/mtomate"
#define NOM_PEP "/mpepino"
#define NOM_LEC "/mlechuga"
#define NOM_CAR "/mcarne"
#define NOM_QUE "/mqueso"
#define NOM_PAN "/mpan"
#define TAM 10000

char *tam_dir = "5";

void ingresar_ingredientes(int ingrediente, char cantidad[]);
void menu();

void main() {
    do {
        menu();
    }while(1);
}

void menu() {
    int ingrediente;
//    char *cantidad;
    printf("Menu de ingredientes:\n");
    printf("[1] Tomate\n[2] Pepino\n[3] Lechuga\n[4] Carne\n[5] Queso\n[6] Pan\n\n");
    printf("Ingrese opción del ingrediente:\n");
    scanf("%d", &ingrediente);
    printf("Ingrese cantidad del ingrediente:\n");
//    scanf("%s", cantidad);
    ingresar_ingredientes(ingrediente, tam_dir);
}

void ingresar_ingredientes(int ingrediente, char *cantidad) {
    int f;
    char *ptr;

    if (ingrediente == 1)
        f = shm_open(NOM_TOM, O_RDWR, 0);
    else if (ingrediente == 2)
        f = shm_open(NOM_PEP, O_RDWR, 0);
    else if (ingrediente == 3)
        f = shm_open(NOM_LEC, O_RDWR, 0);
    else if (ingrediente == 4)
        f = shm_open(NOM_CAR, O_RDWR, 0);
    else if (ingrediente == 5)
        f = shm_open(NOM_QUE, O_RDWR, 0);
    else
        f = shm_open(NOM_PAN, O_RDWR, 0);
    
    if (f == -1) {
        printf("Error, Memoria compartida no puede ser creada\n");
        exit(1);
    }

    ptr = mmap(0, sizeof(tam_dir), PROT_WRITE, MAP_SHARED, f, 0);
    
    if (ptr == MAP_FAILED) {
        printf("Error en el mapeo de la memoria\n");
        exit(1);
    }
    
    memcpy(ptr, cantidad, sizeof(tam_dir));
    close(f);
}