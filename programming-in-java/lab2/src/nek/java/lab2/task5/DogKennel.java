package nek.java.lab2.task5;

import java.util.LinkedList;

public class DogKennel {
    static LinkedList<Dog> dogs = new LinkedList<>();

    public static void addDogs(Dog ...newDogs){
        for(Dog dog : newDogs){
            dogs.add(dog);
        }
    }

    public static void main(String[] args) {
        System.out.println("Изначальный список собак: "+dogs);

        addDogs(new Dog("ТестКличка", 3), new Dog("ТестПрозвище", 9));
        System.out.println("Список собак после добавления 2-х собак: "+dogs);

        System.out.println("Первая собака до изменений: " + dogs.getFirst());
        System.out.println("Человеческий возраст: " + dogs.getFirst().getHumanAge() + " лет");
        dogs.getFirst().setNickname("Перррвая");
        dogs.getFirst().setAge(14);
        System.out.println("Изменены данные для первой собаки: " + dogs.getFirst());
        System.out.println("И ее человеческий возраст: " + dogs.getFirst().getHumanAge());

        System.out.println("\n\n");
        addDogs(
                new Dog("Test dog M", 5.5),
                new Dog("Test dog N", 15),
                new Dog("Test dog X", 2),
                new Dog("Test dog Y", 6),
                new Dog("Test dog Z", 7)
        );
        System.out.println("Список собак после 5 добавлений: "+dogs);
    }

}
