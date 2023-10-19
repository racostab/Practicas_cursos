/*
   Description
      Read operation of files.
   Compile
      $ gcc -o file_blocks_v1 file_blocks_v1.c
*/
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

int main()
{
   char *c, *str;
   int fd, sz;
  
    // 1. Abrir
    //fd = open("contador.txt", O_RDONLY | O_CREAT); 
    fd = open("contador.txt", O_RDONLY | O_WRONLY | O_CREAT | O_TRUNC, 0644); 

    printf("fd = %d\n", fd); 
    if (fd == -1) { 
        printf("Error Number % d\n", errno); 
        perror("Program"); 
        exit(1); 
    } 

   // 2. Leer
   c = (char*) calloc(100, sizeof(char));

   sz = read(fd, c, 10); 
   printf("called read(% d, c, 10). returned that %d bytes were read.\n", fd, sz); 
   //c[sz] = '\0'; 
   printf("Content:\n-----\n");
   printf("%s", c);
   printf("\n-----\n");

   // 3. Escribir
   str = (char*) malloc(100 * sizeof(char));
   strcpy(str, "qwerty\n");
   sz = write(fd, str, strlen(str));
   printf("Writing: %d bytes\n", sz);

   // 4. Cerrar
   if(close(fd) < 0) { 
        perror("close"); 
        exit(1); 
   } 
   printf("closed the fd.\n"); 

   return 0;
}

