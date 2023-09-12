package nek.java.lab2.task10;

import java.util.Scanner;

public class HowMany {
    public static void main(String[] args) {
        String text = "";
        System.out.println("Введите текст ниже. Каждая новая строка дополнит введенный текст. Для завершения введите " +
                "EOI (строка с данным словом будет исключена из текста):\n");
        String line = "";
        Scanner in = new Scanner(System.in);
        while(true) {
            line = in.nextLine();
            if(line.contains("EOI")){
                break;
            }
            text += line + " ";
        }

        text = text.replaceAll("[^a-zа-я-]+"," ").trim();
        System.out.println("\n\nОчищенный текст:\n" + text);
        System.out.println("Количество слов: " + text.split(" ").length);
    }
}
