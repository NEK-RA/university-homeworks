#ifndef ARRAY_STATIC_H
#define ARRAY_STATIC_H

#include <iostream>
#include <string>
#include <random>

#include "utils.h"

using namespace std;

struct StatArr{
  int array[50] = {0};
  int length;
};

void printStatArr(StatArr, string);
int double2in3ss(StatArr);
void insertAfter(int, StatArr&, int);
void deleteAt(StatArr&, int);
void deleteAllTargets(StatArr&);
void launchStaticArray();

#endif // ARRAY_STATIC_H