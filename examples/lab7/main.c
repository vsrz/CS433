#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main(int argc, char *argv[])
{

    int   value;

    if (argc != 2) {
        printf("Usage: %s <value> \n", argv[0]);
        exit(-1);
    }

    value = atoi(argv[1]);

    printf("Value %d: square %d cube %d \n", 
            value, sqr(value), cube(value));

    exit(0);
}

