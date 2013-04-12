#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>

struct msgbuf {
    long mtype;     /* message type, must be > 0 */
    char mtext[1];  /* message data */
};

int main(int argc, char *argv[])
{

	int msqid;               
	size_t len;
	int 	type;

    struct msgbuf *buf;
	
	if (argc != 4)
	{
		printf("Usage: %s <msgqid> <type> <msg> \n", argv[0]);
		exit(1);
	}
    
	msqid = atoi(argv[1]);
	type = atoi(argv[2]);
    len = sizeof(long) + strlen(argv[3]);

	buf = (struct msgbuf *)calloc(len, sizeof(char)); 
	buf->mtype = type;
    memcpy(buf->mtext, argv[3], strlen(argv[3]));
    

	if (msgsnd(msqid, buf, len, 0) == -1)
	{
		perror("msgsnd error");
		exit(1);
	}

	
	exit(0);

}

