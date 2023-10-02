package nek.java.lab2.task6;

public class CircleTester {
  public static void main(String[] args) {
    Circle c1 = new Circle();
    Circle c2 = new Circle(1.5, 9.9, 1.2);

    System.out.printf("Окружность1: %s с площадью: %.5f и длиной: %.5f\n", c1.toString(), c1.getSquare(),
            c1.getLength());

    System.out.printf("Окружность2: %s с площадью: %.5f и длиной: %.5f\n", c2.toString(), c2.getSquare(),
            c2.getLength());

    byte squareComp = c1.compareBySquare(c2);
    switch(squareComp){
      case 0:
        System.out.println("Окружности имеют одинаковую площадь");
        break;
      
      case 1:
        System.out.println("Окружность1 имеет большую площадь, чем Окружность2");
        break;
      
      case -1:
        System.out.println("Окружность2 имеет большую площадь, чем Окружность1");
        break;
    }
    System.out.println("\n\nИзменяем радиус Окружность1 (r -> r+1)");
    c1.setRadius(c1.getRadius()+1);
    System.out.printf("Окружность1: %s с площадью: %.5f и длиной: %.5f\n", c1.toString(), c1.getSquare(),
            c1.getLength());
    System.out.printf("Окружность2: %s с площадью: %.5f и длиной: %.5f\n\n", c2.toString(), c2.getSquare(),
            c2.getLength());

    byte lengthComp = c1.compareByLength(c2); 
    switch(lengthComp){
      case 0:
        System.out.println("Окружности имеют одинаковую длину");
        break;
      
      case 1:
        System.out.println("Окружность1 длиннее, чем Окружность2");
        break;
      
      case -1:
        System.out.println("Окружность2 длиннее Окружность1");
        break;
    } 
  }
}
