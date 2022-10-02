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
  cout << "Корректна ли строка: " << isCorrect(num) << endl;
  return true;
}

int getValue(char ch){
  switch(ch){
    case 'I':
      return 1;
    case 'V':
      return 5;
    case 'X':
      return 10;
    case 'L':
      return 50;
    case 'C':
      return 100;
    case 'D':
      return 500;
    case 'M':
      return 1000;
    default:
      return 0;
  }
}

bool isCorrect(string rome){
  char letters[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
  // Проверка отсутствия повторений 4+ повторений для каждой цифры
  bool toomuch = false;
  for(int i=0; i<7; i++){
    // cout << "Checking 4x" << letters[i] << endl;
    if(regex_search(rome,regex(string(letters[i],4)))){
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
  char first,second;
  for(int i=1; i < rome.size()-1; i++){
    first = rome[i-1];
    second = rome[i];
    
  }
  return !toomuch && !doublehalf;
}