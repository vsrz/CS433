#ifdef _SHM_H

int shmcreate(char *filename, size_t length);
int shmrmid(int shmid);
int shmread(int shmid);
int shmwrite(int shmid);

#endif
