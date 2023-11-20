/*
   Description
       Use mmap for putting a file in memory
   Compile
      $ gcc -o mmap_v1 mmap_v1.c
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

float measure( void (*func)(), int);
void leer_archivo();
struct stat sb;
char *p;

int main(int argc, char *argv[])
{
  float time;
  int fd;

   if( argc <2 ){
       printf("Error: filename\n");
       return 1;
   }
   //printf("Filename: %s\n", argv[1]);

   fd = open(argv[1], O_RDONLY);
   if (fd == -1) {
       perror ("open");
       return 2;
   }

   // Se obtiene su tamaño
   if (fstat(fd, &sb) == -1) {
       perror ("fstat");
       return 3;
   }

   // Se verifica que sea un archivo
   if (!S_ISREG (sb.st_mode)) {
       fprintf (stderr, "%s is not a file\n", argv[1]);
       return 4;
   }

   // Se liga a la memoria RAM
   p = mmap (0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
   if (p == MAP_FAILED) {
       perror ("mmap");
       return 5;
   }

   if (close (fd) == -1) {
       perror ("close");
       return 6;
   }

   //-----------------------------------------------------------
   int exe = 0;
   if( exe ){
      // Se imprime el contenido del archivo
      leer_archivo();
   }else{
      int um=1;
      // Medir el tiempo de ejecucion
      time = measure(leer_archivo, um);
      if( um == 1 ){
         printf("Time elapsed: %.4f sec \n", time); 
      }else{
         printf("Time elapsed: %.4f nano\n", time); 
      }
   }
   //-----------------------------------------------------------

   // Des-ligar a la memoria RAM
   if (munmap(p, sb.st_size) == -1) {
       perror ("munmap");
       return 7;
   }

   return 0;
}

void leer_archivo()
{
 int len;

    for(len = 0; len < sb.st_size; len++)
        putchar(p[len]);
}

float measure( void (*func)(), int um)
{
  struct timespec start, end, time;

    
    clock_gettime(CLOCK_REALTIME, &start);
    func();
	clock_gettime(CLOCK_REALTIME, &end);
    float sec = (end.tv_sec - start.tv_sec);
    float nano = (end.tv_nsec - start.tv_nsec);
    float segundos = sec + (nano / 1e9);

    if( um == 1){
       return segundos;
    }else{
       return nano;
    }
}
