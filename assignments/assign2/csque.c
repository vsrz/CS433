#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX_MSG_LEN (4096)
#define MSG_KEY_ID  (7777)
#define MSG_KEY_ID2 (7778)
struct msgbuf{
  long mtype; /* msgtype */
  char mtext[MAX_MSG_LEN]; /* message data */
};

int main (int argc, char *argv[]) {
  char buffer[BUFSIZ-1],sfile[254],s[BUFSIZ-1];
  int nbytes;
  int msqid,fd[2],n,msqid2;
  size_t len;
  struct msgbuf buf;
  key_t key=MSG_KEY_ID,key2=MSG_KEY_ID2;
  FILE *pf=NULL;
  int oflag=0664 | IPC_CREAT;
  msqid=msgget(key,oflag);
  msqid2=msgget(key2,oflag);
  printf("Please enter a filename: \n");
  gets(sfile);   /* Had to use gets, fgets/read both added a <CR> at the end */
  len=sizeof(long)+strlen(sfile);
  buf.mtype=9999;
  strcpy(buf.mtext,sfile);
  if(msqid==-1){
    printf("Message queue error...\n");
    fflush(stdout);
    exit(1);
  }
  switch(fork()){
    case -1:                                /* Handle error */
    break;
  case 0:                                   /* Child - reads from pipe */
    printf("Opening %s for reading.\n",sfile);
    sleep(1);
    if(n=msgrcv(msqid,buf.mtext,MAX_MSG_LEN,0,0)<0){
      perror("msgrcv error");
      exit(1);
    }
    if((pf=fopen(buf.mtext,"r"))==NULL){
      strcpy(buf.mtext,"File not found");
      if(msgsnd(msqid2,buf.mtext,len,0)<0){
        perror("msgsend");
        exit(1);
      }
    } else {
      while(!eof()) fgets(buf.mtext,sizeof(buf.mtext),pf);
      fclose(pf);
      if(msgsnd(msqid2,buf.mtext,len,0)<0){
        perror("msgsend");
        exit(1);
      }
    }
    exit(EXIT_SUCCESS);
  default:  			            /* Parent - writes to pipe */
    if(msgsnd(msqid,buf.mtext,len,0)<0)
      perror("msgsnd error");
    sleep(1);
    if(n=msgrcv(msqid2,buf.mtext,MAX_MSG_LEN,0,0)<0){
      perror("msgrcv");
      exit(1);
    }
    printf("msg: %s \n",buf.mtext);
    if(msgctl(msqid,IPC_RMID,NULL)<0){
      perror("msgremove");
      exit(1);
    }
    if(msgctl(msqid2,IPC_RMID,NULL)<0){
      perror("msgremove");
      exit(1);
    }
    exit(EXIT_SUCCESS);
  }
  return 0;
}

