package nek.java.lab2.task7;

public class BookShelf {
  public final int capacity;
  private int amount;
  private final Book[] books;

    public BookShelf(int capacity) {
        this.capacity = capacity;
        this.books = new Book[capacity];
        this.amount = 0;
    }

    public int getAmount() {
        return amount;
    }

    public Book[] getBooks() {
        return books;
    }

    public void addBook(Book book){
        if(amount < capacity){
            this.books[amount] = book;
            amount++;
        }else{
            System.out.println("No space left for new books");
        }
    }

    public Book getOlderBook(){
        Book olderBook = this.books[0];
        for(Book book : this.books){
            if(book.getPublishedAt() < olderBook.getPublishedAt()){
                olderBook = book;
            }
        }
        return olderBook;
    }

    public Book getNewerBook(){
        Book newerBook = this.books[0];
        for(Book book : this.books){
            if(book.getPublishedAt() > newerBook.getPublishedAt()){
                newerBook = book;
            }
        }
        return newerBook;
    }

    @Override
    public String toString() {
        String output = "BookShelf begin:\n-------------------------------\n";
        for(Book b : this.books){
            output += String.format("%s - %s (%d)\n", b.getAuthor().getName(), b.getTitle(), b.getPublishedAt());
        }
        output += "-------------------------------\nBookShelf end";
        return output;
    }
}
