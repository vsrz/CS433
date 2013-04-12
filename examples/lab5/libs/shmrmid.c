#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int shmrmid (int shmid)
{

    return(shmctl(shmid, IPC_RMID, NULL));


}


