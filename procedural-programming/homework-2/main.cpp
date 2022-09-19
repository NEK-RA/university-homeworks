#include <iostream>
#include "conus.h"
#include "ifelse.h"
#include "function.h"
#include "sequence.h"
#include "tabs.h"
using namespace std;

int main(){
  setlocale(LC_ALL,"Russian");

  // cout << "Задача <Конус>" << endl;
  // bool conusDone = false;
  // while(!conusDone){
  //   conusDone = calcConus();
  //   cout << endl;
  // }
  // cout << endl << endl;

  // cout << "Задача <Разветвление>" << endl;
  // bool ifelseDone = false;
  // while(!ifelseDone){
  //   ifelseDone = ifelseTask();
  //   cout << endl;
  // }
  // cout << endl << endl;

  // cout << "Задача <Функция>" << endl;
  // bool funcDone = false;
  // while(!funcDone){
  //   funcDone = calcFunction();
  //   cout << endl;
  // }
  // cout << endl << endl;
  
  cout << "Задача <Порядок>" << endl;
  bool sequenceDone = false;
  while(!sequenceDone){
    sequenceDone=displayNumbers();
    cout << endl;
  }
  cout << endl << endl;

  // cout << "Задача <Табуляция>" << endl;
  // bool tabsDone = false;
  // while(!tabsDone){
  //   tabsDone = tabFunc();
  //   cout << endl;
  // }
  // cout << endl << endl;
}
