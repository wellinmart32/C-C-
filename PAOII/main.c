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
#include <sys/wait.h>
#include <errno.h>

#define NOM_TOM "/mtomate"
#define NOM_PEP "/mpepino"
#define NOM_LEC "/mlechuga"
#define NOM_CAR "/mcarne"
#define NOM_QUE "/mqueso"
#define NOM_PAN "/mpan"
#define TAM 10000

#define N 10

static int counter = 0;
int rodajas_tomate, rodajas_pepino, hojas_lechuga, carne,
        rodajas_queso, pedazo_pan, hamburguesa, inicio_banda, estado_banda;
char banda, detener_banda, *m_tomate, *m_pepino, *m_lechuga, *m_carne,
        *m_queso, *m_pan;
char *tam_dir = "20";
pthread_t pts[N];
sem_t sm1, sm2, sm3;

void crear_memoria_compartida();
void obtener_ingredientes();
void limpiar_memoria();
void iniciar_bandas();
char definir_banda();
void detener_bandas();
static void * generar_hamburguesas(void* arg);

void main(void) {
    crear_memoria_compartida();
    iniciar_bandas();
}

void crear_memoria_compartida() {
    int ft, fp, fl, fc, fq, fa;
    
    ft = shm_open(NOM_TOM, O_CREAT | O_RDWR, 00600);
    fp = shm_open(NOM_PEP, O_CREAT | O_RDWR, 00600);
    fl = shm_open(NOM_LEC, O_CREAT | O_RDWR, 00600);
    fc = shm_open(NOM_CAR, O_CREAT | O_RDWR, 00600);
    fq = shm_open(NOM_QUE, O_CREAT | O_RDWR, 00600);
    fa = shm_open(NOM_PAN, O_CREAT | O_RDWR, 00600);
    
    if ((ft == -1) || (fp == -1) || (fl == -1) || (fc == -1) 
            || (fq == -1) || (fa == -1)) {
        printf("Error, Memoria compartida no puede ser creada\n");
        exit(1);
    }

    if ((-1 == ftruncate(ft, sizeof(tam_dir))) || (-1 == ftruncate(fp, sizeof(tam_dir)))
            || (-1 == ftruncate(fl, sizeof(tam_dir))) || (-1 == ftruncate(fc, sizeof(tam_dir))) 
            || (-1 == ftruncate(fq, sizeof(tam_dir))) || (-1 == ftruncate(fa, sizeof(tam_dir)))) {
        printf("Error, Memoria compartida no puede ser actualizada\n");
        exit(1);
    }
    
    close(ft);
    close(fp);
    close(fl);
    close(fc);
    close(fq);
    close(fa);
}

void obtener_ingredientes() {
    int ft, fp, fl, fc, fq, fa;
    struct stat obj_com;

    ft = shm_open(NOM_TOM, O_RDONLY, 00400);
    fp = shm_open(NOM_PEP, O_RDONLY, 00400);
    fl = shm_open(NOM_LEC, O_RDONLY, 00400);
    fc = shm_open(NOM_CAR, O_RDONLY, 00400);
    fq = shm_open(NOM_QUE, O_RDONLY, 00400);
    fa = shm_open(NOM_PAN, O_RDONLY, 00400);

    if ((ft == -1) || (fp == -1) || (fl == -1) || (fc == -1) 
            || (fq == -1) || (fa == -1)) {
        printf("Error en describir el archivo \n");
        exit(1);
    }

    if ((-1 == fstat(ft, &obj_com)) || (-1 == fstat(fp, &obj_com))
            || (-1 == fstat(fl, &obj_com)) || (-1 == fstat(fc, &obj_com)) 
            || (-1 == fstat(fq, &obj_com)) || (-1 == fstat(fa, &obj_com))) {
        printf("Error en la función fstat\n");
        exit(1);
    }

    m_tomate = mmap(NULL, obj_com.st_size, PROT_READ, MAP_SHARED, ft, 0);
    m_pepino = mmap(NULL, obj_com.st_size, PROT_READ, MAP_SHARED, fp, 0);
    m_lechuga = mmap(NULL, obj_com.st_size, PROT_READ, MAP_SHARED, fl, 0);
    m_carne = mmap(NULL, obj_com.st_size, PROT_READ, MAP_SHARED, fc, 0);
    m_queso = mmap(NULL, obj_com.st_size, PROT_READ, MAP_SHARED, fq, 0);
    m_pan = mmap(NULL, obj_com.st_size, PROT_READ, MAP_SHARED, fa, 0);
        
    if ((m_tomate == MAP_FAILED) || (m_pepino == MAP_FAILED)
        || (m_lechuga == MAP_FAILED) || (m_carne == MAP_FAILED) 
        || (m_queso == MAP_FAILED) || (m_pan == MAP_FAILED)) {
        printf("Mapeo fallido en leer el proceso de mapeo: \n");
        exit(1);
    }
        
    if(m_tomate != "" || m_pepino != "" || m_lechuga != "" || m_carne != "" 
            || m_queso != ""  || m_pan != "" ) {

//        printf("%s TOMATE TOMATE TOMATE\n\n", m_tomate);
//        printf("%s PEPINO PEPINO PEPINO\n\n", m_pepino);
        close(ft);
        close(fp);
        close(fl);
        close(fc);
        close(fq);
        close(fa);
        
        m_tomate = "";
        m_pepino = "";
        m_lechuga = "";
        m_carne = "";
        m_queso = "";
        m_pan = "";
        
        limpiar_memoria();
    }
}

