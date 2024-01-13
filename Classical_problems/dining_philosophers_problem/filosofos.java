/*
	Autor: Cureño Contreras Erick Brandon
	Compilación: javac CenaFilosofos.java
	Ejecución: java CenaFilosofos
*/
import java.util.concurrent.Semaphore;

class Filosofo implements Runnable {
    private final int id;
    private final Semaphore tenedorIzquierdo;
    private final Semaphore tenedorDerecho;

    public Filosofo(int id, Semaphore tenedorIzquierdo, Semaphore tenedorDerecho)
    {
        this.id = id;
        this.tenedorIzquierdo = tenedorIzquierdo;
        this.tenedorDerecho = tenedorDerecho;
    }

    private void comer() throws InterruptedException 
    {
        System.out.println("Filósofo " + id + " está comiendo.");
        Thread.sleep(1000); // Simula el tiempo que tarda en comer
    }

    private void pensar() throws InterruptedException
    {
        System.out.println("Filósofo " + id + " está pensando.");
        Thread.sleep(1000); // Simula el tiempo que tarda en pensar
    }

    @Override
    public void run() {
        try {
            while (true) {
                pensar();
                tenedorIzquierdo.acquire(); // Adquirir tenedor izquierdo
                tenedorDerecho.acquire(); // Adquirir tenedor derecho
                comer();
                tenedorIzquierdo.release(); // Liberar tenedor izquierdo
                tenedorDerecho.release(); // Liberar tenedor derecho
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class Filosofos
{
    public static void main(String[] args)
    {
        if (args.length != 1) {
            System.out.println("Uso: java CenaFilosofos <numero_de_filosofos>");
            System.exit(1);
        }

        int numFilosofos = Integer.parseInt(args[0]);
        Semaphore[] tenedores = new Semaphore[numFilosofos];

        for (int i = 0; i < numFilosofos; i++) {
            tenedores[i] = new Semaphore(1); // Inicializar semáforo para cada tenedor
        }

        Thread[] filosofos = new Thread[numFilosofos];

        for (int i = 0; i < numFilosofos; i++) {
            filosofos[i] = new Thread(new Filosofo(i, tenedores[i], tenedores[(i + 1) % numFilosofos]));
            filosofos[i].start();
        }
    }
}

