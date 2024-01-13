/*
	Autor: Cureño Contreras Erick Brandon
	Compilación: gcc -o filos filos.c -lpthread
	Ejecución: ./filos <num_filosofos>
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<semaphore.h>
#include<pthread.h>

#define RESET_COLOR "\033[0m"
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define BLUE_TEXT "\033[1;34m"

int num_fil;
sem_t **tenedores;
sem_t sem_filosofos;

void pensar(int id)
{
	int i, tiempo;
	for(i=0;i<id;i++) printf("\t");
	tiempo = rand() % 3 + 1;
	printf("Filósofo %d está" RED_TEXT " pensando: %d" RESET_COLOR ".\n", id, tiempo);
	sleep(tiempo); // Simula tiempo pensando
}

void comer(int id)
{
	int i, tiempo;
	for(i=0;i<id;i++) printf("\t");
	tiempo = rand() % 3 + 1;
	printf("Filósofo %d está" GREEN_TEXT " comiendo: %d." RESET_COLOR "\n", id, tiempo);
	sleep(tiempo); // Simula tiempo comiendo
}

void *filosofo(void *num)
{
	int id = *((int *)num);
	int tenedor_izq = id;
	int tenedor_der = (id + 1) % num_fil;
	while (1) {
		pensar(id);

		// Esperar a que haya permisos disponibles
		sem_wait(&sem_filosofos);
		// Tomar tenedores
		sem_wait(tenedores[tenedor_izq]);
		sem_wait(tenedores[tenedor_der]);

		comer(id);

		// Liberar tenedores
		sem_post(tenedores[tenedor_izq]);
		sem_post(tenedores[tenedor_der]);
		// Liberar el permiso
		sem_post(&sem_filosofos);
	}
}

int main(int argc, char** argv)
{
	if(argc < 2){
		printf("Uso: ./filo <num_filosofos>\n");
		return 1;
	}
	num_fil = atoi(argv[1]);
	int ids[num_fil];
	// Inicializar semáforo
	sem_init(&sem_filosofos, 0, num_fil - 1);
	int i;
	tenedores = (sem_t**)malloc(sizeof(sem_t*)*num_fil);
	for (int i = 0; i < num_fil; i++){
		char sem_name[10];
		sprintf(sem_name, "tenedor_%d", i);
		sem_unlink(sem_name);
		tenedores[i] = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
	}
	// Crear hilos de filósofos
	pthread_t* filosofos = (pthread_t*)malloc(sizeof(pthread_t)*num_fil);
	for (int i = 0; i < num_fil; i++){
		ids[i] = i;
		pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
	}
	// Esperar a que todos los filósofos terminen
	for (int i = 0; i < num_fil; i++){
		pthread_join(filosofos[i], NULL);
	}
    return 0;
}

