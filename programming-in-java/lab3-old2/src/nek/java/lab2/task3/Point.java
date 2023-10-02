package nek.java.lab2.task3;

public class Point {
  private double x = 0.0;
  private double y = 0.0;

  Point(){}

  Point(double x, double y){
    this.x = x;
    this.y = y;
  }

  public double getX(){
    return this.x;
  }

  public double getY(){
    return this.y;
  }

  public void setXY(double x, double y){
    this.x = x;
    this.y = y;
  }

  @Override
  public String toString(){
    return String.format("(%.5f, %.5f)", this.x, this.y);
  }
}
