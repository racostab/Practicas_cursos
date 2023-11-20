/********************************************************
 *
 * Func.: Cliente que hace Echo con sockets.
 *   Tipo:     SOCK_STREAM
 *   Dominio:  AF_INET
 *
 *   Compile
 *        $ gcc -o tcp_inet_echo_clt tcp_inet_echo_clt.c
 *
 *   Pruebe este programa en 2 computadoras.
 ********************************************************/
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define PORT 8080
#define TAM_MAX   1024

void error(char *msg)
{
   perror(msg);
   //exit(1);
   exit(errno); //este devuelve el error correspondiente 
}

int main(int argc, char const* argv[])
{
  int status, val, sock;
  struct sockaddr_in address;

  // char buffer[TAM_MAX];
  char message[100] = "[Este es el mensaje Clt]";
  char buffer[1024] = { 0 };

    // 1. Crear socket 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error("Socket");
	}
	printf("1. Socket creado.\n");

    // 2. Inicializacion de datos
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
		error("Inet_pton");
	}
	printf("2. Datos inicializados.\n");

    // 3. Conecta al servidor
	if ((status = connect(sock, (struct sockaddr*)&address, sizeof(address))) < 0) {
		error("Connect");
	}
	printf("3. Connect.\n");

    // 4. Enviar mensaje
	//bzero(buffer, TAM_MAX);
    //printf("Message: ");
    //scanf("%s\n", buffer);
	//send(sock, buffer, strlen(buffer), 0);

    printf("Message: ");
    scanf("%s", message);
	send(sock, message, strlen(message), 0);

	printf("4. Message sent.\n");

    // 5. Enviar mensaje
	printf("5. Echo Reading from socket\n");
	val = read(sock, buffer, 1024 - 1); // subtract 1 for the null terminator at the end
	printf("5. Echo Msg: %s\n", buffer);

	close(sock);
	return 0;
}

