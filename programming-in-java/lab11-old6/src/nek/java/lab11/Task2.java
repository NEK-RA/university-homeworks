package nek.java.lab11;

public class Task2 {

  static String[] lastNames = {
    "Иванов",
    "Петров",
    "Сидоров",
    "Федоров",
    "Соколов",
    "Андреев",
    "Александров",
    "Сергеев",
    "Михайлов",
    "Егоров"
  };

  // static void test(){
  //   Student[] stds = new Student[lastNames.length];
  //   for(int i = 0; i < lastNames.length; i++){
  //     stds[i] = new Student(
  //       i+1,
  //       lastNames[i],
  //      Math.random()*2 + 3
  //     );
  //   }
  //   Student.printIdScores(stds);
  //   System.out.println("\nSorting...\n");
  //   SortingStudentsByGPA compsort = new SortingStudentsByGPA();
  //   compsort.quickSort(stds, null, null);
  //   Student.printIdScores(stds);
  // }

  static void anomalyTest(){
    Student[] s = new Student[]{
      new Student("", 3.35),
      new Student("", 3.10),
      new Student("", 3.62),
      new Student("", 3.22),
      new Student("", 4.63),
      new Student("", 3.06),
      new Student("", 3.82),
      new Student("", 4.86),
      new Student("", 3.24),
      new Student("", 3.19),
    };
    Student.printIdScores(s);
    System.out.println("Sorting ... \n");
    SortingStudentsByGPA compsort = new SortingStudentsByGPA();
    compsort.quickSort(s, null, null);
    Student.printIdScores(s);
  }

  public static void main(String[] args) {
    // for(int i : new int[]{1,2,3}){
    //   System.out.println("Iteration "+i);
    //   test();
    //   System.out.println("\n\n\n");
    // }
    anomalyTest();
  }
}
