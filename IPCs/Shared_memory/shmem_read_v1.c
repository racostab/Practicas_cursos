/*
   Description
      C Program for Shared Memory (Reader Process) 
   Compile
      $ gcc -o shmem_read_v1 shmem_read_v1.c

      $ ipcs
      $ ipcs -m o -M
*/
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>

int main (void)
{
  int *vector, shmid;
  key_t llave;

    printf("1. Create key\n");
    llave = ftok("shared", 2019);

    printf("2. Read or create memory zone pointer\n");
    // shmget returns an identifier in shmid 
    shmid = shmget(llave, 25*sizeof(int), IPC_CREAT | 0777);
     
    printf("3. Link memory zone to user space\n");
    vector = (int *)shmat(shmid, (void *)0, 0);
     
    // 3. Utilización
    printf("4. Read the shared memory\n");
    printf("     array[10]: %d\n", vector[10]);
     
     printf("5. Detach memory\n");
     shmdt(vector);
     
    // 6. Delete memory zone
    // printf("6. Delete memory\n");
    // shmctl(shmid, IPC_RMID, 0);

}


