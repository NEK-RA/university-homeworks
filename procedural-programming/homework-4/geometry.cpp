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
  float a = 0, h = 0;
  cout << "Укажите параметры треугольника: " << endl;
  cout << "Укажите длину основания: ";
  if(cin >> a){
    cout << "Укажите высоту: ";
    if(cin >> h){
      cout << "Площадь треугольника составляет: " << fixed << (a*h)/float(2) << endl;
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
  return true;
}

bool calcCircle(){
  float r = 0;
  cout << "Укажите радиус круга: ";
  if(cin >> r){
    cout << "Площадь круга составляет: " << M_PI * r * r << endl;
    return true;
  }
  else{
    cout << "Необходимо вводить числа (разделитель - точка)." << endl;
    cin.clear();
    cin.ignore(10000,'\n');
    return false;
  }
}
