package nek.java.lab4.task1;

public class Circle {
  private double radius;
  private double x;
  private double y;

  public Circle(double x, double y, double radius){
    this.x = x;
    this.y = y;
    this.radius = radius >= 0 ? radius : radius * (-1);
  }


  public double getRadius() {
    return radius;
  }

  public void setRadius(double radius) {
    this.radius = radius >= 0 ? radius : radius * (-1);
  }

  public double getX() {
    return x;
  }

  public void setX(double x) {
    this.x = x;
  }

  public double getY() {
    return y;
  }

  public void setY(double y) {
    this.y = y;
  }

}
