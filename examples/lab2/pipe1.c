#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[])
{

    char    buffer[BUFSIZ-1];
    int     ndata;
    int     fd[2];

    if (argc != 2) {
        printf("Usage: %s <str> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    ndata = write(fd[1], argv[1], strlen(argv[1]));
    printf("Wrote %d bytes \n", ndata);

    memset(buffer, '\0', sizeof(buffer));
    ndata = read(fd[0], buffer, BUFSIZ);
    printf("Read %d bytes: %s \n", ndata, buffer);

    exit(EXIT_SUCCESS);

}

