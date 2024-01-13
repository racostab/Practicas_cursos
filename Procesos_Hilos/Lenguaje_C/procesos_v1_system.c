/*
   Description
      C Program to demonstrate the use of System.
   Compile
      $ gcc -o procesos_v1_system procesos_v1_system.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    //-------------------------------------------------------------
	// Remplaza al proceso asi que después ya no se ejecuta nada.
    //-------------------------------------------------------------

    system("ps");
    //system("/bin/ps -fea");
	return 0;
}
