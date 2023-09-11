package nek.java.lab1;

import java.util.Scanner;

public class Task2 {
    public static void main(String[] args) {
        /*
        * Написать программу, в результате которой массив чисел вводится
        * пользователем с клавиатуры считается сумма элементов целочисленного
        * массива с помощью циклов do while, while, также необходимо найти
        * максимальный и минимальный элемент в массиве, результат выводится на
        * экран.
        * */
        Scanner stdin = new Scanner(System.in);
        System.out.print("Укажите длинну массива: ");
        int len = stdin.nextInt();
        stdin.nextLine();
        int[] nums = new int[len];

        int counter = 0;
        int sum = 0;
        while(counter != len){
            System.out.print("Введите " + (counter+1) + "-е число: ");
            nums[counter] = stdin.nextInt();
            stdin.nextLine();
            sum += nums[counter];
            counter++;
        }

        int min = nums[0];
        int max = nums[0];
        counter = 1;
        do{
            if(nums[counter]>max){
                max = nums[counter];
            }
            if(nums[counter]<min){
                min = nums[counter];
            }
            counter++;
        }while(counter != len);
        System.out.println("Сумма элементов массива: " + sum);
        System.out.println("Максимальный элемент имеет значение: " + max + ", а минимальный: " + min);
    }
}
