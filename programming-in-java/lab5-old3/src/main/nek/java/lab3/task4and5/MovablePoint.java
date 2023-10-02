package nek.java.lab3.task4and5;

// Task 4
public class MovablePoint implements Movable {
  protected int x;
  protected int y;
  protected int xSpeed;
  protected int ySpeed;

  public MovablePoint(int x, int y, int xSpeed, int ySpeed){
    this.x = x;
    this.y = y;
    this.xSpeed = xSpeed;
    this.ySpeed = ySpeed;
  }

  @Override
  public String toString(){
    return String.format("MovablePoint{x=%d, y=%d, xSpeed=%d, ySpeed=%d}", x, y, xSpeed, ySpeed);
  }

  public void moveUp(){
    this.y++;
  }

  public void moveDown(){
    this.y--;
  }

  public void moveLeft(){
    this.x--;
  }

  public void moveRight(){
    this.x++;
  }
}
