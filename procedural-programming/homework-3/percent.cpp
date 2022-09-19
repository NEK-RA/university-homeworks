#include "percent.h"

bool calcPercent() {
  float m,s,n,r,p,target=0.01;
	cout << "Введите сумму займа: ";
	if(cin >> s){
    cout << "На сколько лет взят займ: ";
  	if(cin >> n){
      cout << "Укажите размер ежемесячных выплат (не менее " << (s/n)/12 << "  для 0%): ";
    	if(cin >> m){
        p = 0.0000;
      	bool done = false;
        int counter = 0;
      	while(!done)
      	{
      		r = p / 100;
      		float mt = (s * r * pow(1+r,n)) / (12*(pow(1+r,n)-1));
          float diff = m - mt;
          if(diff < 50){
            cout << fixed << "При проценте " << p << " выходит " << m << " - " << mt << " = " << m-mt << endl;
          }
          if(diff < target){
            done = true;
            float rounded = ceil(p*100)/100;
            // cout.unsetf(ios_base::floatfield); // for old c++
            cout << defaultfloat << "Итого: процент по займу составляет примерно " << rounded << "% (значение " << p << " округлено в большую сторону)" << endl;  
          }
          counter++;
      		p+=0.0001;
      	}
  
  	    return true;
      }else{
        cout << "Ошибка ввода: необходимо было вводить числа (для дробных разделитель - точка).  Программа будет перезапущена." << endl;
        cin.clear();
        cin.ignore(10000,'\n');
        return false;
      }
    }else{
      cout << "Ошибка ввода: необходимо было вводить числа (для дробных разделитель - точка).  Программа будет перезапущена." << endl;
      cin.clear();
      cin.ignore(10000,'\n');
      return false;
    }
  }else{
    cout << "Ошибка ввода: необходимо было вводить числа (для дробных разделитель - точка).  Программа будет перезапущена." << endl;
    cin.clear();
    cin.ignore(10000,'\n');
    return false;
  }
}