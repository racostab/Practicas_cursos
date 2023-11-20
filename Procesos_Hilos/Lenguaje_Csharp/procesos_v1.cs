/*
   Description
      Csharp Program to demonstrate the use of Fork.
   Compile
      $ dotnet --version
      $ dotnet procesos_v1 procesos_v1.cs
*/
using System;

namespace Procesos
{
    public class Program
    {
        public static void Main(string[] args)
        {
            fork();
        }

        public static void hijo()
        {
        }

    }
}