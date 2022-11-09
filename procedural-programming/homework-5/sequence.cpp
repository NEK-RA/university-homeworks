#include "sequence.h"
/*
- [x] 17 - Используя рекуррентное соотношение, вычислить сумму с точностью e = 10^-6, х вводится с клавиатуры. y = SUM(k=0,inf){ (k+2)! / ((k+1)^2 * x^(2k+2)) }
- [x] 34 - Дана строка S из n символов. Определить, содержаться ли в ней все символы (в произвольном порядке), входящие в слово «студенчество».
*/

int fact(int x){
  int mul = 1;
  if(x>1){
    for(int i=1; i<=x; i++){
      mul *=i;
    }
  }
  return mul;
}

double customSum(double x, double ac){
  double sum = 0;
  int k = -1;
  double next = 0;
  do{
    k++;
    next = ( fact(k+2) ) / ( pow(k+1,2) * pow(x,2*k+2) );
    sum += next;
  }while(abs(next) > ac);
  cout << "Вычисления завершены при k=" << k-1 << ". Значение последнего элемента суммы: " << next << endl;
  return sum;
}

bool calcSequence(){
  double x = 0;
  double accuracy = pow(10,-6);
  cout << "Введите X:" << endl;
  cout << "X=";
  if(cin >> x){
    if(x!=0){
      double result = customSum(x,accuracy);
      cout << "При X=" << x << " сумма ряда с заданной точностью составляет: " << result << endl;
      return true;
    }else{
      cout << "При X равном 0 выражение не имеет смысла" << endl;
      cin.clear();
      cin.ignore(10000,'\n');
      return false;
    }
  }else{
    cout << "Необходимо вводить числа" << endl;
    cin.clear();
    cin.ignore(10000,'\n');
    return false;
  }
}

void checkString(){
  /*
  Задача НЕ ГОТОВА
  wcout на фоне простого cout выдает следующий результат:

  Подзадача: проверка строки на вхождение в нее всех символов слова "студенчество"
2548B5 AB@>:C 4;O ?@>25@:8:


2 1K; =0945=? false
4 1K; =0945=? false
5 1K; =0945=? false
= 1K; =0945=? false
> 1K; =0945=? false
A 1K; =0945=? false
B 1K; =0945=? false
C 1K; =0945=? false
G 1K; =0945=? false


 AB@>:5 "" >BACBAB2C5B :0: <8=8<C< A8<2>; '2'. @>3@0<<0 1K;0 >AB0=>2;5=0 ?@8 =0E>645=88 ?5@2>3> >BACBAB2CNI53> A8<2>;0.
B>3>2K9 @57C;LB0B - 7040G0 2K?>;=5=0? false

  */
  // locale::global(locale("ru_RU.UTF-8"));
  wstring target = L"студенчество";
  wstring line;
  map<wchar_t,bool> found;
  for(wchar_t ch : target){
    found.insert(pair<wchar_t,bool>(ch,false));
  }
  wcout << L"Введите строку для проверки:" << endl;
  getline(wcin,line);
  // wcout << line << endl;
  for( pair<wchar_t,bool> letter : found ){
    if( line.find(letter.first) != line.npos ) {
      found[letter.first] = true;
    }
  }

  wcout << endl << endl;
  for( pair<wchar_t,bool> letter : found ){
    wcout << letter.first << L" был найден? " << boolalpha << letter.second << endl;
  }
  wcout << endl << endl;

  bool ok = true;
  for( pair<wchar_t,bool> letter : found ){
    if(!letter.second){
      ok = false;
      wcout << L"В строке \"" << line << L"\" отсутствует как минимум символ '" << letter.first << L"'. Программа была остановлена при нахождении первого отсутствующего символа." << endl;
      break;
    }
  }
  wcout << L"Итоговый результат - задача выполнена? " << boolalpha << ok << endl;
}