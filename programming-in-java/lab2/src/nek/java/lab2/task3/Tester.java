package nek.java.lab2.task3;

public class Tester {
  private static int amount = 5;
  private static Circle[] objects = new Circle[amount];

  public static void main(String[] args) {
    for(int i = 0; i < amount; i++){
      objects[i] = new Circle(new Point(i*12.345/2, i*amount/(Math.sin(i)+Math.cos(i))), i+10*Math.sin(i+0.5));
    }
    boolean first = true;
    for(Circle c : objects){
      if(first){
        first = false;
      }else{
        System.out.print("Yet Another ");
      }
      System.out.println("Circle info:");
      System.out.println("Center located in (x=" + c.getCenterX() +
              "; y=" + c.getCenterY() + ")");
      System.out.println("Circle radius is " + c.getRadius());
      System.out.println("Changing all fields... (x*2, y*3, r/4)");
      c.setXY(c.getCenterX()*2, c.getCenterY()*3);
      c.setRadius(c.getRadius()/4);
      System.out.println("Final circle info:\n" + c);
      System.out.println("\n\n\n");
    }
  }
}
