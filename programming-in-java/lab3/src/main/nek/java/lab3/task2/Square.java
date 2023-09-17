package nek.java.lab3.task2;

public class Square extends Rectangle {
  public Square(){
    super(1,1,"#000000",true);
  }

  public Square(double side){
    super(side, side, "#000000", true);
  }

  public Square(double side, String color, boolean filled){
    super(side, side, color, filled);
  }

  public double getSide(){
    return this.getWidth();
  }

  public void setSide(double side){
    this.setWidth(side);
    this.setHeight(side);
  }

  @Override
  public void setWidth(double side){
    this.setSide(side);
  }

  @Override
  public void setHeight(double side){
    this.setSide(side);
  }

  @Override
  public String toString(){
    return String.format("Square{side=%.5f, color=%s, filled=%b}", this.getWidth(), this.getColor(), this.isFilled());
  }
}
