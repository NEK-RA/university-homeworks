#include <iostream>

#include "utils.h"
#include "array_static.h"
#include "array_dynamic.h"
#include "array_vector.h"

using namespace std;

/*
Вариант 18

1. Найти индекс элемента массива, троичный код значения которого содержит ровно две двойки.

2. Вставить новый элемент в массив после элемента, троичный код значения которого содержит ровно две двойки.

3. Удалить элементы массива, троичный код значений которых содержит ровно две двойки.

Сделать на статическом массиве (с запасом), на динамическом массиве(указатель , а так же malloc,realloc,free либо new/delete) и вариант на векторе

Подзадачи:
- контроллируемый ввод целого числа +
- перевод в трочиную СС +
- поиск первого эл-та массива с ровно двумя двойками в записи +
- вставка после эл-та с -/- +
- удаление элемента +
- удалить все элементы с -/- +
*/

int main(){
  int exitCode = 0;

  short mainChoice = -1;
  IntInput tmp;
  while(mainChoice != 0){
    cout << "\n\n\n" << endl;
    cout << "###\tГЛАВНОЕ МЕНЮ\t###" << endl;
    cout << "Выберите тип массива:" << endl
    << "1. Статический массив" << endl
    << "2. Динамический массив" << endl
    << "3. На базе контейнера vector" << endl
    << "0. Завершить работу" << endl;
    tmp = readInt("Укажите номер нужного варианта",0,3);

    if(tmp.ok){
      mainChoice = tmp.num;
      switch(mainChoice){
        case 1:
          launchStaticArray();
          break;
        case 2:
          launchDynamicArray();
          break;
        case 3:
          launchVector();
          break;
        default:
          if(mainChoice == 0){
            cout << "Завершение работы..." << endl;
          }else{
            cout << "Получено неожиданное значение: " << mainChoice << ", программа будет завершена" << endl;
          }
          break;
      }
    }else{
      // Случай некорректного задания границ в readInt
      cout << tmp.msg << endl;
      cout << "Выполнение программы прекращено" << endl;
      exitCode = 1;
    }

  }

  return exitCode;
}
