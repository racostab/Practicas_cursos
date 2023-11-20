/********************************************************
 *
 * Func.: Cliente que usa sockets.
 *   Tipo:    SOCK_DGRAM
 *   Dominio: AF_INET
 *
 *   Compile
 *        $ gcc -o udp_inet_echo_clt udp_inet_echo_clt.c
 *        $ gcc -w  # Warnings
 *
 * Al capturar el mensaje introduzca espacios. Que pasa?
 ********************************************************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>

#define PUERTO    3000         // Puerto
#define DIR_SERV  "127.0.0.1"  // Host local
#define TAM_MAX   1024

void error(char *msg)
{
   perror(msg);
   exit(1);
}

int main(int argc, char *argv[])
{
 struct sockaddr_in server, client;
 unsigned int sock, clt_length, srv_length, n;
 struct hostent *hp;
 char buffer[TAM_MAX];
   
    // if (argc != 2) { 
    //    printf("Usage: server port\n");
    //    return(1);
    // }
    // port = htons(atoi(argv[2]));

    // 1. Crear socket
    sock= socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0){
       error("socket");
    }
    printf("Socket creado.\n");

    // 2. Obtener direccion IP
    server.sin_family = AF_INET;

    hp = gethostbyname("127.0.0.1"); // localhost
    //hp = gethostbyname(argv[1]);
    if (hp==0){
       error("Unknown host");
    }
    printf("Direccion.\n");

    // 3. Preparar estructuras de datos
    srv_length = sizeof(server);
    clt_length = sizeof(client);

    memset(&server, 0, srv_length);
    memset(&client, 0, clt_length);
    //bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PUERTO);
    server.sin_family = AF_INET;

    // 4. Leer mensaje del teclado
    printf("Enter the message: ");
    scanf("%s", buffer);
    //bzero(buffer, TAM_MAX);
    //fgets(buffer, TAM_MAX, stdin);

    // 5. Enviar mensaje
    n=sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server, srv_length);
    if (n < 0){
       error("Sendto");
    }
    printf("Message sent: %s \n", buffer);
    fflush(stdout);

    // // 6. Leer mensaje
    // printf("Receiving message.\n");
    // fflush(stdout);
    // n = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&client, &length);
    // if (n < 0){
    //    error("recvfrom");
    // }
    // printf("Message received: %s \n", buffer);
    // fflush(stdout);

    return 0;
}

