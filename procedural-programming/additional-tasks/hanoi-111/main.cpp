#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cmath>
using namespace std;

struct tower{
  string name;
  vector<int> rings;
};

vector<int> gentower(int n);
void printTowers(tower &t1, tower &t2, tower &t3, int n, bool clear=true);
void move(tower &from, tower &to, tower &unused, int on, bool print);
int transfer(tower &t1, tower &t2, tower &t3, int n, int on, bool print);

int getSleepMs(){
  // return 500;
  // return 250;
  return 100;
}

void sleep(){
  this_thread::sleep_for(
    chrono::milliseconds(
      getSleepMs()
    )
  );
}

int main() {
  int n = 30;
  // 30 без вывода - ~15 секунд в replit
  // 30 без вывода - ~168 секунд на нетбуке
  // с выводом лучше демонстрировать n=5 с задержкой 250мс или 500мс
  // для большего n с выводом лучше использовать задержку не менее 100мс
  bool show = false;
  tower t1 = {"башня 1", gentower(n)};
  tower t2 = {"башня 2", {}};
  tower t3 = {"башня 3", {}};
  printTowers(t1,t2,t3,n);//,false);
  chrono::time_point<std::chrono::system_clock> start = chrono::system_clock::now();
  unsigned long long moves = transfer(t1,t2,t3,n,n,show);
  chrono::time_point<std::chrono::system_clock> end = chrono::system_clock::now();
  printTowers(t1,t2,t3,n,false);
  chrono::duration<double> diff = end - start;
  cout << "Статистика: " << endl;
  cout << "Произошло " << moves << " перемещений колец" << endl;
  cout << "Прошло " << fixed << diff.count() << " секунд" << endl;
  double eta = diff.count() * pow(2,64-n);
  cout << "Для 64 колец ожидаемое время ~";
  if(eta < 60){
    cout << eta << " секунд" << endl;
  }
  if(eta < 3600){
    cout << eta/60 << " минут" << endl;
  }
  if(eta < 86400){
    cout << eta/3600 << " часов" << endl;
  }
  if(eta < 604800){
    cout << eta/86400 << " суток" << endl;
  }
  if(eta < 2592000){
    cout << eta/604800 << " недель" << endl;
  }
  if(eta < 31104000){
    cout << eta/2592000 << " месяцев" << endl;
  }
  if(eta >= 31104000){
    cout << eta/31104000 << " лет" << endl;
  }
  
  if(show){
    double slept = (getSleepMs()*moves)/1000.;
    cout << "Из них " << slept << " секунд ушло на паузы между выводом" << endl;
    cout << "Время на вычисления составляет примерно " << diff.count()-slept << " секунд" << endl;
  }
  
}

int transfer(tower &src, tower &tmp, tower &tgt, int n, int on, bool print){
  unsigned long long counter = 0;
  if(n==1){
    move(src,tgt,tmp,on,print);
    counter++;
  }else if(n==2){
    move(src,tmp,tgt,on,print);
    move(src,tgt,tmp,on,print);
    move(tmp,tgt,src,on,print);
    counter += 3;
  }else{
    counter += transfer(src,tgt,tmp,n-1,on,print);
    move(src,tgt,tmp,on,print);
    counter++;
    counter += transfer(tmp,src,tgt,n-1,on,print);
  }
  return counter;
}

void move(tower &from, tower &to, tower &unused, int on, bool print){
  int num = from.rings.back();
  //cout << "Перемещаем кольцо (" << num << ") с <" << from.name << "> на <" << to.name << ">" << endl;
  from.rings.pop_back();
  to.rings.push_back(num);
  if(print){
    printTowers(from, to, unused, on);
  }
}

void printTowers(tower &t1, tower &t2, tower &t3, int n, bool clear){
  tower first,second,third;
  // определяем правильный порядок
  if(t1.name == "башня 1"){
    first = t1;
  }else if(t1.name == "башня 2"){
    second = t1;
  }else if(t1.name == "башня 3"){
    third = t1;
  }
  // так же для башни 2
  if(t2.name == "башня 1"){
    first = t2;
  }else if(t2.name == "башня 2"){
    second = t2;
  }else if(t2.name == "башня 3"){
    third = t2;
  }
  // так же для башни 3
  if(t3.name == "башня 1"){
    first = t3;
  }else if(t3.name == "башня 2"){
    second = t3;
  }else if(t3.name == "башня 3"){
    third = t3;
  }
  string pic = "";
  for(int i = n-1; i >= 0; i--){
    if(first.rings.size()>i){
      pic += to_string(first.rings[i]);
      if(first.rings[i]<10 && n>=10){
        pic += " ";
      }
    }else{
      pic += " ";
      if(n>=10){
        pic += " ";
      }
    }
    pic += "  |  ";
    if(second.rings.size()>i){
      pic += to_string(second.rings[i]);
      if(second.rings[i]<10 && n>=10){
        pic += " ";
      }
    }else{
      pic += " ";
      if(n>=10){
        pic += " ";
      }
    }
    pic += "  |  ";
    if(third.rings.size()>i){
      pic += to_string(third.rings[i]);
      if(third.rings[i]<10 && n>=10){
        pic += " ";
      }
    }else{
      pic += " ";
      if(n>=10){
        pic += " ";
      }      
    }

    if(i!=0){
      pic += "\n";
    }else{
      pic += "\n"+string(18,'`');
    }
  }
  cout << endl;
  cout << pic << endl;
  cout << endl;
  sleep();
  if(clear){
    system("clear");  
  }
}

vector<int> gentower(int n){
  vector<int> t = {};
  for(int i=n; i>=1; i--){
    t.push_back(i);
  }
  return t;
}