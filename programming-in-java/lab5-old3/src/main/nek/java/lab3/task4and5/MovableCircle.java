package nek.java.lab3.task4and5;

// Task 4
public class MovableCircle implements Movable {
  private int radius;
  private MovablePoint center;

  public MovableCircle(int x, int y, int xSpeed, int ySpeed, int radius){
    this.radius = radius;
    this.center = new MovablePoint(x,y,xSpeed, ySpeed);
  }

  @Override
  public String toString(){
    return String.format("MovableCircle{radius=%d, x=%d, y=%d, xSpeed=%d, ySpeed=%d}", radius, center.x, center.y, center.xSpeed, center.ySpeed);
  }

  public void moveUp(){
    this.center.moveUp();
  }

  public void moveDown(){
    this.center.moveDown();
  }

  public void moveLeft(){
    this.center.moveLeft();
  }

  public void moveRight(){
    this.center.moveRight();
  }
}
