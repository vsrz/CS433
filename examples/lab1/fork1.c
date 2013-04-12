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
    else if (pid == 0) {
        msg = "This is the child";
        n = 5;
    }
    else {
        msg = "This is the parent";
        n = 3;
    }

    for ( ; n > 0; n--) {
        printf("%s \n", msg);
        sleep(1);
    }

    exit (EXIT_SUCCESS);

} 
        
