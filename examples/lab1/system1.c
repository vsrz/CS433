#include <stdio.h>
#include <stdlib.h>

#define STRLEN    (80)

int main (int argc, char *argv[])
{

    /* check for correct number of command-line parameters */

    if (argc < 2) {
        printf("Usage:: %s <syscall> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Make system call */
    if (system(argv[1]) == -1) {
        printf("Error - invalid system call (%s) \n", argv[1]);
        exit(EXIT_FAILURE);
    }

    
    exit(EXIT_SUCCESS);

}



