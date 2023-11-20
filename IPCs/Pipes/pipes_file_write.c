/*
   Description
      Named pipes.
   Compile
      $ gcc -o pipes_file_write pipes_file_write.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{ 
  const char* pipeName = "./fifoChannel"; 
  char *buffer; 
  int i, fd, size, ascii;

    mkfifo(pipeName, 0666);                  /* read/write for user/group/others */ 
    fd = open(pipeName, O_CREAT | O_WRONLY); /* open as write-only */ 
    if (fd < 0){
       printf("Error al abrir el pipe\n");
       return -1;
    } 

    size = sizeof(char); 
    buffer = calloc(100, size); 
    ascii = 30;
    for(i=0; i<50; i++){ 
        buffer[i] = ascii;
        ascii++;
        if( ascii == 40) ascii=30;
    }
    buffer[50] = '\0';
    printf("Writing to the pipe: %d bytes\n", 50);
    printf("%s\n", buffer);

    write(fd, buffer, size*50);

    close(fd);
    unlink(pipeName);
}
