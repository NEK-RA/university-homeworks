package nek.java.lab4.task2;

public class HumanTest {
  public static void main(String[] args) {
    Human test = new Human("Алексей", "зеленые", "кудрявые");
    test.introduce();
    test.say("Hello world!");
    System.out.println();
    test.goForward(3);
    System.out.println();
    test.leftHand.setState("в кармане");
    test.rightHand.setState("поднята");
    System.out.println(test.leftHand.getState());
    System.out.println(test.rightHand.getState());
  }
}
