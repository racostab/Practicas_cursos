/*
   Description
      Named pipes.
   Compile
      $ gcc -o pipes_file_read pipes_file_read.c
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
  int fd, count, size;

    mkfifo(pipeName, 0666);             /* read/write for user/group/others */ 
    fd = open(pipeName, O_RDONLY);  /* open as read-only */ 
    if (fd < 0){
       printf("Error al abrir el pipe\n");
       return -1;
    } 
    
    size = sizeof(char); 
    buffer = calloc(100, size); 
    count = read(fd, buffer, size);
    printf("Reading from pipe: %d bytes\n", count);
    printf("%s\n", buffer);

    close(fd); 
    unlink(pipeName);
}
