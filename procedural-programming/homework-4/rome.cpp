#include "rome.h"

/*
  I -> 1,
  V -> 5,
  X -> 10,
  L -> 50,
  C -> 100,
  D -> 500,
  M -> 1000.
  не может быть 4 подряд одинаковых, не может быть VV, LL и т.д.
  вычитать можно ближайшее кратное степени десятки: от 100 нельзя отнять 1, можно отнять 10
  99 = XCIX
*/

bool convertRomeNumber(){
  string num = "";
  cout << "Введите число: ";
  cin >> num;
  bool correct = isCorrect(num);
  cout << "Корректна ли строка: " << boolalpha << correct << endl;
  if (correct) {
      int first = 0, second = 0, third = 0, result = 0;
      int skip = 0;
      switch (num.size()) {
        case 1:
            result = getValue(num[0]);
            break;
        case 2:
            first = getValue(num[0]);
            second = getValue(num[1]);
            if (first >= second) {
                result = first + second;
                break;
            }
            else {
                result = second - first;
                break;
            }
        default:
            for (int i = 0; i < num.size(); i++) {
                first = getValue(num[i]);

                if (i + 1 >= num.size()) {
                    second = 0;
                }
                else {
                    second = getValue(num[i + 1]);
                }
                
                if (i + 2 >= num.size()) {
                    third = 0;
                }else{
                    third = getValue(num[i + 2]);
                }


                if (first >= second) {
                    result += first;
                    continue;
                }
                else {
                    result += second - first;
                    i++;
                }
            }
            break;
      }
            cout << num << " = " << result << endl;
  }

  return true;
}

int getValue(char ch){
    //cout << "Получен символ: " << ch << endl;
    int val = 0;
  switch(ch){
    case 'I':
      val = 1;
      break;
    case 'V':
        val = 5;
        break;
    case 'X':
        val = 10;
        break;
    case 'L':
        val = 50;
        break;
    case 'C':
        val = 100;
        break;
    case 'D':
        val = 500;
        break;
    case 'M':
        val = 1000;
        break;
    default:
        val = 0;
        break;
  }
  //cout << "Соответствует число " << val << endl;
  return val;
}

bool isCorrect(string rome){
  char letters[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
  if (rome.size() == 1) {
      bool found = false;
      for (int i = 0; i < 7; i++) {
          if (rome[0] == letters[i]) {
              found = true;
              break;
          }
      }
      if (found) {
          return true;
      }
      else {
          cout << "Некорректный символ, такой цифры нет." << endl;
      }
  }
  // Проверка отсутствия повторений 4+ повторений для каждой цифры
  bool toomuch = false;
  for(int i=0; i<7; i++){
    string sub = string(4, letters[i]);
    //cout << "Checking 4x" << letters[i] << "=" << sub <<" : result - " << regex_search(rome, regex(sub)) << endl;
    if(regex_search(rome,regex(sub))){
      toomuch = true;
      break;
    }
  }
  // Проверка на наличие двух подряд цифр составляющих половину текущего порядка (5+5, 50+50, 500+500)
  bool double5 = regex_search(rome,regex("VV"));
  bool double50 = regex_search(rome,regex("LL"));
  bool double500 = regex_search(rome,regex("DD"));
  bool doublehalf = double5 || double50 || double500;
  // https://www.romannumerals.org/converter
  // вычитать можно только одно число предыдущего порядка: IV - корректно, IIV - НЕкорректно, IX - корректно
  int first = 0, second = 0, third = 0;
  bool halfrange = false,thirdlarge = false, incorrect = false;
  bool threeplus = false;
  int cutend = 0;
  if (rome.size() >= 3) {
      threeplus = true;
      cutend = 2;
  }
  else {
      cutend = 1;
  }
  //cout << "Перебираем строку" << endl;
  for(int i=0; i < rome.size()-cutend; i++){
    first = getValue(rome[i]);
    second = getValue(rome[i+1]);
    if (threeplus) {
        third = getValue(rome[i + 2]);
    }
    //cout << "Первое число: " << first << "\nВторое число: " << second << "\nПервое меньше второго? " << (first < second) << endl;
    if (first < second) {
        //cout << "Проверяем порядок: " << second << "/2 совпадает с первым числом " << first << " ??? " << endl;
        if ((second / 2) == first) {
            halfrange = true;
        }
        if (threeplus) {
            // проверяем что 3-е число не превышает первого, чтобы исключить случаи вида IVI, XCX
            if (third >= first) {
                thirdlarge = true;
            }
        }
        else {
            thirdlarge = false;
        }
        
        incorrect = halfrange || thirdlarge;
        if (incorrect) {
            break;
        }
    }
    
  }
  //cout << "Закончили со строкой" << endl;
  return !toomuch && !doublehalf && !incorrect;
}