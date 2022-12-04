#include <iostream>
#include <vector>
using namespace std;

long long readNum(string message) {
  bool read = false;
  long long a = NULL;
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
  return a;
}

long long max(long long n1, long long n2){
  if(n1 > n2){
    return n1;
  }
  return n2;
}

void printSeats(vector<long long> seats){
  cout << "Участки свободных мест: ";
  for(long long i=0; i < seats.size(); i++){
    cout << "{" << seats[i] << "}";
    if(i+1 != seats.size()){
      cout << ", ";
    }
  }
  cout << endl;
}

long long findMax(vector<long long> data){
  if(data.empty()){
    return -1;
  }
  long long index = 0;
  long long max = data[index];
  if(data.size() > 1){
    for(long long i=1; i < data.size(); i++){
      if(data[i]>max){
        max = data[i];
        index = i;
      }
    }
  }
  return index;
}

vector<long long> splitBlock(long long n){
  vector<long long> result = {};
  long long mid = n / 2 + n % 2;
  result.push_back(mid-1);
  result.push_back(n-mid);
  // cout << "Было мест на участке: " << n << endl;
  // cout << "Занято место: " << mid << endl;
  // cout << "Слева: " << mid-1 << endl;
  // cout << "Справа: " << n-mid << endl;
  // printSeats(result);
  return result;
}

vector<long long> takeSeat(vector<long long> seats, long long &index){
  vector<long long> before = {};
  vector<long long> after = {};
  vector<long long> result = {};
  
  long long block = findMax(seats);
  // cout << "Максимальный участок: " << seats[block] << endl;
  for(long long i=0; i < block; i++){
    before.push_back(seats[i]);
  }
  if(seats.size() > block+1){
    for(long long i=block+1; i < seats.size(); i++){
      after.push_back(seats[i]);
    }
  }

  vector<long long> splited = splitBlock(seats[block]);

  vector<long long>::iterator it = result.begin();
  result.insert(it,before.begin(),before.end());

  it = result.end();
  result.insert(it,splited.begin(),splited.end());
  
  index = result.size()-2;

  it = result.end();
  result.insert(it,after.begin(),after.end());

  return result;
}

int main() {
  long long n = readNum("Укажите количество мест N: ");
  long long k = readNum("Укажите количество школьников K: ");
  // long long n = 10;
  // long long k = 3;
  if(k>n){
    cout << "Школьников больше чем мест, некорректный ввод." << endl;
    exit(1);
  }
  long long index = NULL;
  vector<long long> seats = {n};
  for(long long i = 0; i < k; i++){
    seats = takeSeat(seats, index);
  }
  cout << "Мест слева: " << seats[index] << endl;
  cout << "Мест справа: " << seats[index+1] << endl;
}