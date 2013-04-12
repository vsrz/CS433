#include<stdio.h>
#include<sched.h>
#include<pthread.h>
#include<time.h>
#include<semaphore.h>
#define NBUFF   100

int nitems;		/* read-only by producer and consumer */
int buff[NBUFF];	/* shared data area */

sem_t produced,consumed;
pthread_mutex_t mutex; /* mutex ID */
void setlock(){pthread_mutex_lock(&mutex);};
void setunlock(){pthread_mutex_unlock(&mutex);};
void *produce(void*);
void *consume(void*);

void *produce(void *arg){
  int i;
  for(i=0;i<nitems;i++){
    sem_wait(&consumed);
    setlock();
    sched_yield();
    buff[i%NBUFF]=i; 	/* store i into circular buffer */
    setunlock();
    sem_post(&produced);
  }
  if(i==(nitems/2))
  return(NULL);
}

void *consume(void *arg){
  int i;
  for(i=0;i<nitems;i++){
    sem_wait(&produced); 
    setlock();
    sched_yield();
    if(i!=buff[i%NBUFF])
      printf("out of sync: buff[%d] = %d \n",i,buff[i%NBUFF]);
    else
      printf("buff[%d] = %d \n", i, buff[i % NBUFF]);	
    setunlock();
    sem_post(&consumed);
  }
  return(NULL);
}

int main(int argc, char *argv[]){
  pthread_t tid1,tid2;
  if (argc != 2){
    printf("Usage: %s <#items> \n", argv[0]);
    exit(1);
  }
  if(pthread_mutex_init(&mutex,NULL)<0){
    perror("pthread_mutex_init");
    exit(1);
  }
  if(sem_init(&produced,0,1)<0){
    perror("sem_init");
    exit(1);
  }
  if(sem_init(&consumed,0,1)<0){
    perror("sem_init");
    exit(1);
  }
  nitems = atoi(argv[1]);
  /* Create one producer thread and on consumer thread */
  if(pthread_create(&tid1, NULL, &produce, NULL)!=0){
    perror("pthread_create");
    exit(1);
  }
  if(pthread_create(&tid2, NULL, &consume, NULL)!=0){
    perror("pthread_create");
    exit(1);
  }
  /* wait for the two threads */	
  (void)pthread_join(tid1, NULL);
  (void)pthread_join(tid2, NULL);
  (void)sem_destroy(&produced);
  (void)sem_destroy(&consumed);
  (void)pthread_mutex_destroy(&mutex);
  exit(0);
}

