#include <cmath>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int getNum(char ch);
char getLetter(int num);
int findLength(int num, int base);
string fromDecimal(unsigned long long num, int target);
unsigned long long toDecimal(string num, int base);
bool validate(string num, int base);
string convert(string num, int source, int target);
string upper(string str);
void disclaimer();
bool runNumSystem();
