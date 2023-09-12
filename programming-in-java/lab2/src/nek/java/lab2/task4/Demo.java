package nek.java.lab2.task4;

import java.util.Scanner;

public class Demo {
    public static void main(String[] args) {
        Shop shop = new Shop("SkyNet Computing");
        Scanner sc = new Scanner(System.in);
        System.out.println("Сколько ПК вы хотите добавить: ");
        int amount = 0;
        while(!sc.hasNextInt()){
            sc.next();
        }
        amount = sc.nextInt();
        for(int i = 0; i < amount; i++){
            shop.addPC();
            System.out.println("\n\n");
        }

        System.out.println(shop);

        double targetLowerPrice = 0.0;
        double targetHigherPrice = 0.0;

        System.out.println("Укажите нижний порог цены: ");
        while(!sc.hasNextDouble()){
            sc.next();
        }
        targetLowerPrice = sc.nextDouble();

        System.out.println("Укажите верхний порог цены: ");
        while(!sc.hasNextDouble()){
            sc.next();
        }
        targetHigherPrice = sc.nextDouble();

        PC[] searchResults = shop.searchByPriceBetween(targetLowerPrice, targetHigherPrice);

        if(searchResults.length > 0) {
            System.out.println("Результаты поиска:");
            for (PC pc : searchResults) {
                System.out.println(pc + "\n");
            }
            shop.removePC(searchResults[0]);
            System.out.println("После удаления:\n" + shop);
        }else{
            System.out.println("В магазине не нашлось ПК, соответствующего ценовому запросу");
        }

    }
}
