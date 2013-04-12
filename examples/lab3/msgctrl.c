#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

	int msqid;               
	struct msqid_ds info;

	if (argc != 2)
	{
		printf("Usage: msgctrl <msgqid> \n");
		exit(1);
	}
	msqid = atoi(argv[1]);

	if (msgctl(msqid, IPC_STAT, &info) == -1)
	{
		perror("msgctl error");
		exit(1);
	}
	
	printf("read-write: %03o, cbytes = %lu, qnum = %lu, qbytes = %lu \n",
		info.msg_perm.mode & 0777, info.msg_cbytes,
		info.msg_qnum, info.msg_qbytes);

	system("ipcs -q");

	exit(0);

}

