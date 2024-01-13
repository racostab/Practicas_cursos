/********************************************************
 *
 * Func.: Servidor que hace Echo con sockets.
 *   Tipo:     SOCK_STREAM
 *   Dominio:  AF_INET
 *
 *   Compile
 *        $ gcc -o tcp_inet_echo_srv tcp_inet_echo_srv.c
 *
 *   Pruebe este programa en 2 computadoras.
 ********************************************************/
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define PORT 8080

void error(char *msg)
{
   perror(msg);
   //exit(1);
   exit(errno); //este devuelve el error correspondiente 
}

int main(int argc, char const* argv[])
{
  struct sockaddr_in address;
  int sock, new_socket, len;
  ssize_t valread;
  int opt = 1;

  socklen_t addrlen = sizeof(address);
  char buffer[1024] = { 0 };
  char message[100] = "[Este es el msg Srv]";

	// 1. Crear socket 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error("socket failed");
	}
	printf("1. Socket creado.\n");

    // 2. Inicializacion de datos
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	printf("2. Datos inicializados.\n");

    // 3. Bind socket to port
	if (bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0) {
		error("bind failed");
	}
	printf("3. Binded.\n");

    // 4. Listen conections
	if (listen(sock, 3) < 0) {
		error("listen");
	}
	printf("4. Listen until 3 conections.\n");

    // 5. Accept
	if ((new_socket = accept(sock, (struct sockaddr*)&address, &addrlen)) < 0) {
		error("accept");
	}
	printf("5. Accept one conection.\n");

    // 6. Communication read / send
	len = read(new_socket, buffer, 1024 - 1); // subtract 1 for the null
	printf("6a. Message received: %s\n", buffer);

	//send(new_socket, message, strlen(message), 0);
	send(new_socket, buffer, strlen(buffer), 0);
	printf("6b. Message sent\n");

	close(new_socket);
	close(sock);

	return 0;
}
