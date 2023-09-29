#ifndef TASK_1_H
#define TASK_1_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void cat(string filename);
void mkFixedOrRandom(string filename, bool fixedNumbers);
void writeFile(string filename, string text, bool append);
int readNthNumber(string filename, int n);
int countNumbers(string filename);
string variantSpecific(string filename);

void task1();

#endif