/*
	Autor: Cureño Contreras Erick Brandon
	Compilación: javac ForkExample.java
	Ejecución: java ForkExample
*/
import java.util.concurrent.TimeUnit;
import java.io.IOException;

public class ForkExample {
	public static void main(String[] args) {
	try {
		// Obtener el ID del proceso padre
		long parentPid = ProcessHandle.current().pid();
		System.out.println("Proceso padre: Mi PID es " + parentPid);
		// Crear un proceso hijo utilizando ProcessBuilder
		ProcessBuilder processBuilder = new ProcessBuilder("java", "-cp", System.getProperty("java.class.path"), ForkedProcess.class.getName());
		// Iniciar el proceso hijo
		Process process = processBuilder.start();
		// Obtener el ID del proceso hijo
		long childPid = process.pid();
		System.out.println("Proceso padre: PID del proceso hijo es " + childPid);
		// Esperar a que el proceso hijo termine
		int exitCode = process.waitFor();
		System.out.println("Proceso padre: El proceso hijo terminó con código de salida " + exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

	public static class ForkedProcess {
		public static void main(String[] args) {
			// Obtener el ID del proceso hijo
			long pid = ProcessHandle.current().pid();

			// Imprimir el PID del proceso hijo
			System.out.println("Proceso hijo: Mi PID es " + pid);
			try {
				// Esperar por n segundos
				TimeUnit.SECONDS.sleep(10);
			}catch (InterruptedException e) {
				e.printStackTrace();
        	}
        }
    }
}

