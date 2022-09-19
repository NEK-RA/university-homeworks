#include "ifelse.h"

bool ifelseTask(){
  float a=0, x=0;
  cout << "Введите значение X: ";
  if(cin >> x){
    cout << "Введите значение A: ";
    if(cin >> a){
      float modx = abs(x);
      if(modx < 1){
        // a * ln|x|
        cout << "|X| < 1, поэтому выражение принимает вид: W = " << a << " * ln|" << x << "|" << endl;
        if(x == 0){
          cout << "Ошибка: подлогарифмическое выражение не может равняться нулю. Программа будет перезапущена." << endl;
          cin.clear();
          cin.ignore(10000, '\n');
          return false;
        }
        float w = a * log(modx);
        cout << "Результат: W = " << w << endl;
        return true;
      }else{
        // sqrt(a-x^2)
        float toroot = a - x*x;
        cout << "|X| >= 1, поэтому выражение принимает вид: W = sqrt(" << a << " - " << x << " * " << x << ", т.е. W = sqrt(" << toroot << ")" << endl; 
        if(toroot >= 0){
          float w = sqrt(toroot);
          cout << "Результат: W = " << w << endl;
          return true;
        }else{
          cout << "Ошибка: подкоренное выражение для квадратного корня не может быть меньше нуля. Программа будет перезапущена" << endl;
          cin.clear();
          cin.ignore(10000, '\n');
          return false;
        }
      }
    }else{
      cout << "Ошибка ввода: необходимо вводить только числа.  Программа будет перезапущена." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      return false;
    }
  }else{
    cout << "Ошибка ввода: необходимо вводить только числа.  Программа будет перезапущена." << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    return false;
  }
}