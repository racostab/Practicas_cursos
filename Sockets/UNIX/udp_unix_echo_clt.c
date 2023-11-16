/********************************************************
 *
 * Func.: Cliente que hace Echo con sockets.
 *   Tipo:    SOCK_DGRAM
 *   Dominio: AF_UNIX
 *
 *   Compile
 *        $ gcc -o udp_unix_echo_clt udp_unix_echo_clt.c
 ********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define SOCKET_PATH_CLT    "./myclient"
#define SOCKET_PATH_SRV    "./myserver"

int main(int argc, char**argv)
{   
 int sock, len_srv, msg_len, index;
 struct sockaddr_un adr_clt, adr_srv;
 char *msg;

    // 1. Crear socket
    if( (sock=socket(AF_UNIX, SOCK_DGRAM,  0)) < 0 ){
        perror("socket: ");
        return(1);
    }

    // 2. Preparar estrucutras de datos
    bzero(&adr_clt, sizeof(adr_clt));
    adr_clt.sun_family = AF_UNIX;
    strcpy(adr_clt.sun_path, SOCKET_PATH_CLT);
   
    // 3. Enlazar el socket 
    if( bind(sock, (struct sockaddr*)&adr_clt, sizeof(adr_clt)) < 0 ){
        close(sock);
        perror("bind: ");
        return(2);
    }

    // 4. Preparar estructuras de datos 
    bzero(&adr_srv, sizeof(adr_srv));
    adr_srv.sun_family = AF_UNIX;
    strcpy(adr_srv.sun_path, SOCKET_PATH_SRV);
 
    if(argc>1)
      index = 1;
    else
      index = 0;

    msg = argv[index];
    msg_len = strlen(msg);

    // 5. Enviar 
    len_srv = sendto(sock, msg, msg_len, 0, (struct sockaddr *) &adr_srv, sizeof(adr_srv));

    // 6. Procesamiento del resultado
    if (len_srv<0) {
        perror("sendto");
        return(4);
    }else{
        printf("client : sent %d bytes\n", len_srv);
    }

    // 7. Liberar recursos
    unlink(SOCKET_PATH_CLT);
    close(sock);
    printf("Client done\n"); 

 return 0;
}
