#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int shmwrite (int shmid)
{

    int   i;
    struct shmid_ds  buf;
    unsigned char *ptr;
  
    ptr = shmat (shmid, NULL, 0);
    if (ptr == NULL)
        return(-1);

    if (shmctl(shmid, IPC_STAT, &buf) == -1)
        return(-1);

    for (i = 0; i < buf.shm_segsz; i++) {
        *ptr++ = i % 256;
    }

    return(0);

}

