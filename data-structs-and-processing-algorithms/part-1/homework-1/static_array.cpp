#include <iostream>
#include <random>
#include <limits>
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
struct IntInput{
  bool ok;
  int num;
  string msg;
};

struct StatArr{
  int array[50] = {0};
  int length;
};

IntInput readInt(string, int, int);
string decTo3ss(int);
int double2in3ss(StatArr);
void insertAfter(int, StatArr&, int);
void deleteAt(StatArr&, int);
void deleteAllTargets(StatArr&);

int main() {
  // Создание массива и указание его длинны
  StatArr st;
  IntInput lenStruct = readInt("Укажите длинну массива",1,20);
  if(lenStruct.ok){
    st.length = lenStruct.num;
  }
  // Заполнение массива рандомными числами до 1000
  srand(rand());
  for(int i = 0; i < st.length; i++){
    st.array[i] = rand() % 1001;
  }
  // Вывод массива в консоли
  for(int i = 0; i < st.length; i++){
    cout << st.array[i] << " ";
  }
  cout << endl;
  // Поиск первого эл-та с ровно двумя двойками в троичной записи
  int firstTarget = double2in3ss(st);
  if(firstTarget != -1){
    cout << "Первый элемент с ровно двумя двойками в троичной записи имеет индекс " << firstTarget << endl;
  }else{
    cout << "Элемента, соответствующего условию, не найдено" << endl;
  }
  // Ввода числа и его вставка после нужного элемента
  if(firstTarget != -1){
    IntInput task2num = readInt("Укажите число для вставки",numeric_limits<int>::min(),numeric_limits<int>::max());
    if(task2num.ok){
      insertAfter(task2num.num, st, firstTarget);
      cout << "Значения массива и их троичная запись после вставки:" << endl;
      for(int i = 0; i < st.length; i++){
        cout << "a[" << i << "]=" << st.array[i] << " -> " << decTo3ss(st.array[i]) << endl;
      }
      cout << endl;
    } 
  }
  // Удаление
  deleteAllTargets(st);
cout << "Значения массива и их троичная запись после удаления элементов:" << endl;
  for(int i = 0; i < st.length; i++){
    cout << "a[" << i << "]=" << st.array[i] << " -> " << decTo3ss(st.array[i]) << endl;
  }
  cout << endl;
  return 0;
}

void deleteAllTargets(StatArr& st){
  int target = double2in3ss(st);
  while(target != -1){
    deleteAt(st,target);
    target = double2in3ss(st);
  }
}

void deleteAt(StatArr &st, int pos){
  // Удаление
  for(int i = pos; i < st.length; i++){
    st.array[i] = st.array[i+1];
  }
  st.length--;
}

void insertAfter(int num, StatArr &st, int pos){
  // Вставка
  for(int i = st.length-1; i > pos; i--){
    st.array[i+1] = st.array[i];
  }
  st.array[pos+1] = num;
  st.length++;
}

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

int double2in3ss(StatArr st){
  // переменная для индекса
  int result = -1;
  // переменная для троичной записи числа
  string tns = "";
  // переменная для подсчета цифр 2 в троичной записи
  int counter = 0;
  for(int i = 0; i < st.length; i++){
    counter = 0;
    // перевод в троичную запись
    tns = decTo3ss(st.array[i]);
    // вывод для дебага
    // cout << st.array[i] << " -> " << tns << endl;
    for(char num : tns){
      if (num == '2'){
        counter++;
      }
    }
    if(counter == 2){
      result = i;
      break;
    }
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
  int num = NULL;
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