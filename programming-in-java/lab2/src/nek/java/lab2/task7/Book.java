package nek.java.lab2.task7;

import nek.java.lab2.task1.Author;

public class Book {
  private Author author;
  private String title;
  private int writtenAt = 2023;
  private int publishedAt = 2023;
  private int pages;

  Book(String author, String email, char gender, String bookTitle, int writtenAt, int publishedAt, int pages) {
    this.author = new Author(author, email, gender);
    this.title = bookTitle;
    this.writtenAt = Math.abs(writtenAt);
    this.publishedAt = Math.abs(publishedAt);
    this.pages = pages;
  }

  public Author getAuthor() {
    return author;
  }

  public void setAuthor(String name, String mail, char gender) {
    this.author = new Author(name, mail, gender);
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
    return String.format("Book ,,%s``\nAuthor: %s\nWritten at: %d\nPublished at: %d\nAmount of pages: %d", this.title, this.author.toString(), this.writtenAt, this.publishedAt, this.pages);
  }
}
