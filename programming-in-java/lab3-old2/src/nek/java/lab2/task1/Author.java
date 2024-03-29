package nek.java.lab2.task1;

public class Author{
  private String name;
  private String email;
  private char gender;

  public Author(String name, String email, char gender){
    this.name = name;
    this.email = email;
    this.gender = gender;
  }

  public String getName(){
    return this.name;
  }

  public String getEmail(){
    return this.email;
  }

  public void setEmail(String email){
    this.email = email;
  }

  public char getGender(){
    return this.gender;
  }

  @Override
  public String toString(){
    return "Имя: " + this.name + "\n" +
    "E-mail: " + this.email + "\n" +
    "Пол: " + this.gender;
  }
}