/*
   Description
      .
   Compile
      $ gcc -w -pthread -o hilos_productor_consumidor_v1 hilos_productor_consumidor_v1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define	MAX  8
int bfrQ	[MAX];
int i;

void *consumidor(void *unused);
void *productor(void *unused);

int main ()
{	

}


void *consumidor(void *unused){
	int i= MAX -1;
	int x;
	printf("hilo 1....\n");
	while(1){ 
		if (bfrQ[0]==0){
			i= MAX -1;
			printf("*max %d\n",bfrQ[i]);
			for (x=0;x<MAX;x++){
				bfrQ[x]=0;
			}
			usleep(100000);
		}
		else{
			printf("  -->%d *%d \n",bfrQ[i],i);
			bfrQ[i]=0;
			i--;
		}
	}
}

void *productor(void *unused){
	int i= 0;
	printf("hilo 2....\n");
	while(1){
		if(bfrQ[MAX-1]!=0){
			i=0;
			printf("*min  %d\n",bfrQ[i]);
			usleep(100000);
		}
		else{
			bfrQ[i]=i+1;
			printf("<--- %d *%d \n",bfrQ[i],i);
			i++;
		}
	}
}
