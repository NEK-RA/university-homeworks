#include <iostream>
#include "loan.h"
#include "percent.h"
#include "display.h"
#include "numbers.h"
#include "letters.h"
using namespace std;

int main() {
	
  cout << "Задача <Заем>" << endl;
  bool loanDone = false;
  while(!loanDone){
    loanDone = calcLoan();
    cout << endl;
  }
  cout << endl << endl;


  cout << "Задача <Ссуда>" << endl;
  bool percentDone = false;
  while(!percentDone){
    percentDone = calcPercent();
    cout << endl;
  }
  cout << endl << endl;
	
  cout << "Задача <Копирование файла>" << endl;
  bool copyDone = false;
  while(!copyDone){
    copyDone = coutFile();
    cout << endl;
  }
  cout << endl << endl;
  
  cout << "Задача <Цифры>" << endl;
  bool numbersDone = false;
  while(!numbersDone){
    numbersDone = coutNumbers();
    cout << endl;
  }
  cout << endl << endl;
	
  cout << "Задача <Сортировка букв>" << endl;
  sortLetters();
	
  return 0;
}
