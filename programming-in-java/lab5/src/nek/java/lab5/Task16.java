package nek.java.lab5;

import java.util.ArrayList;
import java.util.Scanner;

public class Task16 {
  public static ArrayList<Integer> getNumbers(){
    ArrayList<Integer> nums = new ArrayList<>();
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    in.nextLine();
    nums.add(n);
    if(n == 0){
      return nums;
    }
    nums.addAll(getNumbers());
    return nums;
  }

  public static int findMax(ArrayList<Integer> nums, int from, int to){
    if(from + 1 == to){
      return Math.max(nums.get(from),nums.get(to));
    }else{
      return Math.max(nums.get(from), findMax(nums, from+1, to));
    }
  }
  public static int countMax(ArrayList<Integer> nums, int from, int to, Integer max){
    if(max == null){
      max = findMax(nums,0, nums.size() - 1);
    }
    if(from == to){
      return nums.get(from).equals(max) ? 1 : 0;
    }
    else{
      int count = countMax(nums, from+1, to, max);
      return nums.get(from).equals(max) ? count + 1 : count;
    }
  }

  public static int countMax(ArrayList<Integer> nums){
    return countMax(nums, 0, nums.size() - 1, null);
  }


  public static void main(String[] args) {
    System.out.println("Количество элементов, равных максимальному: " + countMax(getNumbers()));
  }
}
