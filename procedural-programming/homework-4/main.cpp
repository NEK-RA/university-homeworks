#include <iostream>
#include <cstdlib>
#include "filetask.h"
#include "sign.h"
#include "geometry.h"
#include "timegone.h"
#include "sinus.h"
#include "rome.h"
#include "rand.h"
#include "matrix.h"
#include "numsystem.h"
using namespace std;

int main() {
  setlocale(0, "");
	// cout << "1. Задача <Файл>" << endl;
	// bool ftDone = false;
	// while(!ftDone){
	// 	ftDone = fileTask();
	// 	cout << endl;
	// }
	// cout << endl << endl;

	// cout << "2. Задача <Знак числа>" << endl;
	// for(int i=0;i<3;i++){
	// 	getSign();
	// }
	// cout << endl << endl;

	// cout << "3. Задача <Геометрические фигуры>" << endl;
	// runGeometry();
	// cout << endl << endl;

	// cout << "4. Задача <Былая слава>" << endl;
	// printFlag();
	// cout << endl << endl;
  
  cout << "5. Задача <Синусоида>" << endl;
	printSinusoid();
	cout << endl << endl;

	// cout << "6. Задача <Автоматный распознаватель>" << endl;
	// bool romeConverted = false;
	// while(!romeConverted){
	//	 romeConverted = convertRomeNumber();
	//	 cout << endl;
	// }
	// cout << endl << endl;


	// cout << "7. Задача <Генератор псевдослучайных чисел>" << endl;
	// bool numGenerated = false;
	// while(!numGenerated){
	// 	numGenerated = genNumber();
	// 	cout << endl;
	// }
	// cout << endl << endl;
  
  // cout << "8. Задача <Умножение матриц>" << endl;
  // multiplyMatrix();
	// cout << endl << endl;
  

  // cout << "9. Задача <Системы счисления>" << endl;
  // bool numConverted = false;
  // while(!numConverted){
  //   numConverted = runNumSystem();
  //   cout << endl;
  // }
  // cout << endl << endl;
  // system("pause");
}
