#include "rand.h"

/*
Пояснение для исправления:
в функции рандома использовать rand() и srand() чтобы высчитывалось на базе случайного числа
а не на базе N, и вывести N разных результатов
*/

bool genNumber(){
	int n=0,m=0,b=0,c=0;
	cout << "Введите число N - кол-во псевдо-случайных чисел: ";
	if(cin >> n){
		cout << "Определено условиями задания:" << endl;
		cout << "I вариант: m = 37, b = 3, c = 64" << endl;
		randNum(n,37,3,64);
		cout << endl;
		cout << "II вариант: m = 25173, b = 13849, c = 65537" << endl;
		randNum(n,25173,13849,65537);
		cout << endl;
		cout << "Укажите свои значения:" << endl;
		cout << "Укажите значение m:";
		if(cin >> m){
			cout << "Укажите значение b:";
			if(cin >> b){
				cout << "Укажите значение c:";
				if(cin >> c){
					randNum(n,m,b,c);
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

int randNum(int n, int m, int b, int c){
	if(n==0){
		return 0;
	}else{
		int s = 0;
		cout << s << "\t";
		for(int i=1;i<=n;i++){
				s = (m * s + b) % c;
				cout << s << "\t";
		}
		return 0;
	}
}
