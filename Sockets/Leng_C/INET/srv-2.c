/********************************************************
 *
 *
 ********************************************************/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <resolv.h>
#include <errno.h>
#include <stdio.h>

#define PUERTO    3000         // Puerto
#define DIR_SERV  "127.0.0.1"  // Host local
#define TAM_MAX   1024

void error(char *msg)
{
   perror(msg);
   //exit(1);
   exit(errno); //este devuelve el error correspondiente 
}

int main()
{   
 unsigned int sock, new_sock, val, opt=1;
 struct sockaddr_in address; 
 char buffer[TAM_MAX];
 socklen_t length = sizeof(address);

    // 1. Crear socket 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0))<0 ){
        error("Socket");
    }
    printf("Socket creado.\n");

    // 2. Inicializacion de datos

    // if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    //     error("setsockopt");
    // }

    //bzero(&address, length);
    //memset(&address, 0, length);

    address.sin_family = AF_INET;
    address.sin_port = htons(PUERTO);

    address.sin_addr.s_addr = INADDR_ANY;
    //address.sin_addr.s_addr = inet_addr(DIR_SERV);
    //  Conversion de direcciones
    // if (inet_aton(DIR_SERV, &addres.sin_addr.s_addr)==0){
    //     error(DIR_SERV);
    // }
    printf("Data initialized.\n");

    if (bind(sock, (struct sockaddr*) &address, sizeof(address)) < 0) {
        error("bind failed");
    }
    printf("Binded.\n");

    if (listen(sock, 3) < 0) {
        error("listen");
    }
    printf("Listen until 3 conections.\n");

    if ((new_sock = accept(sock, (struct sockaddr*) &address, &length)) < 0) {
        error("accept");
    }
    printf("Accept one conection.\n");

    // 5. Recibir mensaje
    bzero(buffer, TAM_MAX);
    val = read(new_sock, buffer, TAM_MAX - 1); // subtract 1 for the null
    printf("Read: %s\n", buffer);

    close(new_sock);
    close(sock);
 
    return 0;
}
