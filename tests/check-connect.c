#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <assert.h>
#include <string.h>
#include "cbfi.h"

int main(int argc, char *argv[]) {
   int sockfd, portno;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   int x,y;
	
   portno = 80;  // port number
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      printf("ERROR opening socket");
   }
	
   server = gethostbyname("google.com"); // hostname
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   x = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   printf("%d\n",x);
   if(x != 0){
      printf("connect 1 fail\n");
   }
   y = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   printf("%d\n",y);
   if(y != 0){
      printf("connect 2 fail\n");
   }
}