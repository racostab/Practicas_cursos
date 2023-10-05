/*
   C++ Program to demonstrate tthe use of Fork.
   Instalacion:
      $ sudo apt-get update
	  $ sudo apt-get install build-essential 
   Compilar
      $ g++ -o procesos_cpp_v2 procesos_cpp_v2.cpp
*/
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	pid_t pid;

    /*
	fork();
    fork();
    fork();
    cout << "Cuantas veces se imprime? Quien soy?" << endl;
    */

	//
	for(int i=0; i<3; i++){
		pid = fork();
		if( pid == -1){
			perror("fork");
		    exit(EXIT_FAILURE);
		}
		cout << "Cuantas veces se imprime? Quien soy?" << endl;
	}
	//
	return 0;
}
