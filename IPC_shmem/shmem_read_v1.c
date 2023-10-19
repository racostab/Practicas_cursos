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

    // 2. Regresar la zona de memoria o la crea. shmget returns an identifier in shmid 
      shmid = shmget(llave, 25*sizeof(int), IPC_CREAT | 0777);
      printf("Paso 2\n");
     
     // 2. Ligar memoria al espacio del Usr
      vector = (int *)shmat(shmid, (void *)0, 0);
      printf("Paso 3\n");
     
     // 3. Utilización
      printf("Leyendo de la memoria compartida (arreglo): %d\n", vector[10]);
     
     // 4. Desligar
      shmdt(vector);
      printf("Paso 4\n");
     
     // 5. Borrar zona de memoria
      shmctl(shmid, IPC_RMID, 0);
      printf("Paso 5\n");

}


