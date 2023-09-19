package nek.java.lab5;

import java.util.Scanner;
public class Task17 {

    public static int maxNum(){
        Scanner in = new Scanner(System.in);
        int a = in.nextInt();
        in.nextLine();
        if (a == 0){
            return a;
        }
        return Math.max(a, maxNum());
    }

    public static void main(String[] args) {
        System.out.println("Вводите числа по одному на каждую строку. Для завершения введите 0.");
        System.out.println("Максимальное число в указанной последовательности: " + maxNum());
    }
}
