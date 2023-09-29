#include <fstream>
#include <iostream>
#include <string>
#include "task1.h"
#include "task2.h"
using namespace std;

int main(){
  string menu = "1. Работа с текстовым файлом\n"
  "2. Работа с бинарным файлом\n"
  "0. Выход\n"
  "Выбор: ";
  int choice;
  do{
    cout << menu;
    cin >> choice;
    if(cin.fail()){
      cin.clear();
      cin.ignore(10000, '\n');
      continue;
    }
    switch(choice){
      case 1:
        task1();
        break;
      case 2:
        task2();
        break;
      default:
        cout << "Выход..." << endl;
        break;
    }
  }while(choice != 0);
}
