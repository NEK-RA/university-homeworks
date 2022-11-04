#include "texts.h"
/*
- [ ] Задание «Обработка текстовых файлов». Выполнить два варианта задания.
    - [ ] 32 - Шифрование текстового файла сдвигом в алфавите.
    - [ ] 27 - Вычисление частоты повтора символа в текстовом файле.
*/
char getChar(char src, int move){
  int code = src;
  int moved = code;
  if(src<='z' && src>='a'){
    moved += move;
    if (moved > 'z'){
      moved -= 26;
    }
    if (moved < 'a'){
      moved += 26;
    }
  }
  if(src<='Z' && src>='A'){
    moved += move;
    if (moved > 'Z'){
      moved -= 26;
    }
    if (moved < 'A'){
      moved += 26;
    }
  }
  char result = moved;
  return result;
}

string encrypt(string line, int move){
  for(int i=0; i<line.size();i++){
    line[i]=getChar(line[i],move);
  }
  return line;
}

string letterMove(){
  ifstream source;
  ofstream dest;
  string filename = "";
  string encrypted = "";
  string line = "";
  int move = 0;
  cout << "Подзадача: <Шифрование текстового файла сдвигом в алфавите>" << endl;
  cout << "Создайте текстовый файл в папке с программой, затем введите в программе имя файла." << endl;
  cout << "Важно: используйте английские буквы, все остальные будут игнорироваться" << endl;
  cout << "Файл для чтения: ";
  cin >> filename;
  if(filename != ""){
    encrypted = filename + ".enc";
    cout << "Укажите на сколько происходит сдвиг: ";
    if(!(cin >> move)){
      move = 13;
    }
    cout << "Файл для чтения: " << filename << endl;
    cout << "Сдвиг будет производиться на: " << move << " символ(а/ов) (по умолчанию было бы на 13)" << endl;
    cout << "Результат будет записан в файл: " << encrypted << endl;
    source.open(filename);
    if(source){
      // cout << "reading opened" << endl;
      dest.open(encrypted);
      if(dest){
        // cout << "destination opened" << endl;
        line = "";
        while(getline(source, line)){
          // cout << "read line from file: " << line << endl;
          dest << encrypt(line+"\n",move);
          // cout << "written encrypted line" << endl;
        }
      }else{
        cout << "Файл " << encrypted << " не удалось открыть для записи." << endl;
      }
      dest.close();
    }else{
      cout << "Файл " << filename << " не удалось открыть для чтения." << endl;
    }
    source.close();
  }
  return encrypted;
}


pair<char,float> mostFrequent(map<char,int> m){
  map<char,int>::iterator it = m.begin();
  float total = 0;
  // calculate total amount of symbols
  while (it != m.end())
  {
    total += it->second;
    it++;
  }
  cout << "Total symbols: " << total << endl;
  it = m.begin();
  
  char result = it->first;
  float mf = it->second / total;
  it++;

  while (it != m.end())
  {
    float cur = it->second / total;
    if(cur>mf){
      mf = cur;
      result = it->first;
    }
    it++;
  }
  cout << "most frequent char is: " << result << " with frequency " << mf << "%\n\n\n---------\n\n\n";
  return pair<char,float>(result,mf);
}

map<char,int> analyze(string filename){
  map<char,int> frequency;
  for(int i = 0; i <= ('z'-'a'); i++){
    frequency.insert(pair<char,int>('a'+i,0));
  }
  ifstream source;
  string line = "";
  source.open(filename);
  if(source){
    while(getline(source,line)){
      // cout << "current line: \"" << line << "\"" << endl;
      frequency = processLine(line,frequency);
      // printMap(frequency);
    }
  }else{
    cerr << "can't open file for reading" << endl;
  }
  source.close();
  return frequency;
}

bool contains(map<char,int> m,char key){
  map<char,int>::iterator it = m.find(key);
  return (it != m.end());
}

void printMap(map<char,int> m){
  map<char,int>::iterator it = m.begin();
  while (it != m.end())
  {
    cout << it->first << " --> " << it->second << endl;
    it++;
  }
  cout << endl << endl;
}

map<char,int> processLine(string line, map<char,int> frequency){
  char c;
  bool exist = false;
  for(int i = 0; i < line.size(); i++){
    c = tolower(line[i]);
    if(c>='a' && c<='z'){
      exist = contains(frequency,c);
      // cout << "Character \"" << c << "\" is found:" << exist << endl;
      if(exist){
        frequency[c]++;
      }else{
        frequency.insert(pair<char,int>(c,1));
      }
    }else{
      continue;
    }
  }
  return frequency;
}

bool analyzerPart(string filename){
  // string filename = "wikicpp.txt.enc";
  int choice = 0;
  map<char,int> target,base;
  
  cout << "Подзадача <Вычисление частоты повтора символа в текстовом файле>" << endl;
  cout << "По умолчанию будет открыт зашифрованный файл из предыдущей подзадачи(" << filename << "). Продолжить?" << endl;
  cout << "1. Да" << endl;
  cout << "2. Нет, указать свой файл" << endl;
  cout << "Выбор (номер пункта): ";
  if(cin >> choice){
    if(choice>=1 && choice<=2){
      if(choice==1){

        base = analyze("wikilinux.txt");
        printMap(base);
        pair<char,float> mfb = mostFrequent(base);
        
        target = analyze(filename);
        printMap(target);
        pair<char,float> mft = mostFrequent(target);

        cout << "with normal lang the most frequent character is:" << endl;
        cout << mfb.first << " with frequency " << mfb.second << "%" << endl;

        cout << "with text encrypted by caesar cipher the most frequent character is:" << endl;
        cout << mft.first << " with frequency " << mft.second << "%" << endl;

        cout << "based on that, assuming that caesar move is: " << (mft.first - mfb.first) << " symbols" << endl;
        
        return true;
      }else{
        cout << "Не удалось открыть файл для чтения" << endl;
        cin.clear();
        cin.ignore(10000,'\n');
        return false;
      }
    }else{
      cout << "Доступный выбор состоит из номеров 1 и 2." << endl;
      cin.clear();
      cin.ignore(10000,'\n');
      return false;
    }
  }else{
    cout << "Необходимо вводить число." << endl;
    cin.clear();
    cin.ignore(10000,'\n');
    return false;
  }
}