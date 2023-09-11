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
        System.out.println("Dog list at the beginning: "+dogs);

        addDogs(new Dog("Test1", 3), new Dog("Test2", 9));
        System.out.println("Dog list after 2 dogs added: "+dogs);

        System.out.println("First dog before changes: " + dogs.getFirst());
        System.out.println("Human age of it: " + dogs.getFirst().getHumanAge() + " year");
        dogs.getFirst().setNickname("Firrrst");
        dogs.getFirst().setAge(14);
        System.out.println("Changed data of first dog: " + dogs.getFirst());
        System.out.println("And it's human age: " + dogs.getFirst().getHumanAge());

        System.out.println("\n\n");
        addDogs(
                new Dog("Test dog M", 5.5),
                new Dog("Test dog N", 15),
                new Dog("Test dog X", 2),
                new Dog("Test dog Y", 6),
                new Dog("Test dog Z", 7)
        );
        System.out.println("Dog list after 5 more dogs added: "+dogs);
    }

}
