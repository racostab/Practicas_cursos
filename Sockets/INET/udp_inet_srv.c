/********************************************************
 *
 * Func.: Server que usa sockets.
 *   Tipo:    SOCK_DGRAM
 *   Dominio: AF_INET
 *
 ********************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int sock, length, fromlen, n;
  struct sockaddr_in server;
  struct sockaddr_in from;
  char buf[1024];
  int port = 5000; 
   
     sock=socket(AF_INET, SOCK_DGRAM, 0);
     if (sock < 0){
        perror("ERROR creating socket");
        //fprintf(stderr, "ERROR creating socket.\n");
        exit(0);
     }

     length = sizeof(server);
     bzero(&server,length);
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=INADDR_ANY;
     server.sin_port=htons( port );

     if (bind(sock,(struct sockaddr *)&server,length)<0) {
         perror("Binding");
         exit(0);
     }

     fromlen = sizeof(struct sockaddr_in);
     while (1) {
         n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
         if (n < 0){
            perror("recvfrom");
            exit(0);
         }
         write(1,"Received a datagram: ",21);
         write(1,buf,n);
         n = sendto(sock,"Got your message\n",17, 0, (struct sockaddr *)&from, fromlen);
         if (n  < 0){
            perror("sendto");
            exit(0);
         }
     }

 }
