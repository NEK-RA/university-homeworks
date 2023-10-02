package nek.java.lab4;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class App extends JFrame {

  JButton milan = new JButton("AC Milan");
  int milanScore = 0;
  JButton madrid = new JButton("Real Madrid");
  int madridScore = 0;
  JLabel result = new JLabel("Result: 0 X 0");
  JLabel scorer = new JLabel("Last Scorer: N/A");
  JLabel winner = new JLabel("Winnder: DRAW");

  public App(){
    super("Football match clicker");
    setSize(300,100);
    setLayout(new BorderLayout());
    add(milan, BorderLayout.EAST);
    add(madrid, BorderLayout.WEST);
    add(result, BorderLayout.CENTER);
    add(winner, BorderLayout.SOUTH);
    add(scorer, BorderLayout.NORTH);
    setVisible(true);

    milan.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        milanScore++;
        scorer.setText("Last scorer: AC Milan");
        result.setText("Result: " + madridScore + " X " + milanScore);
        updateWinner();
      }
    });

    madrid.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        madridScore++;
        scorer.setText("Last scorer: Real Madrid");
        result.setText("Result: " + madridScore + " X " + milanScore);
        updateWinner();
      }
    });
  }

  void updateWinner(){
    if(milanScore == madridScore){
      winner.setText("Winner: DRAW");
    } else if (milanScore > madridScore) {
      winner.setText("Winner: AC Milan");
    } else {
      winner.setText("Winner: Real Madrid");
    }
  }

  public static void main(String[] args) {
    new App();
  }
}