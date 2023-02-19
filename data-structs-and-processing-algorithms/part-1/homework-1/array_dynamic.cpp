#include "array_dynamic.h"

void launchDynamicArray() {
  DynArr *d = new DynArr;
  IntInput tmp;
  int menuChoice = -1;
  int firstTarget = -1;

  // Создание динамического массива
  tmp = readInt("Укажите длинну массива",1,20);
  if(tmp.ok){
    d->array = new int[tmp.num];
    d->length = tmp.num;
  }

  
  // Выбор метода заполнения
  tmp = readInt("Выберите метод заполнения:\n1. Ручное\n2. Автоматическое",1,2);
  if(tmp.ok){
    if(tmp.num == 1){
      // Ручное заполнение массива
      for(int i = 0; i < d->length; i++){
        tmp = readInt("Введите значение a["+to_string(i)+"]", numeric_limits<int>::min(),numeric_limits<int>::max());
        if(tmp.ok){
          d->array[i] = tmp.num;
        }
      }
    }else{
      // Заполнение массива рандомными числами до 1000
      srand(time(NULL));
      for(int i = 0; i < d->length; i++){
        d->array[i] = rand() % 1001;
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
          printDynArr(d, "Введенный массив и троичные записи чисел:");
          // Поиск первого эл-та с ровно двумя двойками в троичной записи
          firstTarget = double2in3ss(d);
          if(firstTarget != -1){
            cout << "Первый элемент с ровно двумя двойками в троичной записи имеет индекс " << firstTarget << endl;
          }else{
            cout << "Элемента, соответствующего условию, не найдено" << endl;
          }
          break;


        case 2:
          // Ввод числа и его вставка после нужного элемента
          firstTarget = double2in3ss(d);
          if(firstTarget != -1){
            IntInput task2num = readInt("Укажите число для вставки",numeric_limits<int>::min(),numeric_limits<int>::max());
            if(task2num.ok){
              printDynArr(d, "Массив и троичные записи чисел ДО вставки:");
              insertAfter(task2num.num, d, firstTarget);
              printDynArr(d, "Массив и троичные записи чисел ПОСЛЕ вставки:");
            } 
          }else{
            cout << "Элемент, соответствующий условию не найден. Добавление невозможно" << endl;
          }
          break;
        

        case 3:
          // Удаление
          printDynArr(d, "Массив и троичные записи чисел ДО удаления элементов:");
          deleteAllTargets(d);
          printDynArr(d, "Массив и троичные записи чисел ПОСЛЕ удаления элементов:");
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

  // Освобождение памяти
  delete d->array;
  delete d;
}

void printDynArr(DynArr *d, string msg){
  cout << msg << endl;
  for(int i = 0; i < d->length; i++){
    cout << "a[" << i << "]=" << d->array[i] << " -> " << decTo3ss(d->array[i]) << endl;
  }
  cout << endl;
}

void deleteAllTargets(DynArr *d){
  int target = double2in3ss(d);
  while(target != -1){
    deleteAt(d,target);
    target = double2in3ss(d);
  }
}

void deleteAt(DynArr *d, int pos){
  // Удаление
  for(int i = pos; i < d->length; i++){
    d->array[i] = d->array[i+1];
  }
  d->length--;
  d->array = (int*)realloc(d->array, sizeof(d->array[0]) * d->length);
}

void insertAfter(int num, DynArr *d, int pos){
  // добавление/перевыделение памяти на 1 элемент больше
  d->array = (int*)realloc(d->array, sizeof(d->array[0]) * d->length + 1);
  // смещение
  for(int i = d->length-1; i > pos; i--){
    d->array[i+1] = d->array[i];
  }
  // вставка
  d->array[pos+1] = num;
  // учет в структуре
  d->length++;
}

int double2in3ss(DynArr *d){
  // переменная для индекса
  int result = -1;
  // переменная для троичной записи числа
  string tns = "";
  // переменная для подсчета цифр 2 в троичной записи
  int counter = 0;
  for(int i = 0; i < d->length; i++){
    counter = 0;
    // перевод в троичную запись
    tns = decTo3ss(d->array[i]);
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