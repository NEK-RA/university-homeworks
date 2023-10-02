package nek.java.lab2.task6;

public class Circle {
  private double centerX = 0.0;
  private double centerY = 0.0;
  private double radius = 1.0;

  Circle() {
  }

  Circle(double x, double y, double r) {
    this.centerX = x;
    this.centerY = y;
    this.radius = r;
  }

  public double getCenterX() {
    return centerX;
  }

  public void setCenterX(double centerX) {
    this.centerX = centerX;
  }

  public double getCenterY() {
    return centerY;
  }

  public void setCenterY(double centerY) {
    this.centerY = centerY;
  }

  public double getRadius() {
    return radius;
  }

  public void setRadius(double radius) {
    this.radius = radius;
  }

  public double getSquare(){
    return Math.PI*Math.pow(this.radius, 2);
  }

  public double getLength(){
    return 4 * Math.PI * this.radius;
  }

  public byte compareBySquare(Circle another){
    byte res = 0;
    double s1 = this.getSquare();
    double s2 = another.getSquare();
    if(s1 > s2){
      res = 1;
    }else if(s2 > s1){
      res = -1;
    }
    return res;
  }

  public byte compareByLength(Circle another){
    byte res = 0;
    double s1 = this.getLength();
    double s2 = another.getLength();
    if(s1 > s2){
      res = 1;
    }else if(s2 > s1){
      res = -1;
    }
    return res;
  }

  @Override
  public String toString(){
    return String.format("Окружность {центрX=%.5f, центрY=%.5f, радиус=%.5f}", this.centerX, this.centerY,
            this.radius);
  }
}
