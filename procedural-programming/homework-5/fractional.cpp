/*
Создать файл из n из вещественных чисел. Отсортировать его элементы по сумме цифр дробной части. Результат сохранить в другом файле. Программу написать с использованием подпрограмм(ы).
*/
#include "fractional.h"

void printVector(vector<pair<int,string>> data, bool toFile = false){
  if(toFile){
    string filename;
    cout << "Укажите название файла для записи результата: ";
    cin >> filename;
    ofstream out(filename);
    if(out.is_open()){
      for(int i = 0; i < data.size(); i++){
        out << data[i].second << endl;
      }
      cout << "Отсортированный список записан в файл" << filename << "." << endl;
    }
  }else{
    for(int i = 0; i < data.size(); i++){
      cout << "{" << data[i].first << ":" << data[i].second << "}, ";
    }
    cout << endl;
  }
}

vector<pair<int,string>> quicksort(vector<pair<int,string>> array){
  
  if(array.size() < 2){
    return array;
  }
  
  vector<pair<int,string>> left = {};
  vector<pair<int,string>> right = {};
  
  int mid = array.size()/2;
  pair<int,string> midpair = array[mid];
  
  // bool midskip = true;
  for(long unsigned int i=0; i<array.size(); i++){
    if(array[i].first==midpair.first){
      if(i==mid){
        // midskip = false;
        continue;
      }else{
        left.push_back(array[i]);
      }
    }else if(array[i].first < midpair.first){
      left.push_back(array[i]);
    }else if(array[i].first > midpair.first){
      right.push_back(array[i]);
    }
  }

  left = quicksort(left);
  right = quicksort(right);
  
  vector<pair<int,string>> result = {};
  
  vector<pair<int,string>>::iterator it = result.begin();
  result.insert(it,right.begin(),right.end());
  
  it = result.begin();
  result.insert(it,midpair);
  
  it = result.begin();
  result.insert(it,left.begin(),left.end());
  
  return result;
}

int fractsum(string num){
  int sum = 0;
  int dot = num.find(".");
  // cout << "dot found at position: " << dot << endl;
  if(dot != -1){
    string sub = num.substr(dot+1);
    // cout << "num: " << num << ",  fractal part: " << sub << endl;
    if(sub != ""){
      int part = stoi(sub);
      while(part!=0){
        sum += part % 10;
        part /= 10;
      } 
    }
  }
  return sum;
}

string genfile(){
  int amount = 0;
  string filename = "";
  float num = 0;
  cout << "Сколько чисел надо сгенерировать: ";
  if(cin >> amount){
    amount = abs(amount);
    cout << "Укажите имя генерируемого файла: ";
    cin >> filename;
    ofstream src(filename);
    if(src.is_open()){
      unsigned int timestamp = time(NULL);
      srand(timestamp);
      for(int i=0; i<amount; i++){
        num = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (rand() % 1000);
        src << num << endl;
      }
      cout << "Файл "<< filename << " сгенерирован." << endl;
    }else{
      cout << "Не удалось открыть файл для записи" << endl;
      cin.clear();
      cin.ignore(10000,'\n');
      filename = "";
    }
  }else{
    cout << "Необходимо вводить целое число." << endl;
    cin.clear();
    cin.ignore(10000,'\n');
  }
  
  return filename;
}

void sortFracts(){

  string filename = "";
  while(filename==""){
    filename = genfile();
  }

  vector<pair<int,string>> array;
  ifstream source(filename);
  string number = "";
  int place = -1;
  if(source.is_open()){
    while(getline(source,number)){
      // проверка лишних знаков препинания
      // запятые заменяются точкой
      do{
        place = number.find(",");
        if(place != -1){
          number = number.replace(place,1,".");
        }
      }while(number.find(",")!=-1);
      bool multdots = (number.find(".") != number.rfind("."));
      if(multdots){
        cout << "Число " << number << " не является корректным (более одного разделителя), оно будет пропущено." << endl;
        continue;
      }
      bool correct = regex_search(number,regex("^-?[0-9]*\.[0-9]*$"));
      if(!correct){
        cout << "Число " << number << " не является корректным (содержит посторонние символы), оно будет пропущено." << endl;
        continue;
      }
      array.push_back({fractsum(number),number});
    }
  }


  cout << "Список до сортировки: " << endl;
  printVector(array);
  vector<pair<int,string>> sorted = quicksort(array);
  cout << "Отсортированный список: " << endl;
  printVector(sorted);
  printVector(sorted,true);

}