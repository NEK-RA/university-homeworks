package nek.java.lab4.examples;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class Example6MouseListenerAndMenu extends JFrame {
    JLabel jl = new JLabel("");
    JMenuBar jmb = new JMenuBar();

    public Example6MouseListenerAndMenu(){
        super("MouseListener example");
        setSize(400,400);
        setLayout(new BorderLayout());
        add(jl, BorderLayout.SOUTH);

        JMenu jm1 = new JMenu("First JMenu");
        jm1.setLayout(new FlowLayout());
        jm1.add(new JMenuItem("First JMenuItem"));
        jmb.add(jm1);
        JMenu jm2 = new JMenu("Second dropdown");
        jm2.setLayout(new FlowLayout());
        jm2.add(new JMenuItem("Second entry"));
        jmb.add(jm2);
        add(jmb, BorderLayout.NORTH);

        addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {
                jl.setText("Last click at X="+e.getX()+" Y="+e.getY());
            }

            @Override
            public void mousePressed(MouseEvent e) {
                jl.setText("Mouse pressed at X="+e.getX()+" Y="+e.getY());
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                jl.setText("Mouse released at X="+e.getX()+" Y="+e.getY());
            }

            @Override
            public void mouseEntered(MouseEvent e) {
                jl.setText("Mouse entered at X="+e.getX()+" Y="+e.getY());
            }

            @Override
            public void mouseExited(MouseEvent e) {
                jl.setText("Mouse left at X="+e.getX()+" Y="+e.getY());
            }
        });
        setVisible(true);
    }

    public static void main(String[] args) {
        new Example6MouseListenerAndMenu();
    }
}
