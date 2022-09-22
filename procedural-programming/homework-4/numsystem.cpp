#include "numsystem.h"

bool runNumSystem(){
	string num = "";
	int base = 0, target = 0;
	cout << "Введите число для перевода: ";
	cin >> num;
	cout << "Укажите исходную систему счисления: ";
	if(cin >> base){
		if(validate(num,base) && base >= 2){
			cout << "Укажите целевую систему счисления: ";
			if(cin >> target){
				
				int decimal = toDecimal(num,base);
				string result = fromDecimal(decimal,target);
				cout << "Результат перевода: " << result << endl;
				return true;
				
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
				return false;
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
			return false;
		}
	}else{
		cout << "Основания систем счисления должны быть целыми десятичными числами. Программа будет перезапущена." << endl;
		cin.clear();
		cin.ignore(10000,'\n');
		return false;
	}
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
	return isValid;
}

int getNum(char ch){
  int result = -1;
  bool isLetter = false;
  if(ch >= '0' && ch <= '9'){
    result = ch - '0';
  }
  if(ch >= 'a' && ch <= 'z'){
    result = ch - 'a';
    isLetter = true;
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

string fromDecimal(int num, int target){
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
	
  /* my python converter
def from_decimal_to(number,base):
  if number != 0:
    converted = []
    while number > 0:
      digit = number % base
      if digit <= 9:
        converted.insert(0,str(digit))
      else:
        converted.insert(0,get_letter(digit))
      number //= base
    return "".join(converted)
  else:
    return "0"
  */
  //return "";
}

int toDecimal(string num, int base){
	int power = num.size()-1;
	// cout << num << "(" << base << "cc) -> ? (10cc)\n Max power = " << power << endl;
	int decimal = 0;
	for(unsigned int i=0; i < num.size(); i++){
		decimal += getNum(num[i]) * pow(base,power-i);
	}
	// cout << "Result: " << decimal << endl;
  return decimal;
}
