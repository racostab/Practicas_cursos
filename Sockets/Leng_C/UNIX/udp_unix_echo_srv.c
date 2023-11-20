/********************************************************
 *
 * Func.: Servidor que hace Echo con sockets.
 *   Tipo:    SOCK_DGRAM
 *   Dominio: AF_UNIX
 *
 *  Compile
 *      $ gcc -o udp_unix_echo_srv udp_unix_echo_srv.c
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
 int sock, len_clt, len_srv;
 struct sockaddr_un adr_clt, adr_srv;
 unsigned char data[100];

    // 1. Crear socket
    if ((sock=socket(AF_UNIX, SOCK_DGRAM,0))<0 ) {
        perror("socket: ");
        return(1);
    }

    // 2. Preparar estrucutras de datos
    bzero(&adr_srv, sizeof(adr_srv));
    adr_srv.sun_family = AF_UNIX;
    strcpy(adr_srv.sun_path, SOCKET_PATH_SRV);
   
    // 3. Enlazar el socket 
    if( bind(sock, (struct sockaddr*)&adr_srv, sizeof(adr_srv)) == -1 ){
        close(sock);
        perror("bind: ");
        return(2);
    }

    // 4. Preparar estructuras de datos 
    len_clt = sizeof(adr_clt);
    printf("Servidor iniciado. Listo para recibir ...\n");

    while(1){
       // Limpiar buffer 
       bzero(data, 100);

       // 5. Recibir 
       len_clt = recvfrom(sock, data, 100, 0, (struct sockaddr*) &adr_clt, &len_clt);
    
       // 6. Procesamiento del resultado
       if(len_clt == -1) {
           perror("recvfrom: ");
           return(3);
       }else{
           printf("Echo length:  %d bytes\n", len_clt);
           printf("Echo message: %s\n", data);
       }
    }
        
    // 7. Liberar recursos
    unlink(SOCKET_PATH_SRV);
    close(sock);
    printf("Server done\n"); 

 return 0;
}
