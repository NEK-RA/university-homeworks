package nek.java.lab11;

import java.util.Comparator;

public class SortingStudentsByGPA implements Comparator<Student> {

    @Override
    public int compare(Student o1, Student o2) {
        if (o1.getScore() > o2.getScore()){
            return 1; // по возрастанию 1, по убыванию -1
        }else if(o1.getScore() < o2.getScore()){
            return -1;
        }
        return 0;
    }

    private void swap(Student[] sts, int a, int b){
      Student tmp = sts[a];
      sts[a] = sts[b];
      sts[b] = tmp;
    }

    private int partitionHoar(Student[] sts, Integer low, Integer high){
      System.out.println("Начало разбиения");
      int i = low;
      int j = high;
      Student pivot = sts[(i + j) / 2];

      System.out.println("Разбиваем массив в диапазоне от %d до %d, индекс опорного: %d".formatted(i, j, (i + j) / 2));

      while(true){
        System.out.println("Движемся слева от i="+i);
        while(compare(sts[i], pivot) == -1){
          System.out.printf("a[%d]=%s все еще меньше чем %s\n", i, sts[i], pivot);
          i++;
        }
        System.out.printf("Нашелся a[%d]=%s значения которого >= %s\n", i, sts[i], pivot);
        System.out.println("Движемся справа от j="+j);
        while(compare(sts[j], pivot) == 1){
          System.out.printf("a[%d]=%s все еще больше чем %s\n", j, sts[j], pivot);
          j--;
        }
        System.out.printf("Нашелся a[%d]=%s значения которого <= %s\n", j, sts[j], pivot);
        if(i >= j){
          System.out.println("Индексы пересеклись, возврат значения j="+j);
          return j;
        }else{
          System.out.printf("Меняем местами a[%d] и a[%d]\n", i, j);
          swap(sts, i++, j--);
          Student.printIdScores(sts);
        }
        System.out.println();
      }
    }

    public void quickSort(Student[] sts, Integer low, Integer high){
      if(low == null){
        low = 0;
      }
      if(high == null){
        high = sts.length - 1;
      }
      if(low < high){
        int pivot = partitionHoar(sts, low, high);
        quickSort(sts, low, pivot);
        quickSort(sts, pivot+1, high);
      }
    }
}
