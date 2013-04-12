#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

	int msqid;               

	if (argc != 2)
	{
		printf("Usage: msgctrl <msgqid> \n");
		exit(1);
	}
	msqid = atoi(argv[1]);

	if (msgctl(msqid, IPC_RMID, NULL) == -1)
	{
		perror("msgctl error");
		exit(1);
	}
	
	exit(0);

}

