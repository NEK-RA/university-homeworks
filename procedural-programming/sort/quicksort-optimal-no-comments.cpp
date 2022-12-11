#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

void swap(int &a, int &b){
  int tmp = a;
  a = b;
  b = tmp;
}

void printVector(vector<int> &a, string comment = ""){
  if(comment != ""){
    cout << comment << endl;
  }
  for(int i=0; i<a.size();i++){
    cout << a[i] << " ";
  }
  cout << endl;
}

int partition(vector<int> &a, int low, int high){
  int pivot = a[(low+high)/2];
  int i = low;
  int j = high;
  while(true){
    while(a[i] < pivot){
      i++;
    }
    while(a[j] > pivot){
      j--;
    }
    if(i >= j){
      return j;
    }
    swap(a[i++],a[j--]);
  }
}

void quicksort(vector<int> &a, int low, int high){
  if(low < high){
    int p = partition(a, low, high);
    quicksort(a,low,p);
    quicksort(a,p+1,high);
  }

}

int main() {

  long timestamp = chrono::duration_cast<std::chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
  srand(timestamp);
  cout << "Время запуска: " << timestamp << endl;
  cout << "Проверить можно:" << endl
    << "> https://ya.ru/?q=" << timestamp << endl
    << "> https://ddg.gg/?q=timestamp+" << timestamp << endl
    << "> Указав время запуска на https://timestamp.online/" << endl << endl;
  
  int len = 200000;
  int mod = 100000;
  cout << "Создадим массив A из " << len << " элементов со значениями от 0 до " << mod << ":" << endl;
  vector<int> a;
  for(long unsigned int i=0; i < len; i++){
    a.push_back(rand() % mod);
  }
  printVector(a,"До сортировки:");
  cout << endl << endl << string(30,'-') << endl << endl;
  chrono::time_point<chrono::system_clock> sortstart = chrono::system_clock::now();
  quicksort(a, 0, a.size()-1);
  chrono::time_point<chrono::system_clock> sortfinish = chrono::system_clock::now();
  chrono::duration<double> diff = sortfinish - sortstart;

  printVector(a,"После сортировки:");
  cout << "Сортировка заняла: " << fixed << diff.count() << " секунд(ы)" << endl;
}