#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>


void *thr_func1 (void *);
void *thr_func2 (void *);

pthread_mutex_t    mutex1;
pthread_mutex_t    mutex2;


int main( )
{

    pthread_t  tid1;
    pthread_t  tid2;

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    pthread_create(&tid1, NULL, thr_func1, NULL);
    pthread_create(&tid2, NULL, thr_func2, NULL);    

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    exit (EXIT_SUCCESS);

}

void *thr_func1(void *arg)
{

    printf("thread Id %x running ...\n", pthread_self());
    pthread_mutex_lock(&mutex1);
    sched_yield();
    pthread_mutex_lock(&mutex2);

    printf("thread id %x obtained locks \n", pthread_self());

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    pthread_exit(NULL);

}
    
void *thr_func2(void *arg)
{

    printf("thread Id %x running ...\n", pthread_self());
    pthread_mutex_lock(&mutex2);
    sched_yield();
    pthread_mutex_lock(&mutex1);

    printf("thread id %x obtained locks \n", pthread_self());

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);

}

