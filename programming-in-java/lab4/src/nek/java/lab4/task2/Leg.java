package nek.java.lab4.task2;

public class Leg {
  private int size;
  public final String side;

  public Leg(String side, int size) {
    this.side = side;
    this.size = size >= 0 ? size : size * (-1);
  }

  public int getSize() {
    return size;
  }

  public void setSize(int size) {
    this.size = size >= 0 ? size : size * (-1);
  }

  public void stepForward(){
    System.out.println("%s нога шагнула вперед".formatted(this.side));
  }

}
