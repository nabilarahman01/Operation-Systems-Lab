/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package readerwriter;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.Semaphore;

public class ReaderWriter {

    public static Semaphore m, w;
    public static int readCount = 0;
    public static int maxReaderCount = 5;
    public static int maxWriterCount = 2;
    
    public static void main(String[] args) {
         m = new Semaphore(1);
        w = new Semaphore(1);

        new Thread(new Writer()).start();
        new Thread(new Reader()).start();
    }
    
}

class Data {
    public static List<Integer> buffer = new ArrayList<Integer>();
}

class Reader implements Runnable {

    int i = 0;

    @Override
    public void run() {
        while (true) {
            try {
                ReaderWriter.m.acquire();
                ReaderWriter.readCount++;
                if (ReaderWriter.readCount == 1) {
                    ReaderWriter.w.acquire();
                }
                ReaderWriter.m.release();

                if (Data.buffer.size() > 0) {
                    Random rand = new Random();
                    int index = rand.nextInt(Data.buffer.size());
                    int readData = Data.buffer.get(index);
                    Data.buffer.remove(index);
                    System.out.println("Reader " + i + ": Reading " + readData);
                }
                ReaderWriter.m.acquire();
                ReaderWriter.readCount--;
                if (ReaderWriter.readCount == 0) {
                    ReaderWriter.w.release();
                }
                ReaderWriter.m.release();
                i = (i + 1) % ReaderWriter.maxReaderCount;
                Thread.sleep(1000);
            } catch (InterruptedException e) {

            }
        }
    }
}

class Writer implements Runnable {

    int i = 0;

    @Override
    public void run() {
        while (true) {
            try {
                ReaderWriter.w.acquire();

                Random rand = new Random();
                int data_1 = rand.nextInt(999);
                int data_2 = rand.nextInt(999);
                System.out.println("Writer " + i + ": Writes in the system " + data_1 + ", " + data_2);
                Data.buffer.add(data_1);
                Data.buffer.add(data_2);
                   
                ReaderWriter.w.release();
                i = (i + 1) % ReaderWriter.maxWriterCount;
                Thread.sleep(2000);
            } catch (InterruptedException e) {

            }
        }
    }
}