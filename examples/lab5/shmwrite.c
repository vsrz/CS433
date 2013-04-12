#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main (int argc, char *argv[])
{

    int   shmid, i;
    struct shmid_ds  buf;
    unsigned char *ptr;
  

    if (argc != 2) {
        printf("Usage: shmwrite <shmid> \n");
        exit(EXIT_FAILURE);
    }

    ptr = shmat (shmid, NULL, 0);
    shmctl(shmid, IPC_STAT, &buf);

    for (i = 0; i < buf.shm_segsz; i++) {
        *ptr++ = i % 256;
    }

    exit(EXIT_SUCCESS);

}

