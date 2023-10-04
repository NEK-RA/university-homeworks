package nek.java.lab11;

import java.util.ArrayList;

public class Task3{

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

/*
Алгоритм сортировка слиянием (Merge Sort).
Состоит из последовательного выполнения трех шагов:

- разделить массив A[1..n] на 2 равные части;
- провести сортировку слиянием двух подмассивов (рекурсивно);
- объединить (соединить) два отсортированных подмассива.
*/

  static ArrayList<Student> mergeSort(ArrayList<Student> s){
    if(s.size() == 1){
      return s;
    }
    ArrayList<Student> left = new ArrayList<>();
    ArrayList<Student> right = new ArrayList<>();
    int mid = s.size() / 2;
    for(int i = 0; i < s.size(); i++){
      if (i < mid){
        left.add(s.get(i));
      }else{
        right.add(s.get(i));
      }
    }

    left = mergeSort(left);
    right = mergeSort(right);
    s.clear();
    s = merge(left, right);
    return s;
  }

  static ArrayList<Student> merge(ArrayList<Student> left, ArrayList<Student>right){
    int li = 0;
    int ri = 0;
    ArrayList<Student> res = new ArrayList<>();
    while(li < left.size() && ri < right.size()){
      if(left.get(li).getScore() > right.get(ri).getScore()){
        res.add(left.get(li));
        li++;
      }else{
        res.add(right.get(ri));
        ri++;
      }
    }

    ArrayList<Student> others;
    int oi;
    if(li >= left.size()){
      others = right;
      oi = ri;
      left.clear();
    }else{
      others = left;
      oi = li;
      right.clear();
    }
    for(int i = oi; i < others.size(); i++){
      res.add(others.get(i));
    }

    return res;
  }

  public static void main(String[] args) {
    int half = lastNames.length / 2;

    ArrayList<Student> arr1 = new ArrayList<>();
    ArrayList<Student> arr2 = new ArrayList<>();

    for(int i = 0; i < half; i++){
      arr1.add(new Student(lastNames[i], Math.random()*3+2));
      arr2.add(new Student(lastNames[i+half], Math.random()*3+2));
    }

    System.out.println("Список 1:");
    Student.printStudents(arr1.toArray(new Student[0]));
    System.out.println("Список 2:");
    Student.printStudents(arr2.toArray(new Student[0]));

    System.out.println("\nСортируем...");
    arr1 = mergeSort(arr1);
    System.out.println("Список 1 отсортирован...");
    arr2 = mergeSort(arr2);
    System.out.println("Список 2 отсортирован...");

    ArrayList<Student> total = merge(arr1, arr2);
    arr1.clear();
    arr2.clear();

    System.out.println("\nСписки объединены. Итог:");
    Student.printStudents(total.toArray(new Student[0]));

    // Student.printStudents(arr2);
    
  }
}

// Gang of four - Patterns - книга про паттерны проектирования MVC и т.д. НЕ ЧИТАТЬ НА РУССКОМ - ОЧЕНЬ ПЛОХОЙ ПЕРЕВОД