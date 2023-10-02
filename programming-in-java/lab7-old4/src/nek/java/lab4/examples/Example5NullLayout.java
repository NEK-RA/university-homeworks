package nek.java.lab4.examples;

import javax.swing.*;

public class Example5NullLayout extends JFrame {
    JButton jb1 = new JButton("ONE");
    JButton jb2 = new JButton("TWO");
    JButton jb3 = new JButton("THREE");

    public Example5NullLayout(){
        super("NullLayout example for pixel-perfect composition");
        jb1.setBounds(150, 300, 100, 20); // setBounds объединяет в себе setLocation и setSize
        jb2.setSize(80,400);
        jb3.setLocation(300,100);
        jb3.setSize(100,75);
        add(jb1);
        add(jb2);
        add(jb3);
        setSize(500,500);
        setVisible(true);
    }

    public static void main(String[] args) {
        new Example5NullLayout();
    }
}
