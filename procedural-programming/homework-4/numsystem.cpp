#include "numsystem.h"

bool runNumSystem(){
	string num = "";
	int base = 0, target = 0;
	disclaimer();
	cout << "Введите число для перевода: ";
	cin >> num;
	num = upper(num);
	cout << "Укажите исходную систему счисления: ";
	if(cin >> base){
		if(validate(num,base) && base >= 2 && base <= 36){
			cout << "Укажите целевую систему счисления: ";
			if(cin >> target){
				
				unsigned long long decimal = toDecimal(num,base);
				string result = fromDecimal(decimal,target);
				cout << "Результат перевода: " << result << endl;
				return 0;
				
			}else{
				if(target < 2){
					cout << "Минимальное основание системы счисления - 2. Программа будет перезапущена." << endl;
				}else{
					if(target > 36){
						cout << "Максимальное основание системы счисления - 36 (10 цифр + английский алфавит). Программа будет перезапущена" << endl;
					}else{
						cout << "Основания систем счисления должны быть целыми десятичными числами. Программа будет перезапущена." << endl;
					}
				}
				cin.clear();
				cin.ignore(10000,'\n');
				return 1;
			}
		}else{
			if(base < 2){
				cout << "Минимальное основание системы счисления - 2. Программа будет перезапущена." << endl;
			}else{
				if(base > 36){
					cout << "Максимальное основание системы счисления - 36 (10 цифр + английский алфавит). Программа будет перезапущена" << endl;
				}else{
					cout << "Число " << num << " не является корректным в системе счисления с основанием " << base << ". Программа будет перезапущена." << endl;
				}
			}			
			cin.clear();
			cin.ignore(10000,'\n');
			return 1;
		}
	}else{
		cout << "Основания систем счисления должны быть целыми десятичными числами. Программа будет перезапущена." << endl;
		cin.clear();
		cin.ignore(10000,'\n');
		return 1;
	}
}

void disclaimer(){
	cout << "Программа переводит числа в диапазоне unsigned long long" << endl;
  	cout << "Это означает, что минимальное число для ввода: 0" << endl;
  	cout << "Максимальные числа в системах счисления 2-36:" << endl;
  	for(int i=2; i<=36; i++){
    	cout << "В " << i << "сс\t---\t" << fromDecimal(18446744073709551615ull, i) << endl;
  	}
  	cout << endl;
}

string upper(string str){
  	for(int i=0; i < str.size(); i++){
    	str[i] = toupper(str[i]);
  	}
  	return str;
}

bool validate(string num, int base){
	bool isValid = true;
	int single = -1;
	for(unsigned int i = 0; i < num.size(); i++){
		single = getNum(num[i]);
		if(single >= base){
			isValid = false;
			break;
		}
	}
  	string higher = fromDecimal(18446744073709551615ull, base);
  
  	if(higher.size() < num.size()){
    	isValid = false;
  	}

  	if(higher.size() == num.size()){
    	for(int i = 0; i < num.size(); i++){
      		if(num[i] > higher[i]){
        		isValid = false;
        		break;
      		}
    	}   
  	}
  
	return isValid;
}

int getNum(char ch){
	int result = -1;
  	bool isLetter = false;
  	if(ch >= '0' && ch <= '9'){
    	result = ch - '0';
  	}
  	if(ch  >= 'A' && ch <= 'Z'){
    	result = ch - 'A';
    	isLetter = true;
  	}
  	if(result != -1 && isLetter){
    	result += 10;
  	}
  	return result;
}

char getLetter(int num){
	char c = ' ';
  	if(num <= 9){
    	c = num+'0';
  	}else{
    	c = num-10+'A';
  	}
  	return c;
}

int findLength(int num, int base){
	if(num >= 1){
		int counter = 0;
		while(num > 0){
			num = num / base;
			counter++;
		}
		return counter;
	}else{
		return 1;
	}
}

string fromDecimal(unsigned long long num, int target){
	//cout << num << " -> 2cc" << endl;
	if(num == 0){
		return "0";
	}else{
		// int length = findLength(num,target);
		// int counter = 1;
		string converted = "";
		int last = -1;
		while(num > 0){
			last = num % target;
			converted = getLetter(last) + converted;
			num = num / target;
			//counter++;
		}
		return converted;
	}
}

unsigned long long toDecimal(string num, int base){
	int power = num.size()-1;
	// cout << num << "(" << base << "cc) -> ? (10cc)\n Max power = " << power << endl;
	unsigned long long decimal = 0;
	for(unsigned int i=0; i < num.size(); i++){
		decimal += (unsigned long long)(getNum(num[i]) * pow(base,power-i));
	}
	// cout << "Result: " << decimal << endl;
  return decimal;
}
