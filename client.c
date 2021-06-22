
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "echo.h"

void dg_cli(FILE *fp,int sockfd,struct sockaddr *servaddr,size_t servlen)
{
	int n;
	char sendline[MAXLINE],recvline[MAXLINE+1];
	socklen_t len;
	struct sockaddr *preply_addr;

	preply_addr = malloc(servlen);

	while(fgets(sendline,MAXLINE,fp) != NULL){
		if (sendto(sockfd,sendline,strlen(sendline),0,servaddr,len) == -1){
			perror("sendto");
			continue;
		}

		len = servlen;
		n = recvfrom(sockfd,recvline,MAXLINE,0,preply_addr,&len);
		if (len != servlen || memcmp(servaddr,preply_addr,len) != 0){
			fprintf(stderr,"reply from (ignored)\n");
			continue;
		}

		recvline[n] = '\0';
		if (fputs(recvline,stdout) == -1){
			perror("fputs");
			continue;
		}
	}
}

int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;
	
	if (argc!=2 || strcmp(argv[1],"--help")==0){
		fprintf(stderr,"Usage: %s ip-address\n",argv[0]);
		return 1;
	}

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if (inet_pton(AF_INET,argv[1],&servaddr.sin_addr) == -1){
		perror("inet_pton");
		return 1;
	}

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd == -1){
		perror("socket");
		return 1;
	}

	dg_cli(stdin,sockfd,(struct sockaddr *) &servaddr,sizeof(servaddr));
	exit(0);
}
