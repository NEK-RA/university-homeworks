package nek.java.lab2.task9;

import java.util.Collections;
import java.util.LinkedList;
import java.util.Scanner;

public class Poker {
    /*
    * В покере используются стандартные карты, состоящие из 52 карт.
    * Они делятся на 4 масти: пики (♠), черви (♥), бубны (♦) и трефы (♣).
    * Каждая масть содержит по 13 карт: туз, король, дама, валет, и числовые карты от 10 до 2.
    * Важно понимать, что в покере, исключая некоторые специфические варианты игры,
    * старшинство карт определяется их номиналом и мастью играет второстепенную роль.
    * */
    static final LinkedList<String> deck = new LinkedList<>();

    static void fillDeck(){
        char[] suits = {'♠','♥','♦','♣'};
        for(char suit : suits){
            for(int i = 2; i <= 10; i++){
                deck.add(String.format("%c%d", suit, i));
            }
            deck.add(suit + "J");
            deck.add(suit + "Q");
            deck.add(suit + "K");
            deck.add(suit + "A");
        }
        System.out.printf("Deck filled with %d cards:\n%s\n", deck.size(),deck);
        Collections.shuffle(deck);
        System.out.println("Shuffled deck:\n"+deck);
    }

    static String getCard(){
        String card = deck.pop();
        return card;
    }

    public static void main(String[] args) {
        fillDeck();
        System.out.print("How much players: ");
        Scanner sc = new Scanner(System.in);
        while(!sc.hasNextInt()){
            sc.next();
        }
        int players = sc.nextInt();
        if (players * 5 > deck.size()){
            System.err.printf("Too many players! Deck has only %d cards, but %d players require %d cards! \n",
                    deck.size(), players,
                    players * 5);
            System.exit(1);
        }
        System.out.println("Distributing cards...");

        for(int i = 0; i < players; i++) {
            System.out.print("Player " + (i+1) + ": ");
            for (int j = 0; j < 5; j++) {
                System.out.print(getCard() + " ");
            }
            System.out.println("\n");
        }
    }
}
