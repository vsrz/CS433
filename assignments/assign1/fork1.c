/* T. Springer Spring 2008  *
 * Homework 01 - Q1         *
 * Jeremy Villegas          *
 * February 09, 2008        */

#include<sys/time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char *argv[]) {
  if(argc<2) exit(1);
  char s[50]="cat ";
  strcat(s,argv[1]);
  printf("fork child process\n");
  pid_t pid=fork();   /* do a fork  */
  if(pid==0) system(s); /* print file */
  else {
    printf("wait for child process to finish...\n");
    wait(NULL);       /* wait indefinitely */
    printf("child process complete.\n");
    exit(0);
  }
  return 0;
}

