#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main (int argc, char *argv[])
{
  struct stat sb;
  off_t len;
  char *p;
  int fd;

        // Se verifican los parámetros
        if (argc < 2) {
                fprintf (stderr, "usage: %s <file>\n", argv[0]);
                return 1;
        }

        // Se abre el archivo
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
                perror ("open");
                return 1;
        }

        // Se obtiene su tamaño
        if (fstat(fd, &sb) == -1) {
                perror ("fstat");
                return 1;
        }

        // Se verifica que sea un archivo
        if (!S_ISREG (sb.st_mode)) {
                fprintf (stderr, "%s is not a file\n", argv[1]);
                return 1;
        }

        // Se liga a la memoria RAM
        p = mmap (0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
        if (p == MAP_FAILED) {
                perror ("mmap");
                return 1;
        }

        if (close (fd) == -1) {
                perror ("close");
                return 1;
        }

        // Se imprime el contenido del archivo
        for (len = 0; len < sb.st_size; len++){
                //putchar(p[len]);
                printf("[%c]", p[len]);
        }

        if (munmap(p, sb.st_size) == -1) {
                perror ("munmap");
                return 1;
        }

        return 0;
}

