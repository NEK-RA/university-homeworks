#include "rand.h"

/*
Пояснение для исправления:
в функции рандома использовать rand() (и можно srand()) чтобы высчитывалось на базе случайного числа
а не на базе N, но вывести N разных результатов
*/

bool genNumber(){
	int n=0,m=0,b=0,c=0;
	cout << "Введите число N - кол-во псевдо-случайных чисел: ";
	if(cin >> n){
		cout << "Определено условиями задания:" << endl;
		cout << "I вариант: m = 37, b = 3, c = 64" << endl;
		for(int i = 0; i < n; i++){
			cout << "Число " << i+1 <<  ": " << randNum(37,3,64) << endl;	
		}
		cout << endl;
		cout << "II вариант: m = 25173, b = 13849, c = 65537" << endl;
		for(int i = 0; i < n; i++){
			cout << "Число " << i+1 << ": " << randNum(25173,13849,65537) << endl;
		}
		cout << endl;
		cout << "Укажите свои значения:" << endl;
		cout << "Укажите значение m:";
		if(cin >> m){
			cout << "Укажите значение b:";
			if(cin >> b){
				cout << "Укажите значение c:";
				if(cin >> c){
					for(int i = 0; i < n; i++){
						cout << "Число " << i+1 << ": " << randNum(m,b,c) << endl;
					}
					return true;
				}else{
					cout << "Необходимо вводить только целые числа. Программа будет перезапущена." << endl;
					cin.clear();
					cin.ignore(10000,'\n');
					return false;
				}
			}else{
				cout << "Необходимо вводить только целые числа. Программа будет перезапущена." << endl;
				cin.clear();
				cin.ignore(10000,'\n');
				return false;
			}
		}else{
			cout << "Необходимо вводить только целые числа. Программа будет перезапущена." << endl;
			cin.clear();
			cin.ignore(10000,'\n');
			return false;
		}
	}else{
		cout << "Необходимо вводить только целые числа. Программа будет перезапущена." << endl;
		cin.clear();
		cin.ignore(10000,'\n');
		return false;
	}
}

unsigned int randNum(int m, int b, int c){
	int seed = rand() % 150000;
	if(seed <= 15){
		cout << "random seed = " << seed << endl;
	}
	if(seed==0){
		return 0;
	}else{
		unsigned int s = 0;
		if(seed <= 15){
			cout << s;
		}
		for(int i=1;i<=seed;i++){
				s = (m * s + b) % c;
				if(seed <= 15){
					cout << " --> " << s;
				}
		}
		return s;
	}
}
