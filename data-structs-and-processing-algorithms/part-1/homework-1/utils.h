#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct IntInput{
  bool ok;
  int num;
  string msg;
};

IntInput readInt(string, int, int);
string decTo3ss(int);

#endif // UTILS_H
