package nek.java.lab2.task3;

public class Circle {
  private Point center;
  private double radius = 0.0;

  Circle(){
    center = new Point(0.0, 0.0);
  }

  Circle(Point center, double radius){
    this.center = center;
    this.radius = Math.abs(radius);
  }

  public double getRadius(){
    return this.radius;
  }

  public void setRadius(double radius){
    this.radius = radius;
  }

  public void setXY(double x, double y){
    this.center.setXY(x, y);
  }

  public double getCenterX(){
    return this.center.getX();
  }

  public double getCenterY(){
    return this.center.getY();
  }

  @Override
  public String toString(){
    return String.format("Окружность с центром в (%.5f, %.5f) и радиусом r=%.5f", this.center.getX(),
            this.center.getY(), this.radius);
  }
}
