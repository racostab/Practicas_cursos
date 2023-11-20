/*
   Description
      C Program for Semaphore: POSIX.
   Compile
      $ gcc -o semap_posix_v2 semap_posix_v2.c
*/
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#include <errno.h>
#include <fcntl.h> 

sem_t *sem_id;
void P1(), P2();

int main() 
{
 const char *semName="./sem_name";
 int binary = 1; // Binary semaphore
 int pid;

    printf("1. Creating semaphore\n");
	sem_id = sem_open(semName, O_CREAT, 0666, binary);
	if( sem_id == SEM_FAILED ){
		perror("sem_open Failed\n");
		return 1;
	}

    // P1
    printf("2. Creating P1\n");
    pid = fork();
	switch(pid){
	  case -1: // ERROR
		       perror("fork");
		       exit(1);
	  case 0:  // HIJO
	           P1();
		       exit(1);
	  default: // PADRE
		       ; 
	}

    // P2
    printf("3. Creating P2\n");
    pid = fork();
	switch(pid){
	  case -1: // ERROR
		       perror("fork");
		       exit(1);
	  case 0:  // HIJO
	           P2();
		       exit(1);
	  default: // PADRE
		       ; 
	}

    // If processes finish
	printf("5. Destroy semaphore when the last one close it\n");
	if( sem_unlink(semName) < 0 ){
	    perror("sem_unlink Failed \n");
		return 3;
	}

	return 0; 
} 

int critical_region(char *name, int timer)
{
	// Locking semaphore
	if( sem_wait(sem_id) < 0 ){
		perror("sem_wait Failed\n");
		return 1;
	}

	printf("%s Begin \n", name);
    sleep(timer);
	printf("%s End   \n", name);
	//---------------------------------------------

	// Release semaphore
	if( sem_post(sem_id) < 0 ){
		perror("sem_post Failed\n");
		return 2;
	}
	return 0;
}

void P1()
{
 char *name = "P1";

	printf("%s %d\n", name, getpid() );
    while(1){
		critical_region(name, 3);
	}
}

void P2()
{
 char *name = "\t\t\tP2";

	printf("%s %d\n", name, getpid() );
    while(1){ 
		critical_region(name, 1);
	}
}

