#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *thread_function(void *arg);

char buf[BUFSIZ];

int main()
{

	int		status;
	pthread_t	tid;	
	void		*result;


	status = pthread_create(&tid, NULL, thread_function, NULL);
	if (status != 0)
	{
		perror("Thread create error");
		exit(EXIT_FAILURE);
	}

	printf("Enter some text ('end' to exit)\n");
	while (strncmp("end", buf, 3) != 0)
	{
		fgets(buf, BUFSIZ, stdin);
	}

	status = pthread_join(tid, &result);
	if (status != 0)
	{
		perror("Thread join error");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{

	while (strncmp("end", buf, 3) != 0)
	{
		printf("You input %d chars \n", strlen(buf) -1);
	}

	pthread_exit(NULL);
}

