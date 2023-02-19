#include "utils.h"

string decTo3ss(int num){
  // 2456 (dec) -> 10100222 (3ss)
  bool neg = false;
  string result = "";
  if(num < 0){
    neg = true;
    num *= -1;
  }
  while(num > 0){
    result = to_string(num % 3) + result;
    num /= 3;
  }
  if(neg){
    result = "-" + result;
  }
  return result;
}

IntInput readInt(string msg, int min, int max){
  if(min>max){
    return {false,0,"Значение нижнего порога выше, чем верхнего. Некорректное требование"};
  }

  if(min == max){
    return {true,min,"Единственное возможное значение для заданных ограничений"};
  }
  IntInput result;
  result.ok = false;
  int num = 0;
  while(!result.ok){
    cout << msg << endl;
    cout << "Введите целое число от " << min << " до " << max << ": ";
    if (cin >> num){
      if((num >= min)&&(num <= max)){
        result.ok = true;
        result.num = num;
      }else{
        cout << "Введенное число не попадает в диапазон [" << min << ";" << max << "]. Повторите ввод" << endl;
      }
    }else{
      cout << "Введенное значение не является целым числом. Повторите ввод" << endl;
    }
    cout << endl;
    cin.clear();
    cin.ignore(10000,'\n');
  }
  return result;
}
