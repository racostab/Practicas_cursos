/*
   Description
      C Program to demonstrate the use of Signals.
   Compile
      $ gcc -o signals_v1 signals_v1.c

      $ kill -SIGUSR1 pid
      $ kill -30 pid
*/
#include <stdio.h>
#include <signal.h>

void handler(int);

int main (void)
{

   signal(SIGUSR1, handler);

   while(1); 
}

void handler(int sig)
{
   printf("Señal recibida !!! %d\n", sig);
}

