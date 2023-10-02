package nek.java.lab2.task4;

import java.util.LinkedList;
import java.util.Scanner;
import java.util.stream.Collectors;

public class Shop implements Searchable {
    private LinkedList<PC> items = new LinkedList<>();
    private String name;

    Shop(String name){
        this.name = name;
        System.out.println("Магазин с названием \"" + this.name + "\" был создан");
    }

    public void addPC(){
        String cpu;
        String gpu;
        String gpuType;
        boolean external;
        double price;
        Scanner sc = new Scanner(System.in);
        System.out.println("Укажите модель процессора: ");
        cpu = sc.nextLine();
        System.out.println("Укажите модель видеокарты: ");
        gpu = sc.nextLine();
        System.out.println("Укажите тип видеокарты ([I]Интегрированная или [E]Дискретная): ");
        do{
            System.out.print("Пожалуйста укажите ответ заглавной английской буквой: ");
            gpuType = sc.nextLine();
        }while(gpuType.charAt(0) != 'I' && gpuType.charAt(0) != 'E');
        external = gpuType.charAt(0) == 'E';
        System.out.println("Укажите цену ПК: ");
        price = sc.nextDouble();
        this.items.add(new PC(cpu, gpu, external, price));
    }

    public void removePC(PC target){
        items.remove(target);
    }

    @Override
    public PC[] searchByPriceBetween(double lower, double higher) {
        return this.items.stream()
                .filter(pc -> pc.getPrice() >= lower && pc.getPrice() <= higher)
                .collect(Collectors.toList()).toArray(new PC[0]);
    }

    @Override
    public String toString(){
        String data = "";
        for(PC pc : items){
            data += pc.toString();
            data += "\n\n";
        }
        return "Список ПК в магазине:\n"+data;
    }
}
