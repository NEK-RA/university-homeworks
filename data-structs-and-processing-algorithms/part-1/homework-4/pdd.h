#ifndef PDD_H
#define PDD_H

#include <iostream>
#include <string>

#include "utils.h"

struct carnum{
  string* number;
  int region;
};

struct date{
  int day;
  int month;
  int year;
};

struct violation{
  carnum number;
  string* fio;
  string* model;
  date time;
  string* place;
  string* article;
  float penalty;
};

struct var{
  violation* items;
  int amount = 0;
};

date readDate();
carnum readCarNum();
int compareCarNums(carnum c1, carnum c2);
/*
1) Заполнение записи о нарушении ПДД с клавиатуры.
2) Вставить запись в таблицу, упорядочивая записи по не возрастанию по номеру автомобиля.
3) Удалить записи по заданному номеру автомобиля.
4) Сформировать список сведений по автомобилям, которым назначен штраф по заданной статье.
*/
violation registerViolation();
void addViolation(var& table, violation v);
void deleteByNumber(var& v, carnum num);
void printAllByArticle(var& v, string article);

void printAll(var& v);
void deleteAll(var& v);
#endif // PDD_H
