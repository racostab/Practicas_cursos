/********************************************************
 *
 *
 ********************************************************/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <resolv.h>
#include <string.h>
#include <unistd.h>
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
 int sock, length;
 struct sockaddr_in address;
 char buffer[TAM_MAX];

    // 1. Crear socket 
    if ((sock=socket(AF_INET, SOCK_STREAM, 0))<0 ){
        error("Socket");
    }
    printf("Socket creado.\n");

    // 2. Inicializacion de datos
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PUERTO);

    // Conversion
    //address.sin_addr.s_addr = inet_addr(DIR_SERV);
    // if (inet_aton(DIR_SERV, &address.sin_addr.s_addr)==0){
    //     error(DIR_SERV);
    // }

    if (inet_pton(AF_INET, DIR_SERV, &address.sin_addr) <= 0) {
        error(DIR_SERV);
    }
    printf("Data initialized.\n");

    // 3. Conecta al servidor
    if (connect(sock,(struct sockaddr*)&address, sizeof(address))!=0 ){
        error("Connect ");
    }
    printf("Connected.\n");

    // 4. Leer mensaje
    bzero(buffer, TAM_MAX);
    printf("Message: ");
    scanf("%s\n", buffer);

    // 6. Enviar mensaje
    send(sock, buffer, strlen(buffer), 0);
    printf("Msg sended !");

    // 7. Cierra conexion
    close(sock);
 
    return 0;
}
