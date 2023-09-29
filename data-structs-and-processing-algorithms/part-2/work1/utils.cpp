#include "utils.h"

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

IntInput readAnyInt(string msg){
  return readInt(msg, numeric_limits<int>::min(), numeric_limits<int>::max());
}

FloatInput readFloat(string msg, float min, float max){
  if(min>max){
    return {false,0,"Значение нижнего порога выше, чем верхнего. Некорректное требование"};
  }

  if(min == max){
    return {true,min,"Единственное возможное значение для заданных ограничений"};
  }
  FloatInput result;
  result.ok = false;
  float num = 0;
  while(!result.ok){
    cout << msg << endl;
    cout << "Введите любое число от " << min << " до " << max << " (включая дробные): ";
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


string int2bin(int num, bool fullsize = false){
  bool neg = num < 0;
  if(neg){
    num = numeric_limits<int>::max() - abs(num) + 1;
  }
  string result = "";
  if(num == 0){
    result = "0";
  }
  while(num > 0){
    result = to_string(num % 2) + result;
    num = num / 2;
  }
  if(fullsize){
    int left = sizeof(num) * 8 - 1 - result.size();
    result = string(left,'0') + result;
  }

  string readable = "";
  for(int i = 0; i < result.size(); i++){
    if(i % 4 == 0){
      readable = " " + readable;
    }
    readable = result[result.size() - i - 1] + readable;
  }

  readable = neg ? "1." + readable : "0." + readable;
  return readable;
}


void printNameDecBin(string name, int num){
  cout << setw(40) << left << name << 
          setw(40) << " = (decimal) " + to_string(num) << 
          setw(50) << " = (binary) " +  int2bin(num, true) << endl;
}