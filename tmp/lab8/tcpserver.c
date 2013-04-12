#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define MAXLINE	256


void sig_handler(int signal);
void read_n_reply(int socket_fd);

const int backlog = 4;


int main(int argc, char *argv[])
{

	int	listenfd, connfd;
	pid_t	childpid;
	int     clilen;
	struct 	sockaddr_in cliaddr, servaddr;

	if (argc != 3) {
		printf("Usage: tcpserver <address> <port> \n");
		exit(-1);
	}

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd == -1)
	{
		perror("socket error");
		exit(-1);
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family 	   = AF_INET;
	servaddr.sin_addr.s_addr   = inet_addr(argv[1]);
	servaddr.sin_port          = htons(atoi(argv[2]));

	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
		perror("bind error");

	}
	

	if (listen(listenfd, backlog) == -1) {
		perror("listen error");
		exit(-1);
	}

	
	signal(SIGCHLD, sig_handler);

	while (1) {
		clilen = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0 ) {
			if (errno == EINTR)
				continue;
			else {
				perror("aceppt error");
				exit(-1);
			}
		}
		if ((childpid = fork()) == 0) {
			close(listenfd);
			read_n_reply(connfd);
			exit(0);
		}
		close(connfd);
	}
}

void read_n_reply(int socket_fd)
{

	int	n;
	time_t  tnow;
        char    *ptime;
	FILE    *fp;
	char	line[MAXLINE];

	n = read(socket_fd, line, MAXLINE);
	printf("Reading, %s\n",line);
	if((fp=fopen(line,"r"))==NULL){
		strcpy(line,"Error reading file");
		send(socket_fd,line,strlen(line),0);
	}else{
		printf("Client has requested %s\n",line);
		while(fgets(line,1000,fp)){
			send(socket_fd,line,strlen(line),0);
		}
		strcpy(line,"\n");
		send(socket_fd,line,strlen(line),0);
	}
}


void sig_handler(int signal)
{

	pid_t	pid;
	int	status;


	while ((pid = waitpid(-1, &status, WNOHANG)) > 0) 
		printf("child %d terminated \n", pid);

	return;

}

