/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   obtener.c
 * Author: welli
 *
 * Created on January 31, 2021, 10:31 AM
 */

#include <stdio.h>
#include <sys/shm.h>
/*
int main() {
    FILE *archivocompartido;
    key_t clavecompartida;
    int mem = 0;
    char *mcompartida = NULL;

    archivocompartido = fopen("/tmp/acompartido", "w+");
    clavecompartida = ftok("/tmp/acompartido", 33);

    mem =  shmget(clavecompartida,sizeof(char *)*100, 0777);
    mcompartida = (char *) shmat(mem, NULL, 0);

    printf("Trabajando con el segmento: %d\n", mem);
    printf("El valor compartido es: %s\n", mcompartida);

    return 0;
}
*/