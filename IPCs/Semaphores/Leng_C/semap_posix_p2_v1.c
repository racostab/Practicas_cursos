/*
   Description
      C Program for Semaphore: POSIX.
   Compile
      $ gcc -o semap_posix_p2_v1 semap_posix_p2_v1.c
*/
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#include <errno.h>
#include <fcntl.h> 

int main() 
{ 
 sem_t mutex;
 sem_t *sem_id;
 const char *semName="./sem_name";

    printf("1. Create semaphore\n");
	sem_id = sem_open(semName, O_CREAT, 0666, 1);
	if(sem_id == SEM_FAILED) 
	{
		perror("sem_open Failed\n");
	 	return 1;
	}
	// deprecated
	//sem_id = &mutex;
	//sem_init(sem_id, 0, 1); 

    printf("2. Wait, Sleep, Down / P2 \n");
	if( sem_wait(sem_id) < 0 ){
		perror("sem_wait Failed\n");
		return 2;
	}

	//---------------------------------------------
    // Critical Region
	printf("3. Inside Critical region / P2 \n");
	//---------------------------------------------

	if( sem_post(sem_id) < 0 ){
		perror("sem_post Failed\n");
		return 3;
	}
    printf("4. Leave critical region / P2 \n");

    printf("5. Destroy semaphore when the last one close it\n");
	if (sem_close(sem_id) != 0) {
		perror("sem_close Failed\n");
		return 4;
	} 

	return 0; 
} 

