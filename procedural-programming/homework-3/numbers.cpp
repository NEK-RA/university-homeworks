#include "numbers.h"

bool coutNumbers(){
  ifstream text;
  string filename;
  cout << "Введите имя файла: ";
  cin >> filename;
  text.open(filename);
  if(text){
    char ch = ' ';
    bool lastWasNum = true;
    cout << "Числа из файла " << filename << ":" << endl << endl;
    while(text >> ch){
      if(ch>='0' && ch<='9'){
        cout << ch;
        lastWasNum = true;
      }else{
        if(lastWasNum){
          cout << endl;
        }else{
          continue; 
        }
        lastWasNum = false;
      }
    }
    text.close();
    return true;
  }else{
    cout << "Не удалось открыть файл " << filename << " для чтения. Убедитесь что файл находится в той же папке, что и программа. Убедитесь что название файла содержит только латинские буквы или цифры. Программа будет перезапущена." << endl;
    return false;
  }
}