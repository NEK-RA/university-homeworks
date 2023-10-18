package nek.java.lab4.task2;

public class Human {
  final String name;

  public final Hand leftHand = new Hand("Левая");
  public final Hand rightHand = new Hand("Правая");

  public final Leg leftLeg = new Leg("Левая", 35);
  public final Leg rightLeg = new Leg("Правая", 34);

  public final Head head;

  public Human(String name,String eyesColor, String hairs){
    this.name = name;
    this.head = new Head(eyesColor, hairs);
  }

  public void introduce(){
    this.head.say("Меня зовут %s".formatted(this.name), this.name);
  }

  public void say(String smth){
    this.head.say(smth, this.name);
  }

  public void goForward(int steps){
    for(int i = 0; i < steps; i++){
      if(i % 2 == 0){
        rightLeg.stepForward();
      }else{
        leftLeg.stepForward();
      }
    }
  }
}
