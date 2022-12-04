#include <iostream>
using namespace std;

void calc(int m, int n){
  int s = 0;

  for(int i = 1; i <= m; i++){
    for(int j = 1; j <= n; j++){
      // В каждой строке Mx1 находится M фигур 1х1
      // M-1 фигур 2х1
      // M-2 фигур 3х1 и т.д.
      // m+1-i используется чтобы для 1х1 получилось m а при большем размере фигур уже начинало уменьшаться
      s += (m+1-i)*j;
      // cout << "учтена фигура " << (m+1-i) << "x" << j << endl;
    }
  }
  cout << "результат программы для (" << m << "x" << n << "): " << s << endl;
  cout << "правильный ответ: " << ((m * m + m) * (n * n + n) / 4) << " по формуле (x^2+1)*(y^2+1)/4" << endl;
}

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
  int m = inputInt("Укажите ширину листа M: ");
  int n = inputInt("Укажите высоту листа N: ");
  calc(m,n);
}