#include "function.h"

bool calcFunction(){
  float b=0, x=0, y=0;
  cout << "Введите b: ";
  if(cin >> b){
    cout << "Введите x: ";
    if(cin >> x){
      cout << "Введите y: ";
      if(cin >> y){
        // проверка для ln(b-y)
        if(b-y<=0){
          cout << "Ошибка: подлогарифмическое выражение должно быть больше нуля.  Программа будет перезапущена." << endl;
          cin.clear();
          cin.ignore(10000, '\n');
          return false;
        }
        // проверка для sqrt(b-x)
        if(b-x<0){
          cout << "Ошибка: подкоренное выражение не может быть отрицательным.  Программа будет перезапущена." << endl;
          cin.clear();
          cin.ignore(10000, '\n');
          return false;
        }
        // результат
        float z = log(b-y) * sqrt(b-x);
        cout << "Результат: z = " << z << endl;
        return true;
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
  }else{
    cout << "Ошибка ввода: необходимо вводить только числа.  Программа будет перезапущена." << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    return false;
  }
}