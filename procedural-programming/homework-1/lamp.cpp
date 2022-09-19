#include "lamp.h"

bool isLightTask(){
  cout << "Программа задаст несколько вопросов. Для указания ответа используйте номер соответсвующего варианта" << endl;
  int morning=1,day=2,evening=3,night=4,tod=0;
  int curtains=0,opened=1,closed=2;
  int lamp=0,on=1,off=2;
  
  cout << "Укажите время суток:" << endl
  << "1. Утро" << endl
  << "2. День" << endl
  << "3. Вечер" << endl
  << "4. Ночь" << endl
  << "Ваш выбор: ";
  if(cin >> tod){
    if (tod>0 && tod <5){
      
      cout << "Укажите состояние штор:" << endl 
      << "1. Открыты" << endl
      << "2. Закрыты" << endl 
      << "Ваш выбор: ";
      if(cin >> curtains){
        if(curtains>0 && curtains<3){

          cout << "Укажите состояние лампы:" << endl 
          << "1. Включена" << endl
          << "2. Выключена" << endl 
          << "Ваш выбор: ";
          if(cin >> lamp){
            if(lamp>0 && lamp<3){

              bool result = (tod==day && curtains==opened) || (lamp==on);
              if(result){
                cout << "Итог: в комнате СВЕТЛО" << endl;
                return true;
              }else{
                cout << "Итог: в комнате ТЕМНО" << endl;
                return true;
              }
              
            }else{
              cout << "Указан некорректный вариант ответа. Допустимые варианты ответа: 1-2. Программа будет перезапущена." << endl;
              return false;
            }
          }else{
            cout << "Введено некорректное значение. Программа будет перезапущена." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            return false;
          }
          
        }else{
          cout << "Указан некорректный вариант ответа. Допустимые варианты ответа: 1-2. Программа будет перезапущена." << endl;
          return false;
        } 
      }else{
        cout << "Введено некорректное значение. Программа будет перезапущена." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
      }
      
    }else{
      cout << "Указан некорректный вариант ответа. Допустимые варианты ответа: 1-4. Программа будет перезапущена." << endl;
      return false;
    }
  }else{
    cout << "Введено некорректное значение. Программа будет перезапущена." << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    return false;
  }
}