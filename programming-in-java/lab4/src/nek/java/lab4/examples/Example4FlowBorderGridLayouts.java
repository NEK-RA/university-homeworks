package nek.java.lab4.examples;

import javax.swing.*;
import java.awt.*;

public class Example4FlowBorderGridLayouts extends JFrame {
    JPanel[] panels = new JPanel[12];

    public Example4FlowBorderGridLayouts(){
        super("Layouts with colors and buttons");

        setLayout(new GridLayout(3,4)); // строки, столбцы
        int r,g,b;
        for(int i = 0; i < panels.length; i++){
            r = (int) (Math.random() * 255);
            g = (int) (Math.random() * 255);
            b = (int) (Math.random() * 255);
            panels[i] = new JPanel();
            panels[i].setBackground(new Color(r,g,b));
            add(panels[i]);
        }

        panels[4].setLayout(new BorderLayout());
        panels[4].add(new JButton("one"), BorderLayout.WEST);
        panels[4].add(new JButton("two"), BorderLayout.EAST);
        panels[4].add(new JButton("three"), BorderLayout.SOUTH);
        panels[4].add(new JButton("four"), BorderLayout.NORTH);
        panels[4].add(new JButton("five"), BorderLayout.CENTER);

        panels[10].setLayout(new FlowLayout());
        panels[10].add(new JButton("one"));
        panels[10].add(new JButton("two"));
        panels[10].add(new JButton("three"));
        panels[10].add(new JButton("four"));
        panels[10].add(new JButton("five"));

        setSize(800, 500);
        setVisible(true);
    }

    public static void main(String[] args) {
        new Example4FlowBorderGridLayouts();
    }
}
