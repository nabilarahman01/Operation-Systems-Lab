
package producerconsumer;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.Semaphore;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ProducerConsumer {

    public static Semaphore mutex, full, empty;
    public static int size_n = 5;

    public static void main(String[] args) {
        
        mutex = new Semaphore(1);
        full = new Semaphore(0);
        empty = new Semaphore(size_n);
        
        
        Producer producerThread = new Producer();
        Consumer consumerThread = new Consumer();
        
        Thread t1 = new Thread(producerThread);
        Thread t2 = new Thread(consumerThread);
        
        t1.start();
        t2.start();
        
    }
    
}

class Data {
    public static ArrayList<Integer> buffer = new ArrayList<Integer>();
}

class Producer implements Runnable {
    
    @Override
    public void run() {
        int i = 0;
        while (true) {
            try {

                Random rand = new Random();
                int data = rand.nextInt(999);

                System.out.println("Producer " + (i + 1) + ": Data to insert in the buffer");
                System.out.println("Data: " + data);

                ProducerConsumer.empty.acquire();
                ProducerConsumer.mutex.acquire();

                Data.buffer.add(data);

                System.out.println("Producer " + (i + 1) + ": Data " + data + " is inserted in the buffer");
                System.out.println("Empty Space: " + (ProducerConsumer.size_n - Data.buffer.size()));
                System.out.println("Full Space: " + Data.buffer.size());

                ProducerConsumer.mutex.release();
                ProducerConsumer.full.release();
                i = (i + 1) % 2;
//                Thread.sleep(1000);
            } catch (InterruptedException ex) {

            }
        }
    }
}

class Consumer implements Runnable {

    @Override
    public void run() {
        int i = 0;
        while (true) {
            try {
                ProducerConsumer.full.acquire();
                ProducerConsumer.mutex.acquire();
                
                int data = Data.buffer.remove(0);
                
                ProducerConsumer.mutex.release();
                ProducerConsumer.empty.release();
                
                System.out.println("Consumer " + (i + 1) + ": Data " + data + " is consumed from the buffer");
                System.out.println("Full Space: " + Data.buffer.size());
                
                i = (i + 1) % 2;
//                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                
            }
        }
    }

}