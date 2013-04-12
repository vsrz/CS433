#include<stdlib.h>
#include<stdio.h>
#include<sched.h>
#include<pthread.h>
#include<semaphore.h>

void *tobacco_wait();
void *paper_wait();
void *matches_wait();
void *agent_wait();

sem_t tobacco,paper,matches,agent;

int main() {
  pthread_t tagent,ttobacco,tpaper,tmatches;

  /* initalize semaphores */
  sem_init(&agent,0,0);
  sem_init(&tobacco,0,0);

  /* start the threads */
  pthread_create(&tagent,NULL,agent_wait,NULL);
  pthread_create(&ttobacco,NULL,tobacco_wait,NULL);
  pthread_create(&tpaper,NULL,paper_wait,NULL);
  pthread_create(&tmatches,NULL,matches_wait,NULL);

  /* Cleanup */
  pthread_exit(NULL);
  sem_destroy(&agent);
  sem_destroy(&tobacco);
  sem_destroy(&paper);
  sem_destroy(&matches);
  return(0);
}

void *agent_wait(){
  int x=0;
  while(1){
    sched_yield();
    printf("Agent placed PAPER on the table.\n");
    printf("Agent placed MATCHES on the table.\n");
    sched_yield();
    sem_post(&tobacco);
    printf("Agent placed MATCHES on the table.\n");
    printf("Agent placed TOBACCO on the table.\n");
    sched_yield();
    sem_post(&paper); 
    sem_wait(&agent);
    printf("Agent placed TOBACCO on the table.\n");
    printf("Agent placed PAPER on the table.\n");
    sched_yield();
    sem_post(&matches); 
    sched_yield();
    sem_wait(&agent);
    printf("\n");
    if(x++==5)exit(0);
  }
}

/* This smoker needs paper and matches */
void *tobacco_wait(){
  while(1){
    sched_yield();  
    sem_wait(&tobacco);
    printf("Smoker used item PAPER.\n");
    printf("Smoker used item MATCHES.\n");
    sleep(1);
    sem_post(&agent);
  }
}


/* This smoker needs tobacco and matches */
void *paper_wait(){
  while(1){
    sched_yield();  
    sem_wait(&paper);
    printf("Smoker used item MATCHES.\n");
    printf("Smoker used item TOBACCO.\n");
    sleep(1);
    sem_post(&agent);
  }
}

/* this smoker needs paper and tobacco */
void *matches_wait(){
  while(1){
    sched_yield();  
    sem_wait(&matches);
    printf("Smoker used item PAPER.\n");
    printf("Smoker used item TOBACCO.\n");
    sleep(1);
    sem_post(&agent);
  }
}
