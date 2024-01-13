/*
   Description
      C Program to demonstrate the use of Fork.
   Compile
      $ gcc -o procesos_v1_exec procesos_v1_exec.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    //-------------------------------------------------------------
	// Remplaza al proceso asi que después ya no se ejecuta nada.
    //-------------------------------------------------------------

    int elige = 3;
    switch(elige){
		case 1:
			   printf("execl:\n");
			   printf("----------------------------------\n");
               execl("/bin/ls", "ls", "-l", "-R", "-a", NULL);
		case 2: // with execv
			   printf("execv 1:\n");
			   printf("----------------------------------\n");
		       {
                 char *const arreglo[] = {"/bin/ls", "-l", "/home", NULL};
                 execv("/bin/ls", arreglo);
			   }
		case 3:
			   printf("execv 2:\n");
			   printf("----------------------------------\n");
		       {
				 // primer valor de array es el nombre del programa, como en argv[0]
                 char* array[] = {"ls", "-l", "-R", "-a", NULL};
                 execv("/bin/ls", array);
			   }
	}
	return 0;
}
