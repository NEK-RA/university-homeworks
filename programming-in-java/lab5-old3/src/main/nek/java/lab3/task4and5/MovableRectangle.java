package nek.java.lab3.task4and5;

// Task 5
public class MovableRectangle implements Movable{
  MovablePoint leftTop;
  MovablePoint rightBottom;

  public MovableRectangle(int x1, int y1, int x2, int y2, int xSpeed, int ySpeed){
    this.leftTop = new MovablePoint(x1, y1, xSpeed, ySpeed);
    this.rightBottom = new MovablePoint(x2, y2, xSpeed, ySpeed);
  }

  boolean isPointSpeedSame(){
    return (leftTop.xSpeed == rightBottom.xSpeed) && (leftTop.ySpeed == rightBottom.ySpeed);
  }

  public void moveUp(){
    this.leftTop.moveUp();
    this.rightBottom.moveUp();
  }

  public void moveDown(){
    this.leftTop.moveDown();
    this.rightBottom.moveDown();
  }

  public void moveLeft(){
    this.leftTop.moveLeft();
    this.rightBottom.moveLeft();
  }

  public void moveRight(){
    this.leftTop.moveRight();
    this.rightBottom.moveRight();
  }
}
