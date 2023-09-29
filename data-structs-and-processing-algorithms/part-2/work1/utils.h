#ifndef UTILS_H
#define UTILS_H

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct IntInput{
  bool ok = false;
  int num = -1;
  string msg = "";
};

struct FloatInput{
  bool ok;
  float num;
  string msg;
};

IntInput readInt(string, int, int);
IntInput readAnyInt(string);
FloatInput readFloat(string, float, float);

string int2bin(int, bool);
void printNameDecBin(string, int);

#endif // UTILS_H