package nek.java.lab1.task2;

public class Ball {
  public final float radius;
  private String color;

  public Ball(float radius, String color) {
    this.radius = radius;
    this.color = color;
  }

  public String getColor() {
    return color;
  }

  public void setColor(String color) {
    this.color = color;
  }

}
