#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <fcntl.h>

#define MAX_MSG_LEN	(4096)

struct msgbuf {
    long int mtype;
    char     mtext[1];
};

int main(int argc, char *argv[])
{

    struct msgbuf  *buf;
	int msqid;               
	int n;     
	
	if (argc != 2)
	{
		printf("Usage: msgctrl <msgqid> \n");
		exit(1);
	}
	msqid = atoi(argv[1]);

	buf = (struct msgbuf *)malloc(MAX_MSG_LEN);

	if ((n = msgrcv(msqid, buf, MAX_MSG_LEN, 0, 0)) == -1)
	{
		perror("msgrcv error");
		exit(1);
	}

	printf("read %d  bytes, type = %ld \n", n, buf->mtype);
    printf("msg = %s \n", buf->mtext);
	
	exit(0);

}

