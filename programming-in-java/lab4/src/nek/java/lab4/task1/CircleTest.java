package nek.java.lab4.task1;

public class CircleTest {
  public static void main(String[] args) {
    Circle tc = new Circle(4.32, 8.59, 4.0);
    System.out.println("Радиус: %.2f\nКоординаты центра: (%.2f, %.2f)".formatted(tc.getRadius(), tc.getX(), tc.getY()));

    System.out.println("\nИзменяем все параметры...");
    tc.setX(10);
    tc.setY(-10);
    tc.setRadius(-5);
    System.out.println("При задании отрицательного радиуса будет использован его модуль\n");

    System.out.println("Радиус: %.2f\nКоординаты центра: (%.2f, %.2f)".formatted(tc.getRadius(), tc.getX(), tc.getY()));
  }
}
