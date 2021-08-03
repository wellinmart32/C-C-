/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   compartir_memoria.c
 * Author: welli
 *
 * Created on January 31, 2021, 7:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <string.h>

#define NOMBRE_OM "/memObj"

/*
 * 
 */

/*
int main() {
    int fd, size;
    char bf[] = "63", *ptr;//, txt[] = "Esto es 300";
//    bf = txt;
    
    fd = shm_open(NOMBRE_OM, O_RDWR, 0);
    
    if (fd == -1) {
        printf("Error, Memoria compartida no puede ser creada\n");
        exit(1);
    }
    
    ptr = mmap(0, sizeof(bf), PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (ptr == MAP_FAILED) {
        printf("Error en el mapeo de la memoria\n");
        exit(1);
    }
    
//    size = strlen(ptr);
//    ptr = malloc(size*sizeof(char));
    memcpy(ptr, bf, sizeof(bf));
//    free(ptr);
    close(fd);
    
    return 0;
}
*/