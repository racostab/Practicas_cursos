/*
   C++ Program to demonstrate the use of Fork.
   Instalacion:
      $ sudo apt-get update
	  $ sudo apt-get install build-essential 
   Compilar
      $ g++ -o procesos_v1 procesos_v1.cpp
*/
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	pid_t pid = fork();

	switch(pid){
	  case -1: // ERROR
		       perror("fork");
		       exit(EXIT_FAILURE);
	  case 0: // HIJO
	           cout << "Child  PID: " << getpid() << endl;
				break;
	  default: // PADRE
		       cout << "Father PID: " << getpid() << endl;

	}
	return 0;
}
