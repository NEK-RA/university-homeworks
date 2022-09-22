#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int getNum(char ch);
char getLetter(int num);
int findLength(int num, int base);
string fromDecimal(int num, int target);
int toDecimal(string num, int base);
bool validate(string num, int base);
string convert(string num, int source, int target);
bool runNumSystem();
