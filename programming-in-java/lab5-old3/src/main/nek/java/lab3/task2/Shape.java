package nek.java.lab3.task2;

public abstract class Shape {
  protected String color;
  protected boolean filled;

  public Shape() {
    this.color = "#000000";
    this.filled = true;
  }

  public Shape(String color, boolean filled) {
    this.color = color;
    this.filled = filled;
  }

  public String getColor() {
    return this.color;
  }

  public boolean isFilled() {
    return this.filled;
  }

  public void setColor(String color) {
    this.color = color;
  }

  public void setFilled(boolean filled) {
    this.filled = filled;
  }

  public abstract double getArea();

  public abstract double getPerimeter();

  public String toString() {
    return String.format("Shape{color=%s, filled=%b}", this.color, this.filled);
  }
}