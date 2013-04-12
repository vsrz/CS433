#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main (void)
{

    pid_t  pid;
    char   *msg;
    int    n;
  
    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
       if (execlp("ps","ps","-ax", 0) == -1) {
           perror("execlp call failed");
           exit(EXIT_FAILURE);
       }
    }

    wait (NULL);

    exit(EXIT_SUCCESS);

}  

