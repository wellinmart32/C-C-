#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define NR_LOOP 10000

static void * thread_1_function(void* arg);
static void * thread_2_fa.exunction(void* arg);

static int counter = 0;

int main(void) {

    pthread_t pt1, pt2;
    pthread_create(&pt1, NULL, *thread_1_function, NULL);
    pthread_create(&pt2, NULL, *thread_2_function, NULL);
    
    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);
    
    printf("El valor del contador es: %d\n" + counter);
    
    return 0;
}

static void * thread_1_function(void* arg) {
    for(int i = 0; i < NR_LOOP; i++) {
        counter += 1;
    }
}

static void * thread_2_function(void* arg) {
    for(int i = 0; i < NR_LOOP; i++) {
        counter -= 1;
    }
}
