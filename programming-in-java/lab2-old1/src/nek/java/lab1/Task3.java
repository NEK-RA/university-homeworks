package nek.java.lab1;

public class Task3 {
    public static void main(String[] args) {
        /*
        * Написать программу, в результате которой выводятся на экран
        * аргументы командной строки в цикле for.
        * */
        System.out.println("Аргументы командной строки (каждый с новой строки):");
        for(String arg : args){
            System.out.println(arg);
        }
    }
}
