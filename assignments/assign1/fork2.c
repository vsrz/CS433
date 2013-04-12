/* T. Springer Spring 2008  *
 * Homework 01 - Q2         *
 * Jeremy Villegas          *
 * February 09, 2008        */

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>

static int alrm = 0;
struct timeval f,s;

void sig_handler(int sig){
  alrm++;
  //(void)signal(SIGINT,sig_handler); 
}

int main(void){
  pid_t pid=fork();                     /* fork a child */
  int t=0;                              /* time elapsed */
  pid<0?exit(EXIT_FAILURE):NULL;        /* check if pid valid */
  if(pid==0){                           /* child process */
    printf("running child process...\n"); /* display notification */
    (void)signal(SIGALRM,sig_handler);  /* Install sig handler */
    gettimeofday(&f,NULL);              /* get first time */
    printf("wait for sig...\n");        /* display notification */
    pause();				/* wait for the sig */
    alrm?gettimeofday(&s,NULL):alrm;    /* Get second time */
    t=(s.tv_usec)-(f.tv_usec);          /* Calculate numeros */         
    printf("Time Diff : %dus\n",t/10);  /* Spit out time */
    exit(EXIT_SUCCESS);
  } else kill(pid,SIGALRM);
  wait(NULL);   
  /* Waiting for the signal */
  exit(EXIT_SUCCESS);
}

