#ifndef UTILS_H
#define UTILS_H

#include <iostream>
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
FloatInput readFloat(string, float, float);


#endif // UTILS_H
