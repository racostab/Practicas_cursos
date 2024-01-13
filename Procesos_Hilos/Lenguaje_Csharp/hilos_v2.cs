/*
	Autor: Cureño Contreras Erick Brandon
	Compilación: mcs hilos.cs
	Ejecución: mono hilos.exe
*/
using System;
using System.Threading;

class Program
{
	static void Main()
	{
		Thread hilo = new Thread(NuevoHilo);
		hilo.Start();
		Console.WriteLine("Hilo principal id: " + Thread.CurrentThread.ManagedThreadId);
		Thread.Sleep(500); // Hacer una pausa para que sea más fácil de observar
		hilo.Join();
		Console.WriteLine("Fin del programa");
	}

	static void NuevoHilo()
	{
		Console.WriteLine("Nuevo hilo id: " + Thread.CurrentThread.ManagedThreadId);
		Thread.Sleep(500); // Hacer una pausa para que sea más fácil de observar
	}
}

