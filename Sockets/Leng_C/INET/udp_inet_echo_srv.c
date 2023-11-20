/********************************************************
 *
 * Func.: Server que usa sockets.
 *   Tipo:    SOCK_DGRAM
 *   Dominio: AF_INET
 *
 *   Compile
 *        $ gcc -o udp_inet_echo_srv udp_inet_echo_srv.c
 *   Verify
 *        $ netstat -p udp tcp -f inet unix
 *   Pruebas avanzadas
 *    Asignar dos direcciones diferentes y enviar msg diff.
 ********************************************************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <strings.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>

#define PUERTO    3000         // Puerto
#define DIR_SERV  "127.0.0.1"  // Host local
#define TAM_MAX   1024

void error(char *msg)
{
   //fprintf(stderr, "ERROR creating socket.\n");
   perror(msg);
   exit(1);
}

int main(int argc, char *argv[])
{
  unsigned int sock, srv_length, clt_length, n;
  struct sockaddr_in server;
  struct sockaddr_in client;
  char buffer[TAM_MAX];
   
     // 1. Crear socket
     sock=socket(AF_INET, SOCK_DGRAM, 0); // IPPROTO_UDP en lugar de 0
     if (sock < 0){
        error("ERROR creating socket");
     }
     printf("Socket creado.\n");

     // 2. Estructuras de datos
     srv_length = sizeof(server);
     clt_length = sizeof(client);

     // bzero(&server, length);
     memset(&server, 0, srv_length);
     memset(&client, 0, clt_length);

     server.sin_addr.s_addr = inet_addr(DIR_SERV);
     //server.sin_addr.s_addr = INADDR_ANY; 
     server.sin_port        = htons(PUERTO);
     server.sin_family      = AF_INET;
     printf("Datos inicializados.\n");

     // 3. Enlazar socket a Direccion y Puerto
     if (bind(sock, (struct sockaddr *)&server, srv_length)<0) {
         error("Binding");
     }
     printf("Bindig realizado.\n");

     printf("Starting server ...\n");
     fflush(stdout);

     while (1) {
         n = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &client, &clt_length);
         if (n < 0){
            error("recvfrom");
         }

         printf("  Received message from IP: %s and port: %i \n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
         printf("  Received a message: %s \n", buffer);
         //printf("%s %d", buffer, n);
         fflush(stdout);

         // n = sendto(sock, "Message\n", 17, 0, (struct sockaddr *) &client, clt_length);
         // if (n  < 0){
         //    error("sendto");
         // }
     }

 }
