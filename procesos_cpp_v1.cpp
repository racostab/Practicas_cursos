/*
   C++ Program to demonstrate tthe use of Fork.
   Instalacion:
      $ sudo apt-get update
	  $ sudo apt-get install build-essential 
   Compilar
      $ g++ -o procesos_cpp_v1 procesos_cpp_v1.cpp
*/
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	pid_t pid = fork();

	switch(pid){
	  case -1:
		       perror("fork");
		       exit(EXIT_FAILURE);
	  case 0:
	           cout << "Child  PID: " << getpid()
			        << endl;
				break;
	  default:
		       cout << "Father PID: " << getpid()
			        << endl;

	}
	return 0;
}
