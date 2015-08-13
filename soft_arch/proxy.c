#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <pthread.h>

#define myportno 43369
#define httpport 80
#define buf_size 100000

void* dostuff(void *);
int parse_request(char [],char [],char []);

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main()
{
	pthread_t *wthread;
	int sockfd, newsockfd, portno,rc;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = myportno;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	while(1) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) 
			error("ERROR on accept");
		printf("Creating Thread...\n");
		wthread=malloc(sizeof(pthread_t));
		rc=pthread_create(wthread, NULL, dostuff,(void *)&newsockfd );
		if(rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	return 0;
	close(sockfd);
}

void* dostuff (void *sck)
{
	int sock = *(int *)sck;
	int sockfd, portno=httpport;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int n=1;
	char buffer[buf_size],buffer2[buf_size],host[100],request[100];
	
	bzero(buffer,buf_size);
	n = read(sock,buffer,buf_size);
	if (n < 0)
		error("ERROR reading from socket");
	
	
	printf("Here is the message: %s\n",buffer);
	if(parse_request(buffer,host,request)==-1)
		return;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	
	server = gethostbyname(host);
	if (server == NULL) {
		bzero(buffer2,buf_size);
		strcpy(buffer2,"<h1>No Host Found...<h1>");
		n = write(sock,buffer2,buf_size);
		
		if (n < 0) 
			error("ERROR reading from socket");
		
		fprintf(stderr,"ERROR, no such host\n");
		printf("\nHost--- %s\n",host);
		printf("Request--- %s\n",request);
		printf("Exiting Thread with errors...\n");
		close(sock);
		close(sockfd);
		return;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
	
	n = write(sockfd,request,strlen(request));
	//n = write(sockfd, "GET /\n",  10);
	if (n < 0) 
		error("ERROR writing to socket");
	
	bzero(buffer2,buf_size);
	while(read(sockfd,buffer2,buf_size)) {
		if (n < 0) 
			error("ERROR reading from socket");
		//printf("\n%s\n",buffer2);
		n = write(sock,buffer2,buf_size);
		if (n < 0)
			error("ERROR writing to socket");
		bzero(buffer2,buf_size);
	}
	printf("\nHost--- %s\n",host);
	printf("Request--- %s\n",request);
	printf("Exiting Thread...\n");
	close(sock);
	close(sockfd);
	pthread_exit(NULL);
}

int parse_request(char buffer[],char host[],char request[])
{
	char *url,temp[100];
	int i=0;
	
	url=buffer;
	while(*url!='/')
		url++;
	
	
	url+=2;
	for(i=0;*url!='/';url++,i++)
		host[i]=*url;
	
	host[i]='\0';
	strcpy(host, "iitk.ac.in");
	strcpy(request,"GET ");
	
	for(i=4;*url!=' ';url++,i++)
		request[i]=*url;
	
	request[i]='\n';
	request[i+1]='\0';
	return 0;
}
