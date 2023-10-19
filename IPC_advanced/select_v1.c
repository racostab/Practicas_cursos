/*
   Description
       select() allows a program to monitor multiple file descriptors,
       waiting until one or more of the file descriptors become "ready"
       for some class of I/O operation (e.g., input possible).

       Monitores varios archivos para saber cual cambio.
   Compile
      $ gcc -o select_v1 select_v1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
  fd_set rfds;
  struct timeval tv;
  int retval;

   /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

   /* Wait up to five seconds. */
    tv.tv_sec = 5;
    tv.tv_usec = 0;

   /* Prototipo 
     int select(int nfds, 
                fd_set * readfds,
                fd_set * writefds,
                fd_set * exceptfds,
                struct timeval *timeout);
   
    Espera a que el usuario capture algo en la Entrada Estandar (fd=1)
    y sucede cuando se da Enter.
   */
   retval = select(1, &rfds, NULL, NULL, &tv);

   if (retval == -1){ // Errno
        perror("select()");
   }else if (retval){
         // retval = Number of file descriptors
        printf("Data is available now.\n");
        /* FD_ISSET(0, &rfds) will be true. */
   }else{
        printf("No data within five seconds.\n");
   }
   return 1;
}

