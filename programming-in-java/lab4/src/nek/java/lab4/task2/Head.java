package nek.java.lab4.task2;

public class Head {
  public final String eyesColor;
  private String hairStyle;

  public Head(String eyesColor, String hairs){
    this.eyesColor = eyesColor;
    this.hairStyle = hairs;
  }

  public String getHairStyle(){
    return this.hairStyle;
  }

  public void setHairStyle(String style){
    this.hairStyle = style;
  }

  public void say(String what, String name){
    System.out.println("%s: %s".formatted(name, what));
  }
}
