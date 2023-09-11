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
    authorName += "(AuthorName)";
    
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
    bookTitle += "(Title)";
    
    return new Book(authorName, mail, gender, bookTitle,writtenAt, publishedAt,amountPages);
  }

  public static void main(String[] args) {
    Book test = generate();
    System.out.println("Test book info:");
    System.out.println("Title: " + test.getTitle());
    System.out.println("Written: " + test.getWrittenAt() + " year");
    System.out.println("Published: " + test.getPublishedAt() + " year");
    System.out.println("Amount of pages: " + test.getPages());
    System.out.println("Author info:\n" + test.getAuthor());

    System.out.println("\nChanging title...");
    test.setTitle("New Title");
    System.out.println(test);

    System.out.println("\n\n\n\n\n");
    System.out.println("Making a bookshelf...\n");

    BookShelf bs = new BookShelf(5);
    for(int i = 0; i < bs.capacity; i++){
      bs.addBook(generate());
    }
    System.out.println(bs);

    System.out.println("\nThe most recent book published:\n" + bs.getNewerBook());
    System.out.println("\nThe most old book published:\n" + bs.getOlderBook());
  }
}
