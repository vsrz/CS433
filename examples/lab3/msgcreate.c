#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[])
{

    extern int optind;

	int	c, oflag, mqid;
	key_t key;


	oflag = 0664 | IPC_CREAT;

	while ((c = getopt(argc, argv, "e")) != -1)
	{
		switch(c)
		{
			case 'e':
				oflag |= IPC_EXCL;
				break;
		}
	}

	if (optind != argc - 1)
	{
		printf("Usage: msgcreate [ -e ] <key> \n");
		exit(1);
	}

	key = atoi(argv[optind]);

	mqid = msgget(key, oflag);
	if (mqid == -1)
	{
		perror("msgget error");fflush(stdout);
		exit(1);
	}

	exit(0);

}

