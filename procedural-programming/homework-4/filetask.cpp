#include "filetask.h"

bool fileTask(){
  string filename = "", line = "";
  int counter = 0;
  float num = 0;
  cout << "Укажите имя создаваемого файла: ";
  cin >> filename;
  ofstream file;
  file.open(filename);
  if(file){
    cout << "Введите 10 чисел, указывайте по одному числу на строке, в качестве разделителя у дробных чисел используйте точку:" << endl;
    while(counter < 10){
      num = readNum();
      file << num << endl;
      counter++;
      if(10-counter!=0){
        cout << "Осталось ввести " << 10-counter << " чисел" << endl;
      }
    }
    file.close();
    ifstream reader;
    reader.open(filename);
    float sum = 0;
    while(reader >> num){
      sum += num;
      cout << "Число на строке: " << num << "; текущая сумма: " << sum << endl;
    }
    cout << "Итоговая сумма: " << sum << endl;
  }else{
    cout << "Некорректное имя для файла. Программа будет перезапущена." << endl;
    cin.clear();
    cin.ignore(10000,'\n');
    return false;
  }
  return true;
}

float readNum(){
  float num = 0;
  bool good = false;
  while(!good){
    if(cin >> num){
      good = true;
    }else{
      cout << "Необходимо вводить только числа (1 строка = 1 число, точка - разделитель дробных чисел)" << endl;
      cin.clear();
      cin.ignore(10000,'\n');
    }
  }
  return num;
}