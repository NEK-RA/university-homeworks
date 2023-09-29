#ifndef TASK2_H
#define TASK2_H
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct date {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

struct friendInfo {
    char name[20]; // считаем ключом
    date birthday;
};

vector<friendInfo> readTxt(string filename);
vector<friendInfo> readBin(string filename);
string txt2bin(string filename);
string bin2txt(string filename);
friendInfo readNthFriend(string filename, int n);
void deleteRecord(string filename, int n);
string byMonth2Txt(string filename, int month);
vector<string> searchByDate(string filename, date target);

void task2();

#endif // TASK2_H
