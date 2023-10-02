package nek.java.lab1;

import java.math.BigInteger;
import java.util.Scanner;

public class Task5 {
    public static void main(String[] args) {
        /*
        * Написать программу, которая с помощью метода класса, вычисляет
        * факториал числа (использовать управляющую конструкцию цикла), проверить
        * работу метода.
        * */
        Scanner stdin = new Scanner(System.in);
        long num = 0;
        System.out.println("Для какого числа необходимо вычислить факториал? Для завершения укажите любое отрицательное число");
        do{
            System.out.print("Число: ");
            num = stdin.nextLong();
            stdin.nextLine();
            if(num >= 0){
                System.out.printf("!%d = %s\n", num, factorial(num));
            }
        }while(num >= 0);
        stdin.close();
    }

    public static String factorial(long num){
        if (num < 2){
            return "1";
        }
        BigInteger f = BigInteger.valueOf(1);
        for(int i = 2; i <= num; i++){
            f = f.multiply(BigInteger.valueOf(i));
        }
        return f.toString();
    }
}
