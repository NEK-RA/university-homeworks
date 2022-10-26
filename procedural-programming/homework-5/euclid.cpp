#include "euclid.h"
/* «Алгоритм Евклида». 
Задать 2 числа и найти их наибольший общий делитель двумя способами: делением и вычитанием.

Делением:
1. делим большее на меньшее
2. если делится без остатка, то меньшее и есть НОД
3. если есть остаток, то большее число заменяется на остаток от деления
4. возвращение к пункту 1

Вычитанием:
1. из большего вычитается меньшее
2. если вышел 0 то числа равны и являются НОД
3. если не равно, то большее число заменяется на результат вычитания
4. переход в пункт 1
*/

int division(int a, int b, int c = 0){
  c++;
  int min = NULL, max = NULL;
  cout << "Берем числа по модулю для исключения бесконечных циклов: "
  << a << " --> " << abs(a) << ", " << b << " --> " << abs(b) << endl;
  a = abs(a);
  b = abs(b);
  if(a>b){
    max = a;
    min = b;
  }else{
    max = b;
    min = a;
  }
  cout << "Действие " << c << endl;
  if(max % min == 0){
    cout << "Исходные числа в порядке убывания: " << max << ", " << min << endl;
    cout << "Числа пропорциональны, НОД=|" << min << "|" << endl;
    return abs(min);
  }else{
    cout << "Исходные числа в порядке убывания: " << max << ", " << min << endl;
    cout << "Результат не найден, продолжаем поиск с (" << max << "%" << min << ")=" << (max % min)
      << ", " << min << endl;
    return division(max % min, min, c);
  }
}



int subtraction (int a, int b, int c=0){
  c++;
  int min = NULL, max = NULL;
  cout << "Берем числа по модулю для исключения бесконечных циклов: "
  << a << " --> " << abs(a) << ", " << b << " --> " << abs(b) << endl;
  a = abs(a);
  b = abs(b);
  if(a>b){
    max = a;
    min = b;
  }else{
    max = b;
    min = a;
  }
  cout << "Действие " << c << endl;
  if(max - min == 0){
    cout << "Исходные числа в порядке убывания: " << max << ", " << min << endl;
    cout << "Числа равны, НОД=|" << min << "|" << endl;
    return abs(min);
  }else{
    cout << "Исходные числа в порядке убывания: " << max << ", " << min << endl;
    cout << "Результат не найден, продолжаем поиск с (" << max << " - " << min << ")=" << (max - min)
      << ", " << min << endl;
    return subtraction(max-min, min, c);
  }
}

bool runEuclid(){
  int a=0,b=0;
  cout << "Введите первое число: ";
  if(cin >> a){
    cout << "Введите второе число: ";
    if(cin >> b){
      int nod = NULL;
      cout << "Метод деления:" << endl;
      nod = division(a,b);
      cout << "НОД(" << a << ", " << b << ") = " <<  nod << endl;

      cout << "Метод вычитание:" << endl;
      nod = subtraction(a,b);
      cout << "НОД(" << a << ", " << b << ") = " <<  nod << endl;

      return true;
    }else{
      cout << "Необходимо вводить целое число!" << endl;
      cin.clear();
      cin.ignore(10000,'\n');
      return false;
    }
  }else{
    cout << "Необходимо вводить целое число!" << endl;
    cin.clear();
    cin.ignore(10000,'\n');
    return false;
  }
}