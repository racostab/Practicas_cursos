/*
   Description
      C Program for Semaphore: POSIX.
	  Run first this program and then semap_posix_p2_v1
   Compile
      $ gcc -o semap_posix_p1_v1 semap_posix_p1_v1.c

   sem_open()    Connects to, & optionally creates, a named semaphore( like sem_init() )
   sem_unlink()  Ends connection to an open semaphore & causes the semaphore to be removed 
                     when the last process closes it( like sem_destroy())
   sem_wait()    Wait for semaphore to acquire
   sem_post()    Release semaphore
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
	//                 (const char *name, int oflag, mode_t mode, unsigned int value);
	sem_id = sem_open(semName, O_CREAT, 0666, 1);
	if( sem_id == SEM_FAILED ){
		perror("sem_open Failed\n");
		return 1;
	}
	// deprecated
	//sem_id = &mutex;
	//sem_init(sem_id, 0, 1); 

    printf("2. Wait, Sleep, Down. / P1 \n");
	// Locking semaphore
	if( sem_wait(sem_id) < 0 ){
		perror("sem_wait Failed\n");
		return 2;
	}

	//---------------------------------------------
    // Critical Region
	printf("3. Inside Critical region / P1 \n");
    sleep(7);
	//---------------------------------------------

	// Release semaphore
	if( sem_post(sem_id) < 0 ){
		perror("sem_post Failed\n");
		return 3;
	}
    printf("4. Leave critical region / P1\n");

    printf("5. Destroy semaphore when the last one close it\n");
	if( sem_unlink(semName) < 0 ){
	    perror("sem_unlink Failed \n");
		return 3;
	}

	// if( sem_close(sem_id) != 0 ) {
	// 	perror("sem_close Failed \n");
	// 	return 3;
	// }

	return 0; 
} 

