#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>


void sig_handler(int sig)
{

    printf("Got the signal %d \n", sig);
    (void) signal (SIGINT, SIG_DFL);

}

int main (void)
{

    /* install the signal handler */
    (void) signal(SIGINT, sig_handler);

    while (1) {
        printf("Program is running ... \n");
        sleep(1);
    }
}
 
