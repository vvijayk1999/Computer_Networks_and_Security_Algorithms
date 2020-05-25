#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
int main(int argc,char *argv[])
{
int sockfd,portno,n;
struct sockaddr_in seradd;
char buffer[4096],*serip;
if(argc<4)
{
fprintf(stderr,"usage %s serverip filename port",argv[0]);
exit(0);
}
serip=argv[1];
portno=atoi(argv[3]);
/*---- Create the socket. The three arguments are: ----*/
/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
{
perror("\n Error in creating socket.\n");
perror("\n Client on line.");
}
bzero((char *)&seradd,sizeof(seradd));
 / *---- Configure settings of the server address struct ----*/
 /* Address family = Internet */
seradd.sin_family=AF_INET;
/* Set IP address */
seradd.sin_addr.s_addr=inet_addr(serip);
/* Set port number, using htons function to use proper byte order */
seradd.sin_port=htons(portno);
/*---- Connect the socket to the server using the address struct ----*/
if(connect(sockfd,(struct sockaddr *)&seradd,sizeof(seradd))<0)
{
perror("\n Error in connection setup \n");
write(sockfd,argv[2],strlen(argv[2])+1);
bzero(buffer,4096);
}
n=read(sockfd,buffer,4096);
if(n<=0)
{
perror("\n File not found");
exit(0);
}
write (1,buffer,n);
}
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/fcntl.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
int fd,sockfd,newsockfd,clilen,portno,n;
struct sockaddr_in seradd,cliadd;
char buffer[4096];
if(argc<2)
{
fprintf(stderr,"\n\n No port\n");
exit(1);
}
portno=atoi(argv[1]);
/*---- Create the socket. The three arguments are: ----*/
 /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
{
	 error("\n error opening socket.\n");
bzero((char *)&seradd,sizeof(seradd));
 /*---- Configure settings of the server address struct ----*/
 /* Address family = Internet */
seradd.sin_family=AF_INET;
seradd.sin_addr.s_addr=(htonl)INADDR_ANY;
/* Set port number, using htons function to use proper byte order */
seradd.sin_port=htons(portno);
/*---- Bind the address struct to the socket ----*/
if(bind(sockfd,(struct sockaddr *)&seradd,sizeof(seradd))<0)
{
perror("\n IP addr cannt bind");
/*---- Listen on the socket, with 5 max connection requests queued ----*/
listen(sockfd,5);
clilen=sizeof(cliadd);
printf("\n Server waiting for clint request");
while(1)
{
/*---- Accept call creates a new socket for the incoming connection ----*/
newsockfd=accept(sockfd,(struct sockaddr *)&cliadd,&clilen);
if(newsockfd<0)
perror("\n Server cannot accept connection request ");
bzero(buffer,4096);
read(newsockfd,buffer,4096);
fd=open(buffer,O_RDONLY);
if(fd<0)
{
perror("\n File doesnot exist");
while(1)
{
n=read(fd,buffer,4096);
if(n<=0)
exit(0);
write(newsockfd,buffer,n);
printf("\n File transfer completet\n");
}
close(fd);
close(newsockfd);
}
return 0;
