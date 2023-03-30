#include "pdd.h"

date readDate(){
  IntInput tmp;
  date nd;
  int daylim = 30;

  tmp.ok = false;
  while(!tmp.ok){
    tmp = readInt("Укажите год:",2000,2023);
  }
  nd.year = tmp.num;
  tmp.ok = false;

  while(!tmp.ok){
    tmp = readInt("Укажите месяц:",1,12);
  }
  nd.month = tmp.num;
  tmp.ok = false;

  if(nd.month == 2){
    if(nd.year % 4 == 0){
      daylim = 29;
    }
  }else{
    if(nd.month == 1 || nd.month == 3 || nd.month == 5 ||
    nd.month == 7 || nd.month == 8 || nd.month == 10 || nd.month == 12){
      daylim = 31;
    }
  }
  while(!tmp.ok){
    tmp = readInt("Введите число:",1,daylim);
  }
  nd.day = tmp.num;

  return nd;
}

carnum readCarNum(){
  IntInput num;
  carnum car;
  num.ok = false;

  while(!num.ok){
    num = readInt("Укажите номер региона для автомобиля:", 1, 1000);
  }
  car.region = num.num;

  cout << "Укажите номер автомобиля (без региона):" << endl;
  car.number = new string;
  cin >> *car.number;

  return car;
}

int compareCarNums(carnum c1, carnum c2){
  if ((*c1.number) > (*c2.number)){
    return 1;
  }else if((*c1.number) == (*c2.number)){
    if(c1.region > c2.region){
      return 1;
    }else if(c1.region == c2.region){
      return 0;
    }else{
      return 2;
    }
  }else{
    return 2;
  }
}

// 1) Заполнение записи о нарушении ПДД с клавиатуры.
violation registerViolation(){
  violation nv;
  FloatInput flp;

  flp.ok = false;

  nv.number = readCarNum();

  cout << "Укажите модель автомобиля:" << endl;
  nv.model = new string;
  cin >> *nv.model;

  cout << "Введите фамилию и инициалы:" << endl;
  nv.fio = new string;
  cin >> *nv.fio;

  cout << "Укажите дату нарушения:" << endl;
  nv.time = readDate();

  cout << "Где произошло нарушение?" << endl;
  nv.place = new string;
  cin >> *nv.place;

  cout << "Укажите статью, соответствующую нарушению" << endl;
  nv.article = new string;
  cin >> *nv.article;

  while(!flp.ok){
    flp = readFloat("Укажите сумму штрафа:", 0, 300000);
  }
  nv.penalty = flp.num;

  return nv;
}

// 2) Вставить запись в таблицу, упорядочивая записи по не возрастанию по номеру автомобиля.
void addViolation(var& table, violation v){
  if(table.amount == 0){
    table.amount++;
    table.items = (violation*)malloc(1*sizeof(violation));
    table.items[0] = v;
  }
  else{
    // поиск позиции для вставки
    int index = table.amount; // последний в расширенном
    int cmp = -1;
    for(int i = 0; i < table.amount; i++){
      cmp = compareCarNums(table.items[i].number,v.number);
      if(cmp == 2 || cmp == 0){
        index = i;
        break;
      }
    }
    // расширение
    table.amount++;
    table.items = (violation*)realloc(table.items,(table.amount)*sizeof(violation));
    // смещение
    for(int i = table.amount - 1; i > index; i--){
      table.items[i] = table.items[i-1];
    }
    // вставка
    table.items[index] = v;
  }
}

// 3) Удалить записи по заданному номеру автомобиля.
void deleteByNumber(var& v, carnum num){
  bool sameNumber = false;
  bool sameRegion = false;
  for(int i = 0; i < v.amount; i++){
    sameNumber = *v.items[i].number.number == *num.number;
    sameRegion = v.items[i].number.region == num.region;

    if(sameNumber && sameRegion){
      // Освобождение памяти от полей
      delete v.items[i].place;
      delete v.items[i].number.number;
      delete v.items[i].model;
      delete v.items[i].fio;
      delete v.items[i].article;
      // смещение оставшихся при необходимости
      if(v.amount != 1){
        for(int j = i; j < v.amount-1; j++){
          v.items[j] = v.items[j+1];
        }
        v.amount--;
        v.items = (violation*)realloc(v.items,(v.amount+1)*sizeof(violation));
      }else{
        free(v.items);
        v.amount = 0;
      }
    }
  }
}

// 4) Сформировать список сведений по автомобилям, которым назначен штраф по заданной статье.
void printAllByArticle(var& v, string article){
  int count = 0;
  cout << "Нарушения по статье: " << article << endl;

  for(int i = 0; i < v.amount; i++){
    if(*v.items[i].article == article){
      cout << endl;
      cout << "Информация о нарушении: " << endl;
      cout << "Дата: " << v.items[i].time.day << "." << v.items[i].time.month << "." << v.items[i].time.year << endl;
      cout << "Место: " << *v.items[i].place << endl;
      cout << "Номер автомобиля: " << *v.items[i].number.number << " из " << v.items[i].number.region << " региона" << endl;
      cout << "Наименование: " << *v.items[i].model << endl;
      cout << "Нарушитель: " << *v.items[i].fio << endl;
      cout << "Нарушение по статье: " << *v.items[i].article << endl;
      cout << "Штраф: " << v.items[i].penalty << " условных ед-ц" << endl;
      cout << endl;
      count++;
    }
  }
  if(count == 0){
    cout << "Не найдено нарушений по указанной статье" << endl;
  }
}

void printAll(var& v){
  cout << "Кол-во нарушений: " << v.amount << endl;
  for(int i = 0; i < v.amount; i++){
    cout << endl;
    cout << "Информация о нарушении: " << endl;
    cout << "Дата: " << v.items[i].time.day << "." << v.items[i].time.month << "." << v.items[i].time.year << endl;
    cout << "Место: " << *v.items[i].place << endl;
    cout << "Номер автомобиля: " << *v.items[i].number.number << " из " << v.items[i].number.region << " региона" << endl;
    cout << "Наименование: " << *v.items[i].model << endl;
    cout << "Нарушитель: " << *v.items[i].fio << endl;
    cout << "Нарушение по статье: " << *v.items[i].article << endl;
    cout << "Штраф: " << v.items[i].penalty << " условных ед-ц" << endl;
    cout << endl;
  }
}

void deleteAll(var& v){
  for(int i = 0; i < v.amount; i++){
    delete v.items[i].place;
    delete v.items[i].number.number;
    delete v.items[i].model;
    delete v.items[i].fio;
    delete v.items[i].article;
  }
  free(v.items);
}
