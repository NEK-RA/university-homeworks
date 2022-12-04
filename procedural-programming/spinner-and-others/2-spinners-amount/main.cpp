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
  int m = abs(inputInt("Введите количество лопастей M: "));
  int t = 0;
  int f = 0;
  if(m>=3){
    if(m % 4 == 0){
      f = m / 4;
    }else{
      while(m>=3){
        t++;
        m-=3;
        if(m % 4 == 0){
          f = m / 4;
          m = 0;
        }
      }
      if(m != 0){
        t = 0;
        f = 0;
      }
    }
  }
    
  cout << "С тремя лопастями: " << t << endl;
  cout << "С четырьмя лопастями: " << f << endl; 
  cout << endl;
}