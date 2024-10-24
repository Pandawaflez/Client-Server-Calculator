//client.c
//A simple client program using an internet socket to communicate with a server
//allows user to access a calculator server which evaluates a 
//	single integer expression in prefix notation
//compile using the attached make file, "calculator.mk"
//Pass the hostname and server port as arguments in the command line

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

//error function
//called in main when something goes wrong
void error(const char *msg)
{
   perror(msg);
   exit(0);
}

//main function
//User must pass hostname and port of the server as arguments in the command line
//allows user to send a prefix integer expression to the server, and recieve the evaluated expression
int main(int argc, char *argv[])
{
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;

   char buffer[256];
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
   portno = atoi(argv[2]);
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      error("ERROR opening socket");
   }
   server = gethostbyname(argv[1]);
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
   serv_addr.sin_port = htons(portno);
   if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
      error("ERROR connecting");
   }
   printf("Please an expression in postfix notation: \n");
   printf("(Ex: \"+ 3 4\" )\n");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   n = write(sockfd,buffer,strlen(buffer));
   if (n < 0) {
      error("ERROR writing to socket");
   }
   bzero(buffer,256);
   n = read(sockfd,buffer,255);
   if (n < 0) {
      error("ERROR reading from socket");
   }
   printf("%s\n",buffer);
   close(sockfd);
   return 0;
}
