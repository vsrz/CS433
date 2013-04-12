/* T. Springer Spring 2008  *
 * Homework 01 - Q3         *
 * Jeremy Villegas          *
 * February 09, 2008        */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *fib(void*);
unsigned int f[50],nth;

int main(int argc,char* argv[]){
  pthread_t tid;                                                    /* thread ID */
  int n=0;                                                          /* disp. counter */
  argc<2?exit(EXIT_FAILURE):NULL;                                   /* check for arg */
  nth=atoi(argv[1]);                                                /* convert to int */
  nth>47||nth<0?exit(EXIT_FAILURE):nth;                             /* stay within bounds */
  if(pthread_create(&tid,NULL,fib,(void*)nth)) exit(EXIT_FAILURE);  /* Spawn thread */
  if(pthread_join(tid,NULL)) exit(EXIT_FAILURE);                    /* Rejoin */
  while(n<nth)printf("%d ",f[n++]);                                 /* print it out */
  printf("\n\n");                                                   /* clean it up  */
  return(0);
}

/* Calculate fibonacci seq to the nth place*/
void *fib(void *a){
  int n=1;
  f[0]=0;f[1]=1;                          /* first 2 values of fib seq */
  while(n++<=nth+2)f[n]=f[n-2]+f[n-1];    /* add 2 back, then the last one */ 
  pthread_exit(0);                        /* Pass back */
}

