#include <stdio.h>
#include <stdlib.h>

#include "shm.h"


int main (int argc, char *argv[])
{

    char   *pathname;
    int    shmid;
    size_t length;

    if (argc != 3) {
        printf("Usage: shmmain <pathname> <length> \n");
        exit(EXIT_FAILURE);
    }

    pathname = argv[1];
    length = atoi(argv[2]);
    
    shmid = shmcreate(pathname, length);
    if (shmid == -1) {
        printf("Error unable to create shared memory segment \n");
        exit(EXIT_FAILURE);
    }

    if (shmwrite(shmid) == -1) {
        printf("Error writing to shared memory\n");
        exit(EXIT_FAILURE);
    }

    if (shmread(shmid) == -1) {
        printf("Error reading from shared memory \n");
        exit(EXIT_FAILURE);
    }

    if (shmrmid(shmid) == -1) {
        printf("Error removing shared memory \n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

}


