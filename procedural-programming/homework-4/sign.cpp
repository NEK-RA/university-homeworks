#include "sign.h"

short sign(double x){
	if(x==0){
		return 0;
	}else{
		if(x>0){
			return 1;
		}else{
			return -1;
		}
	}
}

void getSign(){
	double num = 0;
	bool correct  = false;
	while(!correct){
		cout << "Укажите число: ";
		if(cin >> num){
			correct = true;
			cout << "sign(" << num << ")="<< sign(num) << endl;
		}else{
			correct = false;
			cout << "Необходимо вводить числа (для дробных разделитель - точка)." << endl;
			cin.clear();
			cin.ignore(10000,'\n');
		}
	}
}
