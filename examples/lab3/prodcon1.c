#include <stdio.h>
#include <sched.h>
#include <pthread.h>

#define NBUFF   100

int nitems;		/* read-only by producer and consumer */
int buff[NBUFF];	/* shared data area */

/* Function prototypes */

void *produce( void *arg);
void *consume(void *arg);

void *produce( void *arg)
{     

	int	i;

      	for (i = 0; i < nitems; i++) {
		buff[i % NBUFF] = i; 	/* store i into circular buffer */
		if (i == (nitems/2))
			sched_yield();
      	}

	return(NULL);
}

void *consume(void *arg)
{     

	int	i;

	for (i = 0; i < nitems; i++) {	
		printf("buff[%d] = %d \n", i, buff[i % NBUFF]);	
      	}

	return(NULL);
}

int main(int argc, char *argv[]) 
{

	pthread_t tid1,tid2;

	if (argc != 2)
	{
		printf("Usage: %s <#items> \n", argv[0]);
		exit(1);
	}

	nitems = atoi(argv[1]);

	/* Create one producer thread and on consumer thread */
      	pthread_create(&tid1, NULL, &produce, NULL);
      	pthread_create(&tid2, NULL, &consume, NULL);

	/* wait for the two threads */	

	 pthread_join(tid1, NULL);
	 pthread_join(tid2, NULL);

	exit(0);
}
