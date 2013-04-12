#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int shmread (int shmid)
{

    int   i;
    struct shmid_ds  buf;
    unsigned char c;
    unsigned char *ptr;
  
    ptr = shmat (shmid, NULL, 0);
    if (ptr == NULL)
        return(-1);

    if (shmctl(shmid, IPC_STAT, &buf) == -1)
        return(-1);

    for (i = 0; i < buf.shm_segsz; i++) {
        if (( c = *ptr++) != (i % 256)) {
            printf("ptr[%d] = %d \n", i, c);
            return(-1);
        }
    }

    return(0);

}

