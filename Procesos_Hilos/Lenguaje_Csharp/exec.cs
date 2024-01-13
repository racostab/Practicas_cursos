/*
	Autor: Cureño Contreras Erick Brandon
	Compilación: mcs exec.cs
	Ejecución: mono exec.exe
*/
using System;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        Console.WriteLine("Este es el programa original");

        // Crear un proceso para ejecutar el comando "ls"
        Process process = new Process();
        process.StartInfo.FileName = "/bin/ls";
        process.StartInfo.Arguments = "-l";
        process.StartInfo.UseShellExecute = false;
        process.StartInfo.RedirectStandardOutput = true;

        try
        {
            // Iniciar el proceso
            process.Start();

            // Leer y mostrar la salida del proceso
            string output = process.StandardOutput.ReadToEnd();
            Console.WriteLine(output);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error al iniciar el proceso: {ex.Message}");
        }
        finally
        {
            // Asegurarse de que el proceso se cierre adecuadamente
            process.WaitForExit();
            process.Close();
        }

        Console.WriteLine("Proceso padre terminando");
    }
}

