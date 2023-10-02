package nek.java.lab3.task2;

public class Rectangle extends Shape {
  private double width;
  private double height;

  public Rectangle(){
    super("#000000", true);
    this.width = 3;
    this.height = 1;
  }

  public Rectangle(double width, double height) {
    super("#000000", true);
    this.width = width;
    this.height = height;
  }

  public Rectangle(double width, double height, String color, boolean filled){
    super(color, filled);
    this.height = height;
    this.width = width;
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
  public double getArea() {
    return width * height;
  }

  @Override
  public double getPerimeter() {
    return (width+height)*2;
  }

  @Override
  public String toString(){
    return String.format("Rectangle{width=%s, height=%s, color=%s, filled=%b}", this.width, this.height, this.getColor(), this.isFilled());
  }
}
