#include "display.h"

bool coutFile(){
  ifstream reading;
  ofstream writing;

  cout << endl << endl << "Этап 1: Запись данных в файл" << endl << endl;
  
  string filename;
  cout << "Введите имя создаваемого файла: ";
  cin >> filename;
  writing.open(filename);
  if(writing){
    string input="",line="";
    cout << "Введите содержимое файла. Введите ---end--- для завершения ввода.\nСодержимое:\n";
    while(getline(cin,line)){
      if(line=="---end---"){
        break;
      }
      input += line + "\n";
    }
    writing << "---START-OF-USER-CONTENT---\n" << input << "\n---END-OF-USER-CONTENT---" << endl;
    writing.close();
  }

  cout << endl << endl << "Этап 2: Считывание данных из файла" << endl << endl;
  cout << "Введите имя читаемого файла: ";
  cin >> filename;
  
  reading.open(filename);
  if(reading){
    string line = "";
    cout << "Содержимое файла " << filename << ":" << endl << endl;
    while(getline(reading, line)){
      cout << line << endl; 
    }
    reading.close();
    return true;
  }else{
    cout << "Не удалось открыть файл " << filename << " для чтения. Убедитесь что файл находится в той же папке, что и программа. Убедитесь что название файла содержит только латинские буквы или цифры. Программа будет перезапущена." << endl;
    return false;
  }
}