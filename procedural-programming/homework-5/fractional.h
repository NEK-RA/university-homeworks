#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <ctime>
#include <random>
using namespace std;

int fractsum(string num);
void printVector(vector<pair<int,string>> data, bool toFile);
string genfile();
vector<pair<int,string>> quicksort(vector<pair<int,string>> array);
void sortFracts();