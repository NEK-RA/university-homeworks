#ifndef ARRAY_VECTOR_H
#define ARRAY_VECTOR_H

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <iterator>

#include "utils.h" 

using namespace std;

struct VectArr{
  vector<int> array;
  int length;
};

void printVectArr(VectArr, string);
int double2in3ss(VectArr&);
void insertAfter(int, VectArr&, int);
void deleteAt(VectArr&, int);
void deleteAllTargets(VectArr&);
void launchVector();

#endif // ARRAY_VECTOR_H