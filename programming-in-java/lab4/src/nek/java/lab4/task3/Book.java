package nek.java.lab4.task3;

public class Book {
  private String author;
  private String title;
  private int writtenAt = 2023;
  private int publishedAt = 2023;
  private int pages;

  Book(String author, String bookTitle, int writtenAt, int publishedAt, int pages) {
    this.author = author;
    this.title = bookTitle;
    this.writtenAt = Math.abs(writtenAt);
    this.publishedAt = Math.abs(publishedAt);
    this.pages = pages;
  }

  public String getAuthor() {
    return author;
  }

  public void setAuthor(String name) {
    this.author = name;
  }

  public String getTitle() {
    return title;
  }

  public void setTitle(String title) {
    this.title = title;
  }

  public int getWrittenAt() {
    return writtenAt;
  }

  public void setWrittenAt(int writtenAt) {
    this.writtenAt = writtenAt;
  }

  public int getPublishedAt() {
    return publishedAt;
  }

  public void setPublishedAt(int publishedAt) {
    this.publishedAt = publishedAt;
  }

  public int getPages() {
    return pages;
  }

  public void setPages(int pages) {
    this.pages = pages;
  }

  @Override
  public String toString(){
    return String.format("Книга ,,%s``\nАвтор: %s\nНаписана в: %d году\nОпубликована в: %d году\nКол-во страниц: %d",
            this.title,
            this.author.toString(), this.writtenAt, this.publishedAt, this.pages);
  }
}
