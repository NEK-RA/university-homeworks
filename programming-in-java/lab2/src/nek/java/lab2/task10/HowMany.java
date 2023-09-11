package nek.java.lab2.task10;

import java.util.Scanner;

public class HowMany {
    public static void main(String[] args) {
        String text = "";
        System.out.println("Enter the text below. Each new line will append to previously entered text. To stop the " +
                "process enter the EOI keyword (line with it will be dropped):\n");
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
        System.out.println("\n\nCleaned text:\n" + text);
        System.out.println("Amount of words: " + text.split(" ").length);
    }
}
