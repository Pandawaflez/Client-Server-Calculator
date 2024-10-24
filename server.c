//server.c
/* A simple server in the internet domain using TCP
   Provides a simple prefix calculator to client
   The port number is passed as an argument.
   compile it and the server using the make file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "calculator.h"

//error function.  Called in main when things go wrong
void error(const char *msg)
{
   perror(msg);
   exit(1);
}

//main function
//evaluates a prefix integer expression for a client
//requires user to pass the server's port as a command line argument
int main(int argc, char *argv[])
{
   int sockfd, newsockfd, portno;
   socklen_t clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n;
   if (argc < 2) {
      fprintf(stderr,"ERROR, no port provided\n");
      exit(1);
   }
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0){
      error("ERROR opening socket");
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = atoi(argv[1]);
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      error("ERROR on binding");
   }
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
   if (newsockfd < 0) {
      error("ERROR on accept");
   }
   bzero(buffer,256);
   n = read(newsockfd,buffer,255);
   if (n < 0) {
      error("ERROR reading from socket");
   }
   printf("Here is the message: %s\n",buffer);
   char* ret = calculator( buffer );
   n = write(newsockfd,ret,18);
   if (n < 0){ 
      error("ERROR writing to socket");
   } else {
      printf("Returned message: %s\n", ret);
   }
   printf("Closing Socket");
   close(newsockfd);
   close(sockfd);
   printf("Server Shutting Down");
   return 0; 
}
