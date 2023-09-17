package nek.java.lab4.examples;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

public class Example2JButton extends JFrame {
  JTextField jtf1 = new JTextField(10);
  JTextField jtf2 = new JTextField(10);
  JButton jb = new JButton(" Add them up ");
  Font fnt = new Font("Times New Roman", Font.BOLD, 20);

  public Example2JButton(){
    super("Example 2");
    setLayout(new FlowLayout());
    setSize(250, 150);
    add(new JLabel("1st number"));
    add(jtf1);
    add(new JLabel("2nd number"));
    add(jtf2);
    add(jb);
    jb.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
        try{
          double x1 = Double.parseDouble(jtf1.getText().trim());
          double x2 = Double.parseDouble(jtf2.getText().trim());
          JOptionPane.showMessageDialog(null, "Result = " + (x1 + x2), "Message Dialog Title",
                  JOptionPane.INFORMATION_MESSAGE);
        }catch (Exception ex){
          JOptionPane.showMessageDialog(null, "Error in numbers!", "Error dialog title", JOptionPane.ERROR_MESSAGE);
        }
      }
    });
    setVisible(true);
  }

  public static void main(String[] args) {
    new Example2JButton();
  }
}