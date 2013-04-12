/********************************************************************
*
* NAME:
*       shmwrite.c
*
* DESCRIPTION:
*
*       This program writes a random pattern 0,1,2, ..., 255
*	to a shared memory segment and then performs a checksum
*       on the data.
*
* MODIFICATION HISTORY:
*       DATE:           AUTHOR:         PR #:/DESCRIPTION
*       10/21/02        T. Springer     Original
*
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>

extern void src_init(void);
extern unsigned int src_compute(char *, int);

int main(int argc, char *argv[])
{

	int	i, id;
	struct  shmid_ds buf;
	unsigned int     crc;
	unsigned char	 *ptr;


	if (argc != 2)  {
	    printf("Usage: shmwrite <shmid> \n");
	    exit(EXIT_FAILURE);
	}

	id = atoi(argv[1]);                           

	ptr = shmat(id, NULL, 0);
	if (ptr == NULL) {
	    perror("shmat error");
	    exit(EXIT_FAILURE);
	}

	shmctl(id, IPC_STAT, &buf);

	for (i = 0; i < buf.shm_segsz - sizeof(crc); i++)
	    ptr[i] = rand() % 255;

	crc_init();
	crc = crc_compute(&ptr[0], buf.shm_segsz-sizeof(crc));

	memcpy((void *)&ptr[buf.shm_segsz-sizeof(crc)], (void *)&crc, sizeof(crc)); 

	exit(0);
}

