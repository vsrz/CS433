#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>


static int   alarm_fired = 0;

void sig_handler(int sig)
{
    alarm_fired = 1;
}

int main (void)
{

    pid_t    pid;

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    /* Child process sends the signal */
    if (pid == 0) {
        sleep(5);
        kill(getppid(), SIGALRM);
        exit(EXIT_SUCCESS);
    }
    
    /* install the signal handler */
    (void) signal(SIGALRM, sig_handler);

    /* Waiting for the signal */
    printf("Waiting for the alarm to fire ... \n");
    pause();

    if (alarm_fired)
        printf("Alarm fired ! \n");

    exit(EXIT_SUCCESS);

}
 
