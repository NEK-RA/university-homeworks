package nek.java.lab2.task1;

public class TestAuthor {
  public static void main(String[] args) {
    String name = "Тестовое Имя";
    String email = "test@email";
    String gender = "М";
    
    Author a = new Author(name, email, gender.charAt(0));
    System.out.println("Имя -  " + a.getName());
    System.out.println("Почта до изменения - " + a.getEmail());
    email = "public@email";
    a.setEmail(email);
    System.out.printf("Пол - \"%c\"\n", a.getGender());
    System.out.println("Вся информация об авторе:\n" + a);
  }
  
}
