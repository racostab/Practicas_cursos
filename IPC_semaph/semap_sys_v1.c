/*
   Description
      C Program for Semaphore: SYSV.

   Compile
      $ gcc -o semap_sys_v1 semap_sys_v1.c
*/
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 
#include <errno.h>

int main() 
{ 
 union semun arg;
 key_t key;
 int semid;
 struct sembuf sb = {0, -1, 0}; // set to allocate resource 

    printf("1. Creating key\n");
    key = ftok("semaforo", 65);
    
    printf("2. Creating a semaphore\n");
    // create a semaphore set with 1 semaphore: 
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) == -1){
        perror("semget");
        return 2; 
    }

    printf("3. Locking \n");
    if (semop(semid, &sb, 1) == -1){ 
        perror("semop");
        return 3; 
    }
    // ------------------------------------
    // Critical region 
    printf("4. Inside Critical region \n");
    sleep(3);
    // ------------------------------------

    printf("5. Unlocking \n");
    sb.sem_op = 1; // free resource 
    if (semop(semid, &sb, 1) == -1){
        perror("semop");
        return 4; 
        
    }

    printf("6. End \n");

	return 0; 
} 

