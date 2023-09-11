package nek.java.lab2.task1;

public class TestAuthor {
  public static void main(String[] args) {
    String name = "TestName";
    String email = "test@email";
    String gender = "M";
    
    Author a = new Author(name, email, gender.charAt(0));
    System.out.println("Name is "+ a.getName());
    System.out.println("Mail before change: ");
    email = "public@email";
    a.setEmail(email);
    System.out.printf("Gender is \"%c\"\n", a.getGender());
    System.out.println("All info about author:\n" + a);
  }
  
}
