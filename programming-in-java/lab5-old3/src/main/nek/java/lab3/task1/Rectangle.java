package nek.java.lab3.task1;

public class Rectangle extends AbstractShape {
  private double width;
  private double height;

  public Rectangle(double w, double h) {
    this.width = w;
    this.height = h;
  }

  public double getWidth() {
    return width;
  }

  public void setWidth(double width) {
    this.width = width;
  }

  public double getHeight() {
    return height;
  }

  public void setHeight(double height) {
    this.height = height;
  }

  @Override
  double getArea() {
    return width * height;
  }

  @Override
  double getPerimeter() {
    return (width+height)*2;
  }
}
