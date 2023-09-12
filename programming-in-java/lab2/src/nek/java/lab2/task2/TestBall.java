package nek.java.lab2.task2;

public class TestBall {
  public static void main(String[] args) {
    Ball b = new Ball();
    for(int i = 0; i < 5; i++){
      b.move(Math.sin(i)*10*i, Math.cos(i)*50);
    }
    System.out.printf("Последние координаты мяча: x=%.5f y=%.5f\n",b.getX(),b.getY());
    b.setX(123);
    System.out.println("Координата X изменена на "+b.getX());
    b.setY(321);
    System.out.println("Координата Y изменена на "+b.getY());
    b.setXY(11, 22);
    System.out.println("Обе координаты были изменены: "+b.toString());
  }
}
