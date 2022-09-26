#include <iostream>
#include "filetask.h"
#include "sign.h"
#include "geometry.h"
#include "rand.h"
#include "numsystem.h"
using namespace std;

int main() {
	cout << "1. Задача <Файл>" << endl;
	bool ftDone = false;
	while(!ftDone){
		ftDone = fileTask();
		cout << endl;
	}
	cout << endl << endl;

	// cout << "2. Задача <Знак числа>" << endl;
	// for(int i=0;i<3;i++){
	// 	getSign();
	// }
	// cout << endl << endl;

	// cout << "3. Задача <Геометрические фигуры>" << endl;
	// runGeometry();
	// cout << endl << endl;

	// cout << "7. Задача <Генератор псевдослучайных чисел>" << endl;
	// bool numGenerated = false;
	// while(!numGenerated){
	// 	numGenerated = genNumber();
	// 	cout << endl;
	// }
	// cout << endl << endl;

  // cout << "9. Задача <Системы счисления>" << endl;
  // bool numConverted = false;
  // while(!numConverted){
  //   numConverted = runNumSystem();
  //   cout << endl;
  // }
  // cout << endl << endl;
}
