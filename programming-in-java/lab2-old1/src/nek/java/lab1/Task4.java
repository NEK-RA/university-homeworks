package nek.java.lab1;

public class Task4 {
    public static void main(String[] args) {
        /*
        * Написать программу, в результате работы которой выводятся на экран
        * первые 10 чисел гармонического ряда (форматировать вывод).
        * */
        System.out.println("Первые 10 чисел гармонического ряда:");
        for(int i = 1; i < 10; i++){
            System.out.printf("1/%d + ", i);
        }
        System.out.println("1/" + 10);
    }
}
