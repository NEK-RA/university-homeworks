package nek.java.lab3.task2;

public class Circle extends Shape {
  private double radius;

  public Circle(){
    super("#000000", true);
    this.radius = 1.0;
  }

  public Circle(double radius) {
    super("#000000", true);
    this.radius = radius;
  }

  public Circle(double radius, String color, boolean filled){
    super("#000000", true);
    this.radius = radius;
  }

  public double getRadius() {
    return radius;
  }

  public void setRadius(double radius) {
    this.radius = radius;
  }

  @Override
  public double getArea() {
    return Math.PI * radius * radius;
  }

  @Override
  public double getPerimeter() {
    return 2 * Math.PI * radius;
  }

  @Override
  public String toString(){
    return String.format("Circle{radius=%s, color=%s, filled=%b}", this.radius, this.getColor(), this.isFilled());
  }

}
