/********************************************************
 *
 * Func.: Socket Pair.
 *   Tipo:    SOCK_STREAM
 *   Dominio: AF_UNIX
 *
 *   Compile
 *        $ gcc -o tcp_unix_pair tcp_unix_pair.c
 ********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define MAX 100

int main(void)
{
 int sockPair[2];
 char buf[MAX]; 

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockPair) == -1) {
        perror("socketpair");
        exit(1);
    }

    if (!fork()){
        // HIJO
        read(sockPair[1], &buf, MAX);
        printf("Child read: '%s'\n", buf);
        write(sockPair[1], &buf, MAX);
        printf("Child sent: '%s'\n", buf);
    } else {
        // PADRE
        char *str="Flujo_de_bytes";
        write(sockPair[0], str, strlen(str));
        printf("\t\t Parent sent: '%s'\n", str);
        read(sockPair[0], &buf, MAX);
        printf("\t\t Parent read: '%s'\n", buf);
        wait(NULL); /* wait for child to die */
    }

    return 0;
}
