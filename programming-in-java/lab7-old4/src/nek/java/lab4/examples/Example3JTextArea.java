package nek.java.lab4.examples;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Example3JTextArea extends JFrame {
    JTextArea jta = new JTextArea(10,25);
    JButton btn = new JButton("Add some text");
    JScrollPane jsp = new JScrollPane(jta);

    public Example3JTextArea(){
        super("JTextArea example");
        this.setSize(300,300);
        setLayout(new FlowLayout());
        // add(jta); // простое добавление JTextArea без полосы прокрутки
        add(jsp); // создав JScrollPane передав ему JTextArea получим комбо из текстового поля и полосы прокрутки
        // (полосы появятся когда текст окажется длиннее чем ширина/высота текстового поля)
        add(btn);
        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String txt = JOptionPane.showInputDialog(null, "Insert Some Text");
                jta.append(txt);
            }
        });
        setVisible(true);
    }

    public static void main(String[] args) {
        new Example3JTextArea();
    }
}
