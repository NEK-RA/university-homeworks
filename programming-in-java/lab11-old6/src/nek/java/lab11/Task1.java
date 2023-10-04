package nek.java.lab11;

public class Task1 {
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
    "Егоров",
    "Кириллов",
    "Николаев",
    "Орлов",
    "Козлов",
    "Степанов",
    "Семенов",
    "Виноградов",
    "Воробьев",
    "Кузьмин",
    "Макаров"
  };

  static void injectionSort(Student[] sts){
    if(sts.length > 1){
      Student tmp;
      boolean lg;
      int from;
      for(int i = 1; i < sts.length; i ++){
        tmp = sts[i];
        from = i;
        for(int j = i-1; j >= 0; j--){
          lg = sts[j].idNumber > tmp.idNumber;
          if(lg){
            System.out.println("%s > %s ? %b(поле idNumber)".formatted(sts[j], tmp, lg));
            from--;
          }
        }
        if(from != i){
          System.out.println("%s moved to index %d".formatted(tmp, from));
          moveRight(sts, from, i);
          sts[from] = tmp;
          System.out.println();
        }
      }
    }
  }

  static void moveRight(Student[] s, int begin, int end){
    if(begin >= 0 && end <= s.length-1 && begin <= end){
      for(int i = end; i > begin; i--){
        s[i] = s[i-1];
      }
    }
  }
  
  public static void main(String[] args) {
    Student[] stds = new Student[lastNames.length];
    for(int i = 0; i < lastNames.length; i++){
      stds[i] = new Student(
              10-i,
        lastNames[i],
              i+1
//        Math.random()*2 + 3
      );
    }
    stds[3].setScore(0.5);

    Student.printStudents(stds);
    System.out.println();
    injectionSort(stds);
    System.out.println();
    Student.printStudents(stds);
  }
}
