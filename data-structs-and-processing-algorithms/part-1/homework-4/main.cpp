#include <iostream>
#include <random>

#include "pdd.h"

using namespace std;

void addRandomViolation(var& v);

int main()
{
  IntInput choice;
  var list;
  string article;

  cout << "Учет нарушений ПДД" << endl;

  string menu = "Выберите действие\n"
      "1. Отобразить весь список\n"
      "2. Добавить случайную запись\n"
      "3. Добавить запись вручную\n"
      "4. Удалить все записи по заданному номеру\n"
      "5. Отобразить все записи по заданной статье\n"
      "0. Выход";
  while(choice.num != 0 || choice.ok == false){
    choice = readInt(menu,0,5);
    switch(choice.num){
      case 1:
        printAll(list);
        cout << endl;
        break;
      case 2:
        addRandomViolation(list);
        cout << endl;
        break;
      case 3:
        addViolation(list, registerViolation());
        cout << endl;
        break;
      case 4:
        deleteByNumber(list, readCarNum());
        cout << endl;
        break;
      case 5:
        cout << "Укажите статью: " << endl;
        getline(cin,article);
        printAllByArticle(list, article);
        cout << endl;
        break;

      default:
        if(choice.num == 0){
          cout << "Выход..." << endl;
        }else{
          cout << "Получено неожиданное значение: " << choice.num << ". Выход..." << endl;
        }
        break;
    }
  }
  deleteAll(list);
  return 0;
}

void addRandomViolation(var& v){
  string fio[6] = {"Иванов И.И", "Петров П.П.", "Неустановленное лицо", "Семенов А.Ю", "Верхачева Ю.Н.", "Антонова А.А."};
  string model[6] = {"Ford Focus 2", "Opel Corsa", "BMW X6", "Tesla", "Lada X-Ray", "Mitsubishi Outlander"};
  string place[6] = {"Ул. Потапова 7", "Пр-т Вернадского 25", "Ул. Генерала Вареникова 13", "Б-р Рокоссовского 74", "Пожарный проезд", "Ж/Д переезд" };
  string article[6] = {"Пересечение двойной сплошной", "Превышение скорости", "Парковка в запрещенном месте", "Проезд на красный свет", "Движение по встречной полосе", "Движение в не предназначенном для автотранспорта месте"};
  string number[6] = {"АБ123В", "МА758С", "ВР029Э", "ЭМ319И", "АА000А", "МС777К"};
  violation test;

  test.number.region = (rand() % 999) + 1;
  test.number.number = new string(number[rand()%6]);
  test.fio = new string(fio[rand()%6]);
  test.model = new string(model[rand()%6]);
  test.place = new string(place[rand()%6]);
  test.article = new string(article[rand()%6]);
  test.penalty = (rand() % 300000) + 1;
  test.time.day = (rand() % 28) + 1;
  test.time.month = (rand() % 12) + 1;
  test.time.year = (rand() % 23) + 2001;

  addViolation(v, test);
}
