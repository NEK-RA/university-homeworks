package nek.java.lab1;

import java.util.Scanner;

public class Task1 {
    public static void main(String[] args) {
        /*
        * Написать программу, в результате которой массив чисел создается с
        * помощью инициализации (как в Си) вводится и считается в цикле сумма
        * элементов целочисленного массива, а также среднее арифметическое его
        * элементов результат выводится на экран. Использовать цикл for.
        * */
        Scanner stdin = new Scanner(System.in);
        System.out.print("Укажите длинну массива: ");
        int len = stdin.nextInt();
        stdin.nextLine();
        int[] nums = new int[len];
        float sum = 0;
        for(int i = 0; i < len; i++){
            System.out.print("Введите " + (i+1) + "-е число: ");
            nums[i] = stdin.nextInt();
            stdin.nextLine();
            sum += nums[i];
        }

        System.out.println("Сумма элементов массива: "+sum);
        System.out.println("Среднее арифметическое элементов: "+(sum/len));
    }
}
