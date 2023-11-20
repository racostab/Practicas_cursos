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

int timer_prod, timer_cons;

int main(int argc, char**argv)
{	
  pid_t pid;
  int error;

    if (argc < 2) {
       timer_prod = 1;
	   timer_cons = 3;
	}else if (argc >= 3 ) {
       timer_prod = atoi(argv[1]);
	   timer_cons = atoi(argv[2]);
	}
    printf("Timers Prod: %d Cons: %d \n", timer_prod, timer_cons);

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
       sleep(timer_cons);
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
       sleep(timer_prod);

	   tam = strlen(buf);
       write(tuberia[1], buf, tam);
       printf("P => %s\n", buf);
	   fflush(stdout);
       cnt++;
    }
}
