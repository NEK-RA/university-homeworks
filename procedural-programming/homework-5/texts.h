#include <iostream>
#include <fstream>
#include <map>
using namespace std;

char getChar(char src, int move);
string encrypt(string line, int move);
map<char,int> processLine(string line, map<char,int> frequency);
map<char,int> analyze(string filename);
bool contains(map<char,int> m, char key);
void printMap(map<char,int> m);
pair<char,float> mostFrequent(map<char,int> m);

string letterMove();
bool analyzerPart(string filename);
