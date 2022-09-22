#include "geometry.h"

void runGeometry(){
  bool rd = false, td = false, cd = false;
  while(!rd){
    rd = calcRectangle();
    cout << endl;
  }
  while(!td){
    td = calcTriangle();
    cout << endl;
  }
  while(!cd){
    cd = calcCircle();
    cout << endl;
  }
}

bool calcRectangle(){
  float a = 0, b = 0;
  cout << "Укажите параметры прямоугольника: " << endl;
  cout << "Укажите длинну: ";
  if(cin >> a){
    cout << "Укажите ширину: ";
    if(cin >> b){
      cout << "Площадь прямоугольника размерами " << a << "x" << b << " составляет " << a*b << endl;
      return true;
    }else{
      cout << "Необходимо вводить числа (разделитель - точка)." << endl;
      cin.clear();
      cin.ignore(10000,'\n');
      return false;
    }
  }else{
    cout << "Необходимо вводить числа (разделитель - точка)." << endl;
    cin.clear();
    cin.ignore(10000,'\n');
    return false;
  }
}

bool calcTriangle(){
  return true;
}

bool calcCircle(){
  return true;
}
