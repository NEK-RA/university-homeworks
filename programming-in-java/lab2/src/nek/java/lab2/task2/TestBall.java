package nek.java.lab2.task2;

public class TestBall {
  public static void main(String[] args) {
    Ball b = new Ball();
    for(int i = 0; i < 5; i++){
      b.move(Math.sin(i)*10*i, Math.cos(i)*50);
    }
    System.out.printf("Last ball coordinates: x=%.5f y=%.5f\n",b.getX(),b.getY());
    b.setX(123);
    System.out.println("X coordinate changed to "+b.getX());
    b.setY(321);
    System.out.println("Y coordinate changed to "+b.getY());
    b.setXY(11, 22);
    System.out.println("Ball position was set for both coordinates: "+b.toString());
  }
}
