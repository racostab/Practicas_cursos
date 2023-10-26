/*
   Description
      Producer-Consumer problem with Pipes.
   Compile
      $ gcc -o prod_cons_pipes_v1 prod_cons_pipes_v1.c
      $ prod_cons_pipes_v1

      Other terminal:
	  $ pkill prod_cons_pipes_v1
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int tuberia[2];
void consumidor();
void productor();

int main ()
{	
  pid_t pid;
  int error;

    error = pipe(tuberia);
    if( error < 0 ){
      printf("Error en la creacion del pipe\n");
      return 1;
    }

    // Productor
    pid = fork();
	switch(pid){
	  case -1: // ERROR
		       perror("fork");
		       exit(1);
	  case 0:  // HIJO
	           productor();
		       exit(1);
	  default: // PADRE
		       ; 
	}

    // Consumidor
    pid = fork();
	switch(pid){
	  case -1: // ERROR
		       perror("fork");
		       exit(1);
	  case 0:  // HIJO
	           consumidor();
		       exit(1);
	  default: // PADRE
		       ; 
	}
	printf("Father ends. PID: %d\n", getpid() );
	// No es necesario esperar a los hijos, el pipe no se destruye
	//sleep(15);
	return 0;
}


void consumidor()
{
  int bytes;
  char *buf = calloc(100, sizeof(char));

	printf("\t\tConsumidor %d\n", getpid() );

    while(1){ 
       sleep(3);
       bytes = read(tuberia[0], buf, 100);
       printf("\t\t\t%s => C\n", buf);
	   fflush(stdout);
	}
}

void productor()
{
  int bytes, tam, cnt;
  char *buf = calloc(100, sizeof(char));

	printf("Productor %d\n", getpid() );

    cnt=1;
    while(1){
	   // OPC 1
       // strcpy(buf, "abcde");
	   // OPC 2
	   sprintf(buf, "%d", cnt);
       sleep(1);

	   tam = strlen(buf);
       write(tuberia[1], buf, tam);
       printf("P => %s\n", buf);
	   fflush(stdout);
       cnt++;
    }
}
