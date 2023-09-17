package nek.java.lab4.examples;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;

import javax.swing.JFrame;
import javax.swing.JTextField;

public class Example1JTextField extends JFrame{
  JTextField jtf = new JTextField(10);
  Font fnt = new Font("Times New Roman", Font.BOLD, 20);

  public Example1JTextField(){
    super("Example 1");
    setLayout(new FlowLayout());
    setSize(250, 100);
    add(jtf);
    jtf.setForeground(Color.RED);
    jtf.setFont(fnt);
    setVisible(true);
  }

  public static void main(String[] args) {
    new Example1JTextField();
  }
}
