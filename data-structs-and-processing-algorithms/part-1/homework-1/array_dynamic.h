#ifndef ARRAY_DYNAMIC_H
#define ARRAY_DYNAMIC_H

#include <iostream>
#include <string>
#include <random>

#include "utils.h"

using namespace std;

struct DynArr{
  int *array;
  int length;
};

void printDynArr(DynArr*, string);
int double2in3ss(DynArr*);
void insertAfter(int, DynArr*, int);
void deleteAt(DynArr*, int);
void deleteAllTargets(DynArr*);
void launchDynamicArray();

#endif // ARRAY_DYNAMIC_H