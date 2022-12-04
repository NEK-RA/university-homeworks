#include <iostream>
#include <vector>
using namespace std;

vector<vector<pair<int, bool>>> generateSeats() {
  vector<vector<pair<int, bool>>> seats = {};
  vector<pair<int, bool>> coupe = {};
  // места с 1 по 36
  for (int i = 1; i <= 36; i++) {
    coupe.push_back({i, false});
    if (i % 4 == 0) {
      seats.push_back(coupe);
      coupe.clear();
    }
  }
  // места с 37 по 54
  int counter = seats.size() - 1;
  for (int i = 37; i <= 54; i++) {
    seats[counter].push_back({i, false});
    if (i % 2 == 0) {
      counter--;
    }
  }
  return seats;
}

bool intVectorContain(vector<int> v, int n){
  bool result = false;
  for(int i=0; i< v.size(); i++){
    if(v[i]==n){
      result = true;
      break;
    }
  }
  return result;
}

vector<vector<pair<int, bool>>> markFree(vector<vector<pair<int, bool>>> seats, vector<int> free) {
  int n = 0;
  for(int i = 0; i < seats.size(); i++){
    for(int j = 0; j < seats[i].size(); j++){
      n = seats[i][j].first;
      if(intVectorContain(free,n)){
        seats[i][j].second = true;
      }
    }
  }
  return seats;
}

int freeCoupes(vector<vector<pair<int, bool>>> seats){
  int counter = 0;
  int maxfree = 0;
  bool isFree = true;
  for(int i = 0; i < seats.size(); i++){
    isFree = true;
    for(int j = 0; j < seats[i].size(); j++){
      if(!seats[i][j].second){
        isFree = false;
        break;
      }
    }
    if(isFree){
      counter++;
    }else{
      if(counter > maxfree){
        maxfree = counter;
      }
      counter = 0;
    }
  }
  // cout << "Свободных купе: " << counter << endl;
  return maxfree;
}

void printCoupe(vector<pair<int, bool>> coupe, int n = 0) {
  if (n != 0) {
    cout << "Купе " << n << endl;
  }
  for (int i = 0; i < coupe.size(); i++) {
    cout << "Место: " << coupe[i].first << ", свободно ли: " << boolalpha
         << coupe[i].second << endl;
  }
}

int readInt(string message="") {
  bool read = false;
  int a = NULL;
  while (!read) {
    cout << message;
    if (cin >> a) {
      read = true;
    } else {
      cout << "Необходимо вводить только целые числа!" << endl;
      cout << endl;
      cin.clear();
      cin.ignore(10000, '\n');
    }
  }
  // cout << endl;
  return a;
}

vector<int> readIntVector(int n){
  vector<int> arr = {};
  for(int i=0; i<n; i++){
    arr.push_back(readInt()%55);
  }
  return arr;
}

int main() {
  vector<vector<pair<int, bool>>> seats = generateSeats();
  int n = readInt("Укажите кол-во свободных мест N: ");
  cout << "Укажите номера свободных мест, каждое с новой строки:" << endl;
  vector<int> free = readIntVector(n);
  seats = markFree(seats,free);
  cout << "Максимальное количество свободных купе, идущих подряд: " << freeCoupes(seats) << endl;
  // вывод мест
  // for (int i = 0; i < seats.size(); i++) {
  //   printCoupe(seats[i], i + 1);
  //   cout << endl;
  // }
}