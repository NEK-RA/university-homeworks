package nek.java.lab1.task1;

public class DogTester {
  public static void main(String[] args) {
    Dog test = new Dog("Белка", 3.54f);
    System.out.println("Имя: "+test.getName());
    System.out.println("Возраст: "+test.getAge());
    test.setAge(5.2f);
    test.setName("Стрелка");
    System.out.println("После изменений:");
    System.out.println("Имя: "+test.getName());
    System.out.println("Возраст: "+test.getAge());
  }
}
