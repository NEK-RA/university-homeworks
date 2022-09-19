#include "arithmetic.h"

bool arithmeticTask() {
  float a=0,b=0;
  cout << "Введите первое число: ";
  if(cin >> a){
    cout << "Введите второе число: ";
    if(cin >> b){
      cout << a << " + " << b << " = " << a+b << endl;
      cout << a << " - " << b << " = " << a-b << endl;
      cout << a << " * " << b << " = " << a*b << endl;
      cout << a << " / " << b << " = ";
      if(b == 0){
        cout << "Нет результата, по причине невозможности деления на ноль." << endl;
      }else{
        cout << a/b << endl;
      }
      return true;
    }else{
      cout << "Введено некорректное значение. Программа будет перезапущена." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      return false;
    }
  }else{
    cout << "Введено некорректное значение. Программа будет перезапущена." << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    return false;
  }
}