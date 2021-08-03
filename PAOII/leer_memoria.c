#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <string.h>

#define NOMBRE_OM "/memObj"

/*
 * 
 */

/*
int main(int argc, char** argv) {
    int fd;
    char *ptr;
    struct stat obj_com;
    
    fd = shm_open(NOMBRE_OM, O_RDONLY, 00400);
    
    if (fd == -1) {
        printf("Error en describir el archivo %s\n", strerror(errno));
        exit(1);
    }
    
    if(fstat(fd, &obj_com) == -1) {
        printf("Error en la función fstat\n");
        exit(1);
    }
    
    ptr = mmap(NULL, obj_com.st_size, PROT_READ, MAP_SHARED, fd, 0);
    
    if (ptr == MAP_FAILED) {
        printf("Mapeo fallido en leer el proceso de mapeo: %s\n", strerror(errno));
        exit(1);
    }
    
    printf("%s \n", ptr);
    close(fd);

    return 0;
}
**/