
#include <unistd.h>
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
	int len;

	while(fgets(sendline,MAXLINE,fp) != NULL){
		if (sendto(sockfd,sendline,MAXLINE,0,(struct sockaddr *) servaddr,servlen) == -1){
			perror("sendto");
			continue;
		}

		n = recvfrom(sockfd,recvline,MAXLINE,0,NULL,NULL);
		if (n == -1){
			perror("recvfrom");
			return;
		}
		recvline[n] = '\0';
		if (fputs(recvline,stdout) == -1){
			perror("fputs");
			continue;
		}
	}
}

void dg_cli2(FILE *fp,int sockfd,struct sockaddr *servaddr,size_t servlen)
{
	int n;
	char sendline[MAXLINE],recvline[MAXLINE+1];

	if (connect(sockfd,(struct sockaddr *) servaddr,servlen) == -1){
		perror("connect");
		return;
	}

	while(fgets(sendline,MAXLINE,fp) != NULL){
		
		if (write(sockfd,sendline,strlen(sendline)) == -1){
			perror("write");
			continue;
		}

		n = read(sockfd,recvline,MAXLINE);
		if (n <= 0){
			perror("read");
			continue;
		}

		recvline[n] = '\0';
		if (fputs(recvline,stdout) == -1){
			perror("fputs");
			continue;
		}
	}
}

void dg_cli3(FILE *fp,int sockfd,struct sockaddr *servaddr,size_t servlen)
{
	int n;
	char sendline[MAXLINE],recvline[MAXLINE+1];

	/* UDP socket receive buffer size */
	n = 1024*100;
	if (setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&n,sizeof(n)) == -1){
		perror("setsockopt");
		return;
	}

	if (connect(sockfd,(struct sockaddr *) servaddr,servlen) == -1){
		perror("connect");
		return;
	}

	while(fgets(sendline,MAXLINE,fp) != NULL){
		
		if (write(sockfd,sendline,strlen(sendline)) == -1){
			perror("write");
			continue;
		}

		n = read(sockfd,recvline,MAXLINE);
		if (n <= 0){
			perror("read");
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

	dg_cli3(stdin,sockfd,(struct sockaddr *) &servaddr,sizeof(servaddr));
	exit(0);
}
