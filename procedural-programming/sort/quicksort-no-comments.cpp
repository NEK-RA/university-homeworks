#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <cstdlib>
using namespace std;

void printVector(vector<int> v){
  for(long unsigned int i=0;i<v.size();i++){
    cout << v[i] << " ";
  }
  cout << endl;
}

vector<int> sort(vector<int> array){
  if(array.size() < 2){
    return array;
  }
  vector<int> left = {};
  vector<int> right = {};
  int mid = array.size()/2;
  bool midskip = true;
  for(long unsigned int i=0; i<array.size(); i++){
    if(array[i]==array[mid]){
      if(midskip){
        midskip = false;
        continue;
      }else{
        left.push_back(array[i]);
      }
    }else if(array[i]<array[mid]){
      left.push_back(array[i]);
    }else if(array[i]>array[mid]){
      right.push_back(array[i]);
    }
  }
  left = sort(left);
  right = sort(right);
  vector<int> result = {};
  vector<int>::iterator it = result.begin();
  result.insert(it,right.begin(),right.end());
  it = result.begin();
  result.insert(it,array[mid]);
  it = result.begin();
  result.insert(it,left.begin(),left.end());
  return result;
}

int main() {
  system("clear");
  long timestamp = time(NULL);
  srand(timestamp);

  int len = 200000;
  int mod = 100000;
  cout << "Создадим массив A из " << len << " элементов со значениями от 0 до " << mod << ":" << endl;
  vector<int> a;
  for(long unsigned int i=0; i < len; i++){
    a.push_back(rand() % mod);
  }
  cout << "Исходный массив: " << endl;
  printVector(a);
  cout << endl << endl;
  long begin = time(NULL);
  cout << "Время начала: " << begin << endl;
  vector<int> sorted = sort(a);
  timestamp = time(NULL);
  cout << "Время завершения: " << timestamp << endl;
  cout << "Результат сортировки: " << endl;
  printVector(sorted);
  cout << endl << endl;
  cout << "Сортировка заняла: " << timestamp << " - " << begin << " = менее " << (timestamp - begin + 1) << " секунд(ы)" << endl;
}
