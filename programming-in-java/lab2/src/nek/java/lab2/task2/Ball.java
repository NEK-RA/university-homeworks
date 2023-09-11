package nek.java.lab2.task2;

class Ball{
  private double x = 0.0;
  private double y = 0.0;

  Ball(){}

  Ball(double x, double y){
    this.x = x;
    this.y = y;
  }

  public double getX(){
    return this.x;
  }

  public void setX(double x){
    this.x = x;
  }

  public double getY(){
    return this.y;
  }

  public void setY(double y){
    this.y = y;
  }

  public void setXY(double x, double y){
    this.x = x;
    this.y = y;
  }

  public void move(double x, double y){
    System.out.printf("Ball was at (%.5f, %.5f);",this.x, this.y);
    this.x += x;
    this.y += y;
    System.out.printf(" moved to (%.5f, %.5f)\n",this.x, this.y);
  }

  @Override
  public String toString(){
    return String.format("Ball coordinates: x=%.5f y=%.5f", this.x, this.y);
  }
}