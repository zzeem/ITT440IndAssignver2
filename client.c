#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

#define MAXLINE 512
#define LISTENQ 8

typedef struct sockaddr SO_AD;

int main (int argc, char **argv){
	int sockfd, n;
	char recvline [MAXLINE + 1];
	struct sockaddr_in serverAdd;
	int port;

	if(argc != 3){
		printf("run output file <ip> <port>\n");
	}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
		printf("Socket Error\n");
	}

	port = atoi(argv[2]);
	bzero(&serverAdd, sizeof(serverAdd));
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(port);

	if (inet_pton(AF_INET, argv[1], &serverAdd.sin_addr)<= 0){
		printf("Presentation error %s\n", argv[1]);
	}

	if (connect(sockfd, (SO_AD *) &serverAdd, sizeof(serverAdd))< 0){
		printf("Error.\n");
	}

	while ((n=read(sockfd, recvline, MAXLINE))> 0){
	recvline[n] =0;

	if (fputs(recvline, stdout) == EOF){
		printf("fputs error.\n");
		}
	}

	if (n <0){
		printf("Not found.\n");
	}
}
