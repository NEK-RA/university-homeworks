#include <iostream>
using namespace std;

int inputInt(string message){
  bool read = false;
  int a = NULL;
  while(!read){
    cout << message;
    if(cin >> a){
      read = true;
    }else{
      cout << "Необходимо вводить только целые числа!" << endl;
      cout << endl;
      cin.clear();
      cin.ignore(10000,'\n');
    }
  }
  cout << endl;
  return a;
}

int main() {
  cout << "Hello World!\n";
  int a=0,b=0,c=0,n=0;
  a = abs(inputInt("Укажите стоимость основания А: "));
  b = abs(inputInt("Укажите стоимость одной лопасти В: "));
  c = abs(inputInt("Укажите максимальную стоимость С: "));
  if(a+b>c){
    n = 0;
  }else{
    n = (c-a) / b;
  }
  cout << "Максимальное кол-во лопастей спиннера N: " << n << endl;
}