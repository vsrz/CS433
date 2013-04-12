#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
  char buffer[BUFSIZ-1];
  char sfile[128];
  int ndata;
  int fd[2];
  FILE* pF;
  if (pipe(fd) == -1) {
    perror("pipe failed");
    exit(EXIT_FAILURE);
  }
  puts("Please enter a filename: ");
  gets(sfile);
  switch (fork()) {
    case -1:                                /* Handle error */
    break;
  case 0:                                   /* Child - reads from pipe */
    ndata=read(fd[0],buffer,BUFSIZ);        /* Get data from pipe */
    printf("Opening %s for reading.\n",buffer);
    if((pF=fopen(buffer,"r"))==NULL)
      ndata=write(fd[1],"Error reading file...",21);
    else {
      fgets(buffer,sizeof(buffer),pF);
      ndata=write(fd[1],buffer,strlen(buffer));
      fclose(pF);
    }
    exit(EXIT_SUCCESS);
  default:  			            /* Parent - writes to pipe */
    ndata=write(fd[1],sfile,strlen(sfile));  /* ndata (num of bytes written) */
    memset(buffer,'\0',sizeof(buffer));
    sleep(1);
    ndata=read(fd[0],buffer,BUFSIZ);        /* Get data from pipe */
    printf("%s\n",buffer);
    close(fd[0]);
    close(fd[1]);                           /* Child will see EOF */
    exit(EXIT_SUCCESS);
  }
  return 0;
}

