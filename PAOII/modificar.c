/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <sys/shm.h>
/*
int main() {
        FILE *archivocompartido;
        key_t clavecompartida;
        int mem = 0;
        int contador = 0;
        char *mcompartida = NULL;

        archivocompartido = fopen("/tmp/acompartido", "w+");
        clavecompartida = ftok("/tmp/acompartido", 33);

        mem = shmget (clavecompartida,sizeof(char *)*100,0777);
        mcompartida = (char *) shmat(mem, NULL, 0);

        printf("Trabjando con el segmento: %d\n", mem);
        printf("Cada segundo se actualiza el valor compartido, el programa dura un minuto\n");

    while(contador != 60) {
        contador = contador + 1;
        sprintf(mcompartida,"%d",contador);        
        sleep(1);
    }

    return 0;
}
 */