#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>
#include <filesystem>
#include <fstream>
#include "utils.h"
using namespace std;

vector<string> getAvailableNames(vector<string> installed);
void printAvailableDesktops(vector<string> installed);
string desktopNameById(int id);
int desktopIdByName(string name);
int desktopIdByExecutable(string name);
vector<string> detectDesktops();
int installDE(string installCommand, int id);
int removeDE(string removeCommand, int id);
int installVncServer(string installCommand);
int switchVncDesktop(int deId);
int processOtherTasks(vector<pair<actions,string>> tasks, State state);
