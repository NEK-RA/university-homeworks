#include "equation.h"

bool equationTask(){
  float b=0, c=0;
  cout << "Программа решит уравнение вида: b*x + c = 0" << endl;
  cout << "Введите b: ";
  if(cin >> b){
    cout << "Введите c:";
    if(cin >> c){
      cout << "Ваше уравнение: " << b << "*x + " << c << " = 0" << endl;
      if(b==0 && c!=0){
        cout << "ОШИБКА: при b=0 уравнение принимает вид " << c << "=0, что является невозможным! Программа будет перезапущена." << endl;
        return false; 
      }else{
        float x = -c / b;
        cout << "Решение: x=" << x << endl;
        return true;
      }
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