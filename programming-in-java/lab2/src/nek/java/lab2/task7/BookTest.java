package nek.java.lab2.task7;

import java.util.Random;

public class BookTest {

  static Book generate(){
    String characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    Random rand = new Random();
    int maxAuthorName = 10;

    String authorName = "";
    String mail = "";
    char gender = rand.nextInt(2) == 1? 'M':'F';
    String bookTitle = "";
    int writtenAt = rand.nextInt(1024)+1000;
    int publishedAt = rand.nextInt(20)+writtenAt;
    int amountPages = rand.nextInt(500)+100;

    for(int i = 0; i < rand.nextInt(maxAuthorName)+10; i++){
      authorName += characters.charAt(rand.nextInt(characters.length()));
    }
    authorName += "(ИмяАвтора)";
    
    for(int i = 0; i < 20; i++){
      if(i != 0){
        if(i % 10 == 0){
          mail += "@";
        }
      }
      if(20 - i == 3){
        mail += ".";
      }
      mail += characters.charAt(rand.nextInt(characters.length()/2));
    }

    for(int i = 0; i < rand.nextInt(30)+10; i++){
      if(i % 10 == 0 && i != 0){
        bookTitle += " ";
        i++;
      }
      bookTitle += characters.charAt(rand.nextInt(characters.length()));
    }
    bookTitle += "(Наименование)";
    
    return new Book(authorName, mail, gender, bookTitle,writtenAt, publishedAt,amountPages);
  }

  public static void main(String[] args) {
    Book test = generate();
    System.out.println("Информация о тестовой книге:");
    System.out.println("Наименование: " + test.getTitle());
    System.out.println("Написана в: " + test.getWrittenAt() + " году");
    System.out.println("Опубликована в: " + test.getPublishedAt() + " году");
    System.out.println("Кол-во страниц: " + test.getPages());
    System.out.println("Информация об авторе:\n" + test.getAuthor());

    System.out.println("\nИзменяем наименование...");
    test.setTitle("Читаемое наименование");
    System.out.println(test);

    System.out.println("\n\n\n\n\n");
    System.out.println("Создаем книжную полку...\n");

    BookShelf bs = new BookShelf(5);
    for(int i = 0; i < bs.capacity; i++){
      bs.addBook(generate());
    }
    System.out.println(bs);

    System.out.println("\nНаиболее поздняя из опубликованных книг:\n" + bs.getNewerBook());
    System.out.println("\nНаиболее ранняя из опубликованных книг:\n" + bs.getOlderBook());
  }
}
