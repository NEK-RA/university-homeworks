package nek.java.lab1.task3;

public class BookTester {
  public static void main(String[] args) {
    Book first = new Book("First book", "First author", 2023, 125);
    System.out.println("Автор: " + first.author);
    System.out.println("Название: "+ first.title);
    System.out.println("Опубликовано: " + first.published);
    System.out.println("Продолжительность (страниц): " + first.length);
  }
}
