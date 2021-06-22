
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "echo.h"

void dg_echo(int sockfd,struct sockaddr *cliaddr,size_t size)
{
}

int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr,cliaddr;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd,(struct sockaddr *) &servaddr,sizeof(servaddr)) == -1){
		perror("bind");
		return 1;
	}
	
	dg_echo(sockfd,(struct sockaddr *) &cliaddr,sizeof(cliaddr));
}
