/*
   C++ Program to demonstrate tthe use of Fork.
   Compilar
      $ g++ -o procesos_v1_pbms procesos_v1_pbms.cpp
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
