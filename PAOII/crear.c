/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   crear.c
 * Author: welli
 *
 * Created on January 31, 2021, 8:28 AM
 */

#include <stdio.h>
#include <sys/shm.h>
/*
int main () {
    FILE *archivocompartido;
    key_t clavecompartida;
    int mem = 0;
    char *mcompartida = NULL;

    archivocompartido = fopen("/tmp/acompartido","w+");
    clavecompartida = ftok("/tmp/acompartido",33);

    mem = shmget(clavecompartida,sizeof(char *)*100,0777 | IPC_CREAT);
    mcompartida = (char *) shmat(mem, NULL, 0);

    printf("Creando el segmento %d de memoria compartida\n\n",mem);
    printf("Precione ENTER para liberar los recursos compartidos\n");

    getchar ();

    shmctl(mem, IPC_RMID,(struct shmid_ds *)NULL);
    unlink("/tmp/acompartido");
    return 0;
}
*/