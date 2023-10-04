package nek.java.lab11;
public class Student{
  private static int nextId = 0;

  public final int idNumber;
  public final String name;
  private double score;

  public Student(String name, double score){
    this.idNumber = Student.nextId++;
    this.name = name;
    this.score = score;
  }

  public Student(int id, String name, double score){
    this.idNumber = id;
    this.name = name;
    this.score = score;
    Student.nextId = id+1;
  }

  public double getScore(){
    return this.score;
  }

  public void setScore(double newScore){
    this.score = newScore;
  }

  @Override
  public String toString(){
    return "Студент %s: id=%d, score=%.2f".formatted(this.name, this.idNumber, this.score);
  }

  public static void printStudents(Student... sts){
    for (Student student : sts) {
      System.out.println(student);
    }
  }

  public static void printIdScores(Student... sts){
    for (Student student : sts) {
      System.out.printf("id=%d: %.2f\n",student.idNumber, student.getScore());
    }
  }
}