void limpiar_memoria() {
    int ft, fp, fl, fc, fq, fa;
    char *pt, *pp, *pl, *pc, *pq, *pa;

    ft = shm_open(NOM_TOM, O_RDWR, 0);
    fp = shm_open(NOM_PEP, O_RDWR, 0);
    fl = shm_open(NOM_LEC, O_RDWR, 0);
    fc = shm_open(NOM_CAR, O_RDWR, 0);
    fq = shm_open(NOM_QUE, O_RDWR, 0);
    fa = shm_open(NOM_PAN, O_RDWR, 0);

    pt = mmap(0, sizeof(tam_dir), PROT_WRITE, MAP_SHARED, ft, 0);
    pp = mmap(0, sizeof(tam_dir), PROT_WRITE, MAP_SHARED, ft, 0);
    pl = mmap(0, sizeof(tam_dir), PROT_WRITE, MAP_SHARED, ft, 0);
    pc = mmap(0, sizeof(tam_dir), PROT_WRITE, MAP_SHARED, ft, 0);
    pq = mmap(0, sizeof(tam_dir), PROT_WRITE, MAP_SHARED, ft, 0);
    pa = mmap(0, sizeof(tam_dir), PROT_WRITE, MAP_SHARED, ft, 0);
    
    memcpy(pt, "0", sizeof(tam_dir));
    memcpy(pp, "0", sizeof(tam_dir));
    memcpy(pl, "0", sizeof(tam_dir));
    memcpy(pc, "0", sizeof(tam_dir));
    memcpy(pq, "0", sizeof(tam_dir));
    memcpy(pa, "0", sizeof(tam_dir));
    
    close(ft);
    close(fp);
    close(fl);
    close(fc);
    close(fq);
    close(fa);
}

void iniciar_bandas() {
    banda = 'A';
    estado_banda = 0;
    detener_banda = 'Z';
    inicio_banda = 1;
    hamburguesa = 1;
    sem_init(&sm1, 0, 1);
    sem_init(&sm2, 0, 1);
    sem_init(&sm3, 0, 1);
    rodajas_tomate = 50;
    rodajas_pepino = 60;
    hojas_lechuga = 40;
    carne = 20;
    rodajas_queso = 20;
    pedazo_pan = 40;

    for(int i = 0; i < N; i++) {
        pthread_t pt;
        pts[i] = pt;
    }

    for(int i = 0; i < N; i++) {
        pthread_create(&pts[i], NULL, *generar_hamburguesas, NULL);
//        printf("********%d********\n", i+1);
    }
    for(int i = 0; i < N; i++)
        pthread_join(pts[i], NULL);
}

