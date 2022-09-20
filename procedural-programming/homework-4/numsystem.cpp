#include "numsystem.h"

bool runNumSystem(){
  // for(int i=0; i< 16; i++){
  //   char c = getLetter(i);
  //   int n = getNum(c);
  //   cout << "Итерация " << i << ": число " << i << " в 16сс является " << c << ", а в 10сс - " << n << endl;
  // }
  return true;
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
  if(num <= 9){
    return num+'0';
  }else{
    return num-10+'A';
  }
}

int findPower(int num, int base){
  int power = 0;
  bool found = false;
  while(!found){
    int powered = pow(base, power);
    if(powered == num){
      found = true;
    }
    if(powered > num){
      found = true;
      power--;
    }
    power++;
  }
  return power;
}

string fromDecimal(int num, int target){
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
  return "";
}

int toDecimal(string num, int base){
  return 0;
}