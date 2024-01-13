/*
   1. Crear el proyecto
      $ dotnet new console
   2. Cambiar el codigo del archio Programa.cs
      $ vim Programa.cs
   3. Compilar
      $ dotnet build
   4. Ejecutar
      $  bin/Debug/net7.0/proyecto1
*/
using System;

namespace Procesos
{
    public class Program
    {
        public static void Main(string[] args)
        {
            //fork();
            System.Console.WriteLine("Hello, C#!");
        }

        public static void hijo()
        {
        }

    }
}
