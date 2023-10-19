#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>

int main (void)
{
  int *vector, shmid;
  key_t llave;

     // 1. Crear llave
     //            path     id
     llave = ftok("shared", 2019);
      printf("Paso 1\n");
     
     // 2. Crear zona de memoria: arreglo de 25 enteros
     shmid = shmget(llave, 25*sizeof(int), IPC_CREAT | 0777);
      printf("Paso 2\n");
     
     // 3. Ligar memoria al espacio del Usr
      vector = (int *) shmat(shmid, (void *)0, 0);
      printf("Paso 3\n");
     
     // 4. Utilización
      vector[10]=54321;
      printf("Escribiendo en memoria compartida (arreglo): %d \n", vector[10]);
     
     // 5. Desligar
     shmdt(vector);
      printf("Paso 5\n");
     
}


