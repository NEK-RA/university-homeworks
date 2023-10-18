package nek.java.lab4.task2;

public class Hand {
  public final String side;
  private String state = "опущена";

  public Hand(String side){
    this.side = side;
  }

  public String getState(){
    return "%s рука: %s".formatted(this.side, this.state);
  }

  public void setState(String state){
    this.state = state;
  }
}
