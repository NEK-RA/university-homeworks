package nek.java.lab3.task1;

public class Circle extends AbstractShape {
  private double radius;

  public Circle(double r) {
    this.radius = r;
  }

  public double getRadius() {
    return radius;
  }

  public void setRadius(double radius) {
    this.radius = radius;
  }

  @Override
  double getArea() {
    return Math.PI * radius * radius;
  }

  @Override
  double getPerimeter() {
    return 2 * Math.PI * radius;
  }

}
