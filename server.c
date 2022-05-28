#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define MAXLINE 512
#define LISTENQ 8

typedef struct sockaddr SO_AD;

int main(int argc, char **argv){
	int listenfd, connfd;
	struct sockaddr_in serverAdd, clientAdd;
	char buff [MAXLINE];
	time_t ticks;
	int port;
	socklen_t len;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	port = atoi(argv[1]);
	bzero(&serverAdd, sizeof(serverAdd));
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAdd.sin_port = htons(port);

	bind(listenfd, (SO_AD *) &serverAdd, sizeof(serverAdd));
	printf("Listening at port %d\n", port);
	listen(listenfd, LISTENQ);

	for ( ; ; ) {
		len = sizeof(clientAdd);
		connfd = accept(listenfd, (SO_AD *) &clientAdd, &len);
		printf("Listened to %s from port %d\n", inet_ntop(AF_INET,&clientAdd.sin_addr.s_addr, buff, sizeof(buff)), ntohs(clientAdd.sin_port));
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));
		close(connfd);
	}

}
