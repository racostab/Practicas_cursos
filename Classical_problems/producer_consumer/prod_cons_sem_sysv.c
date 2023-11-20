/*
   Description
      Producer-Consumer problem with Semaphores SYSV.
   Compile
      $ gcc -o prod_cons_sem_sysv prod_cons_sem_sysv.c
      $ prod_cons_wsem_sysv

    Modificar el programa para que el buffer funcione.
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>

#define SEM_KEY 0x1234
#define BUFFER_SIZE 10

int in = 0, out = 0, count = 0;
int buffer[BUFFER_SIZE];

void produce(int semid)
{
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(semid, &sem_op, 1);

    buffer[in] = count++;
    in = (in + 1) % BUFFER_SIZE;
    printf("Produced item: %d\n", buffer[in] );

    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    semop(semid, &sem_op, 1);
}

void consume(int semid)
{
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(semid, &sem_op, 1);

    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    printf("\t\t\tConsumed item: %d\n", item);

    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    semop(semid, &sem_op, 1);

}

int main()
{
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid < 0){
        perror("semget");
        return 1;
    }

    if (semctl(semid, 0, SETVAL, 1) < 0){
        perror("semctl");
        return 1;
    }

    if (fork() == 0){
        for (int i = 0; i < 5; i++){
            produce(semid);
        }
    } else {
        for (int i = 0; i < 5; i++){
            consume(semid);
        }
    }

    return 0;
}