char definir_banda() {
    if (estado_banda == 0) {
        if(inicio_banda) {
            inicio_banda--;
            return 'A';
        }

        if(banda == 'A')
            banda = 'B';
        else if(banda == 'B')
            banda = 'C';
        else if(banda == 'C')
            banda = 'D';
        else if(banda == 'D')
            banda = 'E';
        else if(banda == 'E')
            banda = 'F';
        else if(banda == 'F')
            banda = 'G';
        else if(banda == 'G')
            banda = 'H';
        else if(banda == 'H')
            banda = 'I';
    }else {
        if(estado_banda == 1)
            banda = 'A';
        else if(estado_banda == 2)
            banda = 'B';
        else if(estado_banda == 3)
            banda = 'C';
        else if(estado_banda == 4)
            banda = 'D';
        else if(estado_banda == 5)
            banda = 'E';
        else if(estado_banda == 6)
            banda = 'F';
        else if(estado_banda == 7)
            banda = 'G';
        else if(estado_banda == 8)
            banda = 'H';
        else if(estado_banda == 9)
            banda = 'I';
        
        estado_banda = 0;
        detener_banda = 'Z';
    }
    
    return banda;
}

void detener_bandas() {
    int orden;
    
    if(detener_banda == 'Z') {
        printf("Menu de bandas:\n");
        printf("[1] Banda A\n[2] Banda B\n[3] Banda C\n[4] Banda D\n[5] Banda E\n[6] Banda F\n[7] Banda G\n[8] Banda H\n[9] Banda I\n[10] Continuar\n\n");
        printf("Ingrese su orden:\n");
        scanf("%d", &orden);

        if(orden == 1)
            detener_banda = 'A';
        else if(orden == 2)
            detener_banda = 'B';
        else if(orden == 3)
            detener_banda = 'C';
        else if(orden == 4)
            detener_banda = 'D';
        else if(orden == 5)
            detener_banda = 'E';
        else if(orden == 6)
            detener_banda = 'F';
        else if(orden == 7)
            detener_banda = 'G';
        else if(orden == 8)
            detener_banda = 'H';
        else if(orden == 9)
            detener_banda = 'I';
        else
            return;
    }
}

static void *generar_hamburguesas(void *arg) {
    int total_tomate, total_pepino, total_lechuga, total_carne, total_queso
            ,total_pan, pc = fork(), estado_hilo;
    pthread_t pt;

    sem_wait(&sm1);
    char letra_banda = definir_banda();
    sem_post(&sm1);
    
    while(1) {
//        printf("----------------%c----------1\n", letra_banda);
        sem_wait(&sm2);
        total_tomate = rodajas_tomate - 3;
        total_pepino = rodajas_pepino - 4;
        total_lechuga = hojas_lechuga - 2;
        total_carne = carne - 1;
        total_queso = rodajas_queso - 1;
        total_pan = pedazo_pan - 2;
        sem_post(&sm2);
//        printf("----------------%c----------2\n", letra_banda);
        if ((total_tomate >= 0) && (total_pepino >= 0) 
                && (total_lechuga >= 0) && (total_carne >= 0) 
                && (total_queso >= 0) && (total_pan >= 0)) {
            sem_wait(&sm3);
            sleep(10);
            rodajas_tomate = rodajas_tomate - 3;
            rodajas_pepino = rodajas_pepino - 4;
            hojas_lechuga = hojas_lechuga - 2;
            carne = carne - 1;
            rodajas_queso = rodajas_queso - 1;
            pedazo_pan = pedazo_pan - 2;
            printf("Generando la hamburguesa número %d en la banda %c\n", hamburguesa, letra_banda);
            printf("Ingredientes restantes:\nTomate: %d, Pepino: %d, lechuga: %d, carne: %d, queso: %d, pan: %d\n", total_tomate,
                    total_pepino, total_lechuga, total_carne, total_queso, total_pan);
            hamburguesa++;
            obtener_ingredientes();
//            detener_bandas();
            sem_post(&sm3);
        }
        
        if (detener_banda == letra_banda) {
            pthread_create(&pt, NULL, *generar_hamburguesas, NULL);
            pthread_join(pt, NULL);
            pc = wait(&estado_hilo);
        }
    }
}
