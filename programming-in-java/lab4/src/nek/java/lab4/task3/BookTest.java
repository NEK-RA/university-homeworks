package nek.java.lab4.task3;

public class BookTest {

  public static void main(String[] args) {
    Book test = new Book("Писатель", "Книга", 2000, 2001, 196);
    System.out.println("Информация о тестовой книге:");
    System.out.println("Наименование: " + test.getTitle());
    System.out.println("Написана в: " + test.getWrittenAt() + " году");
    System.out.println("Опубликована в: " + test.getPublishedAt() + " году");
    System.out.println("Кол-во страниц: " + test.getPages());
    System.out.println("Имя автора: " + test.getAuthor());

    System.out.println("\nИзменяем все...");
    test.setTitle("Басни и сказки");
    test.setAuthor("Крылов");
    test.setWrittenAt(1987);
    test.setPublishedAt(1988);
    test.setPages(372);
    System.out.println(test);
  }
}
