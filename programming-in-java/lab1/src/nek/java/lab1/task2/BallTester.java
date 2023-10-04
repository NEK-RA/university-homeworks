package nek.java.lab1.task2;

public class BallTester {
  public static void main(String[] args) {
    Ball test = new Ball(13.76f, "Красный");
    System.out.println("Диаметр мяча: " + test.radius*2);
    System.out.println("Цвет мяча: " + test.getColor());
    System.out.println("Перекраска...");
    test.setColor("Синий");
    System.out.println("Цвет мяча: " + test.getColor());
  }
}
