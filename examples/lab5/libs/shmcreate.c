#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int shmcreate (char *pathname, size_t length)
{

    int    oflag;

    oflag = 0644 | IPC_CREAT;

    return(shmget(ftok(pathname, 1), length, oflag));

}


