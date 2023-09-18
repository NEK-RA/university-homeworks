package nek.java.lab2.task8;

import java.util.Arrays;

public class StringArrayReverser {
    public static void main(String[] args) {
        String[] words = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
        System.out.println(Arrays.toString(words));
        String tmp;
        for(int i = 0; i < words.length - 1; i++){
            for(int k = 0; k < words.length - 1 - i; k++) {
                tmp = words[k];
                words[k] = words[k+1];
                words[k+1] = tmp;
//                System.out.println(String.format("i=%d, k=%d  ==>  ",i,k) + Arrays.toString(words));
            }
//            System.out.println();
        }
        System.out.println(Arrays.toString(words));
    }
}
