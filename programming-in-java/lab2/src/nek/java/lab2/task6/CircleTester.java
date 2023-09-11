package nek.java.lab2.task6;

public class CircleTester {
  public static void main(String[] args) {
    Circle c1 = new Circle();
    Circle c2 = new Circle(1.5, 9.9, 1.2);

    System.out.printf("Circle1: %s with square: %.5f and length: %.5f\n", c1.toString(), c1.getSquare(), c1.getLength());

    System.out.printf("Circle2: %s with square: %.5f and length: %.5f\n", c2.toString(), c2.getSquare(), c2.getLength());

    byte squareComp = c1.compareBySquare(c2);
    switch(squareComp){
      case 0:
        System.out.println("Circles have equal square");
        break;
      
      case 1:
        System.out.println("Circle1 has larger square than Circle2");
        break;
      
      case -1:
        System.out.println("Circle2 has larger square than Circle1");
        break;
    }
    System.out.println("\n\nChanging radius of Circle1 (r -> r+1)");
    c1.setRadius(c1.getRadius()+1);
    System.out.printf("Circle1: %s with square: %.5f and length: %.5f\n", c1.toString(), c1.getSquare(), c1.getLength());
    System.out.printf("Circle2: %s with square: %.5f and length: %.5f\n\n", c2.toString(), c2.getSquare(), c2.getLength());

    byte lengthComp = c1.compareByLength(c2); 
    switch(lengthComp){
      case 0:
        System.out.println("Circles have equal length");
        break;
      
      case 1:
        System.out.println("Circle1 is longer than Circle2");
        break;
      
      case -1:
        System.out.println("Circle2 is longer than Circle1");
        break;
    } 
  }
}
