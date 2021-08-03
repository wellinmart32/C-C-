/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   compartir_memoria.c
 * Author: welli
 *
 * Created on January 31, 2021, 6:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/unistd.h>
#include <sys/types.h>

#define NOMBRE_OM "/memObj"
#define TAM 200

/*
 * 
 */

/*
int main() {
    int fd;
    char *bf, texto[] = "600";
    
    fd = shm_open(NOMBRE_OM, O_CREAT | O_RDWR, 00600);
    
    if (fd == -1) {
        printf("Error, Memoria compartida no puede ser creada\n");
        exit(1);
    }

    if (-1 == ftruncate(fd, sizeof(texto))) {
        printf("Error, Memoria compartida no puede actualizada\n");
        exit(1);
    }
    
    close(fd);
    return 0;
}
 */