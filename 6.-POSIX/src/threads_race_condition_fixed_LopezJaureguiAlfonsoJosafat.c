#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

int x = 0;
pthread_mutex_t mutex_addition = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;

void* thread_func(void* args){

    int i;
    for ( i = 0; i < 10000000; i++ )
    {
        // Critical section

        pthread_mutex_lock(&mutex_addition);
        x++; // errata from the processes class: this is not atomic
        pthread_mutex_unlock(&mutex_addition);
        sem_post(&sem);
    }
}

void *thread_func2(void* args) {
    int i = 0;
    for( i = 0; i < 5000000; i++) {
        sem_wait(&semaforo);
        pthread_mutex_lock(&mutex_addition);
        x--; // errata from the processes class: this is not atomic
        if ( x < 0) {
            printf("Stack underflow");
        }
        pthread_mutex_unlock(&mutex_addition);
    }
}

int main () {
    pthread_t thread_id[3];

    sem_init(&sem,0,0);

    printf("I will create two threads\n");
    printf("Point 1 >> X is: %d\n", x);
    pthread_create(&thread_id[0],NULL,&thread_func,NULL);
    pthread_create(&thread_id[1],NULL,&thread_func,NULL);
    pthread_create(&thread_id[2],NULL,&thread_func2,NULL);
    printf("The threads has been created\n");
    pthread_join(thread_id[0],NULL);
    pthread_join(thread_id[1],NULL);
    pthread_join(thread_id[2],NULL);
    printf("The threads have exited\n");
    printf("Point 2 >> X is: %d\n", x);

    return 0;
}
