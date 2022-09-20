#include <iostream>
#include "numsystem.h"
using namespace std;

int main() {
  cout << "Задача <Системы счисления>" << endl;
  bool numConverted = false;
  while(!numConverted){
    numConverted = runNumSystem();
    cout << endl;
  }
  cout << endl << endl;
}