#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main (int argc, char *argv[])
{

    int    c, id;
    int    oflag;
    char   *ptr;
    size_t length;

    oflag = 0644 | IPC_CREAT;
    while ((c = getopt(argc, argv, "e")) != -1) {
        switch (c) {
            case 'e':
               oflag |= IPC_EXCL;
               break;
        }
    }

    if (optind != argc - 2) {
        printf("Usage: shmget [-e] <pathname> <length>\n");
        exit(EXIT_FAILURE);
    }
    
    length = atoi(argv[optind + 1]);

    id = shmget(ftok(argv[optind], 1), length, oflag);
    ptr = shmat(id, NULL, 0);

    exit (EXIT_SUCCESS);

}


