/*
   Description
      Process and timers.
      syscalls: fork, getpid
                malloc, printf
   Compile
      $ gcc -o procesos_v3.1 procesos_v3.1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

char *tabul(int);
void hijo(int);

int main(int argc, char**argv)
{
  pid_t pid;
  int NP, cnt;

  if(argc<2){
     printf("Parametros: numero_de_procesos\n");
     return 0;
  }

  NP=atoi(argv[1]);
  if( NP <= 0 ){
     printf("El parametro debe ser un numero positivo mayor que cero\n");
     return 0;
  }

  for(cnt=1; cnt<=NP; cnt++)
  {
     pid = fork();
	 switch(pid){
	   case -1: // ERROR
	 	       perror("fork");
	 	       exit(1);
	   case 0: // HIJO
	 	       //printf("Child PID: %d\n", getpid() );
	           hijo(cnt);
	 	       exit(1);
	   default: // PADRE
	 	       //printf("Father PID: %d\n", getpid() );
	 		   ;
	 }
  }
  return 0;
}

void hijo(int id)
{
    while(1){
       char *tabs = tabul(id);
	   printf("%s%d\n", tabs, getpid() );
	}
}

char *tabul(int id)
{
  int cnt;
  char *str=malloc(100);
    strcpy(str,""); //str="";
    if(id != 1){
	   for(cnt=1; cnt<id; cnt++){
	      sprintf(str, "%s\t", str);
	   }
	}
	return str;
}