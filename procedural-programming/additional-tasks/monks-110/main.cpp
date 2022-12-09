#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
using namespace std;

void printmap(map<int,int> m){
  map<int,int>::iterator it = m.begin();
  while(it != m.end()){
    cout << "{" << it->first << ", " << it->second << "}" << endl;
    it++;
  }
}

vector<string> split(string str,string sub){
  vector<string> result = {};
  int next = str.find(sub);
  if(next != -1){
    int counter = 0;
    int first = 0;
    int len = str.find(sub) - first;
    while(next != -1){
      result.push_back(str.substr(first,len));
      first += len + 1;
      next = str.find(sub,first+1);
      if(next != -1){
        len = next - first;
      }
    }
    result.push_back(str.substr(first,str.size()-1));
  }else{
    result.push_back(str);
  }
  return result;
}

vector<string> readlines(){
  ifstream file("110.txt");
  if(file.is_open()){
    vector<string> data = {};
    string line = "";
    int counter = 1;
    while(getline(file,line)){
      if(regex_search(line,regex("^[0-9 ]*$"))){
        data.push_back(line);
      }else{
        cout << "ОШИБКА: На строке " << counter << " обнаружены лишние символы, строка пропущена (значения проигнорированы). Содержимое: " << endl;
        cout << line << endl << endl;
      }
      counter++;
    }
    file.close();
    return data;
  }else{
    cout << "ОШИБКА: Не удалось открыть файл для чтения" << endl;
  }
  return {};
}

map<int,int> getData(){
  // id монаха, id учителя
  map<int,int> monks = {};
  // string result = "32 41 42 43\n25 31 32 0\n24 33 34 0\n13 24 25 0\n11 21 22 23\n1 11 12 13";
  // vector<string> lines = split(result,"\n");
  vector<string> lines = readlines();
  vector<vector<int>> rawdata = {};
  vector<string> monkline = {};
  vector<int> monkdata = {};
  for(int i=0;i<lines.size();i++){
    monkline = split(lines[i]," ");
    if(monkline.size()==4){
      for(int j=0; j<monkline.size(); j++){
        monkdata.push_back(stoi(monkline[j]));
      }
      rawdata.push_back(monkdata);
      monkdata.erase(monkdata.begin(), monkdata.end());
    }else{
      cout << "ОШИБКА: В строке " << i+1 << " некорректное количество значений, строка пропущена (значения не учтены)"  << endl;
      continue;
    }
  }
  // вносим учеников
  for(int i=0; i < rawdata.size(); i++){
    for(int j=1; j<4; j++){
      if(rawdata[i][j]!=0){
        monks.insert({rawdata[i][j],rawdata[i][0]});
      }
    }
  }
  // проверяем наличие учителей и уведомляем пользователя об исходных данных при необходимости
  for(int i=0; i < rawdata.size(); i++){
    if( monks.find(rawdata[i][0])!= monks.end() ){
      continue;
    }else{
      if(rawdata[i][0]!=1){
        cout << "ОШИБКА: в исходных данных: Строка " << i+1 << " - в качестве учителя указан монах №" << rawdata[i][0] << ", который более нигде не упоминается (нет учителя)" << endl;
      }else{
        monks.insert({1,0});
      }
    }
  }
  return monks;
}

vector<int> checkMonk(int n, map<int,int> monks, bool print=false){
  if(n>=1 && n<=600){
    vector<int> masters = {};
    map<int,int>::iterator search;
    int next = 0;
    search = monks.find(n);
    while(search != monks.end()){
      next = search->second;
      if(next != 0){
        masters.push_back(next);
      }
      search = monks.find(next);
    }
    if(print){
      if(masters.empty()){
        cout << "Монаха с таким номером (№" << n <<") нет в исходных данных" << endl;
      }else{
        cout << "Монах №" << n << " обучался у монахов: ";
        for(int i=0; i<masters.size(); i++){
          if(i==masters.size()-1){
            cout << masters[i] << endl;
          }else{
            cout << masters[i] << " <- ";
          }
        }
      }
    }
    return masters;
  }else{
    if(print){
      cout << "ОШИБКА: Минимальный номер монаха: 1\nМаксимальный номер монаха: 600" << endl;
    }
    return {};
  }
}

bool found(int value, vector<int> data){
  for(int i=0; i< data.size(); i++){
    if(data[i]==value){
      return true;
    }
  }
  return false;
}

