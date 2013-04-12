#include <stdio.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>

#define MAXLINE 256

void str_client(FILE *fp, int socket_fd);

int main(int argc, char *argv[])
{

	int	socket_fd;
	struct  sockaddr_in servaddr;

	if (argc != 3) {
		printf("Usage: tcpclient <address> <port> \n");
		exit(-1);
	}

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		perror("socket error");
		exit(-1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(atoi(argv[2]));

	if (connect(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
		perror("connect error");
		exit(-1);
	}

	str_client(stdin, socket_fd);

	exit(0);

}

void str_client(FILE *fp, int socket_fd)
{
	char	sndLine[MAXLINE];
	char	rcvLine[MAXLINE];
	int	n;

        printf("enter the path name: ");
	while (fgets(sndLine, MAXLINE, fp)==NULL){}

        /* send the filename */
	send(socket_fd,sndLine,strlen(sndLine),0);	

        /* wait for response from the server */
        n=recv(socket_fd,rcvLine,sizeof(rcvLine),0);
        while(n>0){
		write(1,rcvLine,n);
		n=recv(socket_fd,rcvLine,sizeof(rcvLine),0);
	}
/*
		write(socket_fd, sndLine, strlen(sndLine));

		if (read(socket_fd, rcvLine, MAXLINE) == 0) {
			printf("ERROR: server terminated \n");
			return;
		}

		fputs(rcvLine, stdout);
	}
*/
}

	
