/*
   Description
      Csharp Program to demonstrate the use of Fork.
   Compile
      $ javac hilo_v1.java
      $ java hilo_v1
*/

public class hilo_v1 extends Thread 
{
   public void run() {
      for (int i = 0; i < 3; i++) {
         printMsg();
      }
   }

   public void printMsg() {
      Thread h = Thread.currentThread();
      String name = h.getName();
      System.out.println("Metodo = " + name);
   }

   public static void main(String[] args) 
   {
      hilo_v1 h = new hilo_v1();
      h.setName("Ejecutando hilo");
      System.out.println("Antes de iniciar, estado del hilo = " + h.isAlive());
      h.start();
      System.out.println("Despues de start(), estado del hilo)=" + h.isAlive());
	   
      for (int i = 0; i < 3; i++) {
         h.printMsg();
      }
      System.out.println("Terminando el programa, estado del hilo=" + h.isAlive());
   }
}