int findMaster(int one, int another, map<int,int> monks){
  if(one == another){
    return 0;
  }
  vector<int> m1 = checkMonk(one,monks);
  if(m1.empty()){
    cout << "ОШИБКА: Монаха с таким номером (№" << one <<") нет в исходных данных" << endl;
  }
  vector<int> m2 = checkMonk(another,monks);
  if(m2.empty()){
    cout << "ОШИБКА: Монаха с таким номером (№" << another <<") нет в исходных данных" << endl;
  }
  if(m1.empty() || m2.empty()){
    return 0;
  }


  int result = 0;
  if(one<another){
    for(int i = 0; i<m1.size(); i++){
      if(found(m1[i],m2)){
        result = m1[i];
        break;
      }
    }
  }else{
    for(int i = 0; i<m1.size(); i++){
      if(found(m2[i],m1)){
        result = m2[i];
        break;
      }
    }
  }
  return result;
}

vector<vector<int>> getTasks(){
  string rawtasks = "";
  string line = "";
  vector<vector<int>> tasks = {};
  vector<string> parts = {};

  cout << "Введите все необходимые строки с заданиями. " << endl;
  cout << "Формат строк: " << endl;
  cout << "1 10 - если необходимо проверить существование монаха и выяснить номера его учителей" << endl;
  cout << "2 24 35 - если необходимо найти ближайшего общего учителя двух монахов" << endl;
  cout << "Когда все данные будут введены, с новой строки введите END, чтобы завершить ввод" << endl;
  cout << "Ввод: " << endl;
  while(line != "END"){
    getline(cin,line);
    if(line=="END"){
      break;
    }
    if(regex_search(line,regex("^[0-9 ]*$"))){
      parts = split(line," ");

      if(parts[0] == "1" && parts.size() == 2){
        tasks.push_back({stoi(parts[0]), stoi(parts[1])});
      }else if(parts[0] == "1" && parts.size() != 2){
        cout << "ПРЕДУПРЕЖДЕНИЕ: Обнаружено несоответствие формату ввода, строка проигнорирована" << endl;
      }

      if(parts[0] == "2" && parts.size() == 3){
        tasks.push_back({stoi(parts[0]), stoi(parts[1]), stoi(parts[2])});
      }else if(parts[0] == "2" && parts.size() != 3){
        cout << "ПРЕДУПРЕЖДЕНИЕ: Обнаружено несоответствие формату ввода, строка проигнорирована" << endl;
      }

      if(parts[0] != "1" && parts[0] != "2"){
        cout << "ПРЕДУПРЕЖДЕНИЕ: код 1 используется для проверки монаха, код 2 для поиска общего учителя, других кодов не предусмотрено, строка проигнорирована" << endl;
      }
    }else{
      cout << "ПРЕДУПРЕЖДЕНИЕ: Обнаружены посторонние символы, строка проигнорирована" << endl;
    }
  }
  cout << "Дано " << tasks.size() << " задач" << endl;
  return tasks;
}

int main(){
  vector<vector<int>> tasks = getTasks();
  map<int,int> monks = getData();
  int id = 0;
  if(monks.empty()){
    cout << "Список монахов отсутствует!" << endl;
    return 1;
  }
  for(int i = 0; i<tasks.size(); i++){
    if(tasks[i][0]==1){
      checkMonk(tasks[i][1], monks, true);
    }else{
      id = findMaster(tasks[i][1],tasks[i][2], monks);
      if(id != 0){
        cout << "Ближайший общий учитель монахов №" << tasks[i][1] << " и №" << tasks[i][2] << ": монах №" << id << endl;
      }else{
        cout << "Ближайший общий учитель монахов №" << tasks[i][1] << " и №" << tasks[i][2] << ": не был найден. Причина поясняется одной из ошибок выше." << endl;
      }
    }
  }
  return 0;
}

/*
+1. каждый монах известен миру только по своему личному номеру;
+2. у каждого монаха в течение жизни не может быть более трех учеников;
+3. у каждого монаха есть только один учитель.

решить следующие задачи:

- по номеру монаха узнать, был ли такой монах и если был, то кто были его учитель, учитель его учителя и т.д. до самого Святого Павла;
- по двум монашеским номерам найти их общего ближайшего учителя.

Исходные данные: строки, в каждой указан номер монаха и после него три номера его учеников, если у монаха было менее трех учеников, то на соответствующих местах будут нули

Ввод: строки, в каждой стоит код(кол-во номеров дальше) и один или два монашеских номера.

Указания:
Святой Павел  = 1;
id остальных от 2 до 600;
номера монахов не обязательно последовательны, но номер ученика всегда больше, чем номер его учителя.

## Пример

Исходные данные о монахах:

```
32 41 42 43
25 31 32 0
24 33 34 0
13 24 25 0
11 21 22 23
1 11 12 13
```

Вариант задания:

```
1 31
1 51
2 34 41
2 31 51
```

Результаты работы программы:

```
31 – монах, его учителя 25, 13
51 – не монах
34 и 41 – оба монахи, и их общий учитель 13
51 – не монах
```

*/
