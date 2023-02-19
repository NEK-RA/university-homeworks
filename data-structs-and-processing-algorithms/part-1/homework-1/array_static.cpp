#include "array_static.h"

using namespace std;

void launchStaticArray() {
  StatArr st;
  IntInput tmp;
  int menuChoice = -1;
  int firstTarget = -1;

  // Создание массива и указание его длинны
  tmp = readInt("Укажите длинну массива",1,20);
  if(tmp.ok){
    st.length = tmp.num;
  }

  // Выбор метода заполнения
  tmp = readInt("Выберите метод заполнения:\n1. Ручное\n2. Автоматическое",1,2);
  if(tmp.ok){
    if(tmp.num == 1){
      // Ручное заполнение массива
      for(int i = 0; i < st.length; i++){
        tmp = readInt("Введите значение a["+to_string(i)+"]", numeric_limits<int>::min(),numeric_limits<int>::max());
        if(tmp.ok){
          st.array[i] = tmp.num;
        }
      }
    }else{
      // Заполнение массива рандомными числами до 1000
      srand(time(NULL));
      for(int i = 0; i < st.length; i++){
        st.array[i] = rand() % 1001;
      }
    }
  }

  while(menuChoice != 0){
    cout << "Возможные действия:" << endl;
    cout << "1. Найти первый элемент, у которого в троичной записи ровно две двойки" << endl
      << "2. Вставить число после первого эл-та, у которого в троичной записи ровно две двойки" << endl
      << "3. Удалить все элементы, у которых в троичной записи ровно две двойки" << endl
      << "0. Выйти в главное меню" << endl;
      tmp = readInt("Укажите номер нужного варианта",0,3);
      if(tmp.ok){
        menuChoice = tmp.num;
      }
      switch(menuChoice){

        case 1:
          printStatArr(st, "Введенный массив и троичные записи чисел:");
          // Поиск первого эл-та с ровно двумя двойками в троичной записи
          firstTarget = double2in3ss(st);
          if(firstTarget != -1){
            cout << "Первый элемент с ровно двумя двойками в троичной записи имеет индекс " << firstTarget << endl;
          }else{
            cout << "Элемента, соответствующего условию, не найдено" << endl;
          }
          break;


        case 2:
          // Ввод числа и его вставка после нужного элемента
          firstTarget = double2in3ss(st);
          if(firstTarget != -1){
            IntInput task2num = readInt("Укажите число для вставки",numeric_limits<int>::min(),numeric_limits<int>::max());
            if(task2num.ok){
              printStatArr(st, "Массив и троичные записи чисел ДО вставки:");
              insertAfter(task2num.num, st, firstTarget);
              printStatArr(st, "Массив и троичные записи чисел ПОСЛЕ вставки:");
            } 
          }else{
            cout << "Элемент, соответствующий условию не найден. Добавление невозможно" << endl;
          }
          break;
        

        case 3:
          // Удаление
          printStatArr(st, "Массив и троичные записи чисел ДО удаления элементов:");
          deleteAllTargets(st);
          printStatArr(st, "Массив и троичные записи чисел ПОСЛЕ удаления элементов:");
          break;
        

        default:
          if(menuChoice == 0){
            cout << "Возвращаемся в главное меню..." << endl;
          }else{
            cout << "Получено неожиданное значение: " << menuChoice << ", работа со статическим массивом будет завершена" << endl;
          }
          break;
      }
  }
}

void printStatArr(StatArr st, string msg){
  cout << msg << endl;
  for(int i = 0; i < st.length; i++){
    cout << "a[" << i << "]=" << st.array[i] << " -> " << decTo3ss(st.array[i]) << endl;
  }
  cout << endl;
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

void insertAfter(int num, StatArr &st, int pos){
  // Вставка
  for(int i = st.length-1; i > pos; i--){
    st.array[i+1] = st.array[i];
  }
  st.array[pos+1] = num;
  st.length++;
}

void deleteAt(StatArr &st, int pos){
  // Удаление
  for(int i = pos; i < st.length; i++){
    st.array[i] = st.array[i+1];
  }
  st.length--;
}

void deleteAllTargets(StatArr& st){
  int target = double2in3ss(st);
  while(target != -1){
    deleteAt(st,target);
    target = double2in3ss(st);
  }
}

