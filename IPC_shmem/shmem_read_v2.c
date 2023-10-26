/*
   Description
      C Program for Shared Memory (Reader Process) 
   Compile
      $ gcc -o shmem_read_v2 shmem_read_v2.c

      $ ipcs
      $ ipcs -m o -M
*/
#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h>

int main (void)
{
  int *vector, shmid, cnt;
  key_t llave;

    llave = ftok("shared", 2019);
    shmid = shmget(llave, 25*sizeof(int), IPC_CREAT | 0777);
     
    vector = (int *)shmat(shmid, (void *)0, 0);
    for(cnt=1; cnt<=20; cnt++){
       printf("%d\n", vector[10]);
       sleep(3);
    }
     
    shmdt(vector);
     
    // shmctl(shmid, IPC_RMID, 0);
}


