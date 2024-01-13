/*
	Autor: Cureño Contreras Erick Brandon
	Compilación: mcs fork.cs
	Ejecución: mono fork.exe
*/
using System;
using System.Threading;

class Program
{
    static void Main()
    {
        Thread newThread = new Thread(MyThreadMethod); // Crear un nuevo hilo
	    Console.WriteLine($"Hilo principal: {GetThreadId()}");
        newThread.Start();
        newThread.Join();
        Console.WriteLine("Fin del programa.");
    }

    static void MyThreadMethod()
    {
	   Console.WriteLine($"Proceso hijo: {GetThreadId()}");
	   Thread.Sleep(10000);
    }

    // Método para obtener el identificador de hilo nativo
    [System.Runtime.InteropServices.DllImport("libc")]
    private static extern int syscall(int number);

    private static int GetThreadId()
    {
        return syscall(186); // 186 es el número de llamada al sistema para obtener el identificador de hilo en Linux
    }
}

