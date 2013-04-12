#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main (int argc, char *argv[])
{

    int    shmid;

    if (argc != 2) {
        printf("Usage: shmrmid <shmid> \n");
        exit(EXIT_FAILURE);
    }
    
    shmid = atoi(argv[1]);
    shmctl(shmid, IPC_RMID, NULL);

    exit (EXIT_SUCCESS);

}


