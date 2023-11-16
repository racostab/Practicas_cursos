/********************************************************
 *
 * Func.: Cliente que hace Echo con sockets.
 *   Tipo:     SOCK_STREAM
 *   Dominio:  AF_INET
 *
 ********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>

#define PUERTO    3000         // Puerto
#define DIR_SERV  "127.0.0.1"  // Host local
#define TAM_MAX   1024

int main()
{   
 int desc_socket;
 struct sockaddr_in dest; //dest tomara valores para la familia de conectores y puertos
 char bufer[TAM_MAX];

    // 1. Crear socket 
    if ((desc_socket=socket(AF_INET,SOCK_STREAM,0))<0 ){
        perror("Socket");
        exit(errno);//este devuelve el error correspondiente para el resultado de la conexion
    }

    // 2. Inicializacion de datos
    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(PUERTO);

    // 3. Conversion de
    if (inet_aton(DIR_SERV,&dest.sin_addr.s_addr)==0){
        perror(DIR_SERV);
        exit(errno);//este devuelve el error correspondiente para el resultado de la conexion
    }

    // 4. Conecta al servidor
    if (connect(desc_socket,(struct sockaddr*)&dest,sizeof(dest))!=0 ){
        perror("Connect ");
        exit(errno);
    }

    // 5. Recibir mensaje
    bzero(bufer,TAM_MAX);
    recv(desc_socket,bufer,sizeof(bufer),0);
    printf("%s", bufer);

    // 6. Cierra conexion
    close(desc_socket);
 
    return 0;
}
