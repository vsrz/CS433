#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *calc_factorial(void *arg);

int main(int argc, char *argv[])
{

     pthread_t    tid;
     int          val;
     int          result;

     if (argc != 2) {
        printf("Usage: %s <factor> \n", argv[0]);
        exit(EXIT_FAILURE);
     }

     val = atoi(argv[1]);

     /* Create the thread to calculate factorial */
     if (pthread_create(&tid, NULL, calc_factorial, (void *)&val) != 0) {
        perror("Thread create failed");
        exit(EXIT_FAILURE);
     }

     /* Wait for thread to calculate the factorial */
     if (pthread_join(tid, (void *)&result) != 0) {
         perror("Thread join failed");
         exit(EXIT_FAILURE);
     }

     printf("%d factorial is %d \n", val, result);

     exit(EXIT_SUCCESS);

}


void *calc_factorial(void *arg)
{

    int    i, n;
    int    factorial = 1;

    n = *((int *)arg);

    /* Calculate the factorial */
    for (i = 1; i < n; i++) {
        factorial += factorial * i;
    }

    return((void *)factorial);

}

