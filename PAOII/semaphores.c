/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: welli
 *
 * Created on January 29, 2021, 8:26 PM
 */

#include <stdio.h>
//#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define NR_LOOP 10000
static void * thread_1_function(void* arg);
static void * thread_2_function(void* arg);

static int counter = 0;
/*
 * 
 
int main(void) {
    pthread_t pt_1, pt_2;
    pthread_create(&pt_1, NULL, *thread_1_function, NULL);
    pthread_create(&pt_2, NULL, *thread_2_function, NULL);
    
    pthread_join(pt_1, NULL);
    pthread_join(pt_2, NULL);
    
    printf("Valor del contador: %d\n", counter);
    return 0;
}
*/
static void * thread_1_function(void* arg) {
    for(int i = 0; i < NR_LOOP; i++) {
//        printf("subiendo");
        counter += 1;
    }
}

static void * thread_2_function(void* arg) {
    for(int i = 0; i < NR_LOOP; i++) {
//        printf("bajando");
        counter -= 1;
    }
}