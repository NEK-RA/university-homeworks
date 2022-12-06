// with g++ need to compile with -pthread flag: g++ -pthread shariki.cpp -o shariki
// строка 245 - количество потоков
// строка 246 - количество шариков для перебора
#include <iostream>
#include <vector>
#include <cmath>
// #include <ctime>
#include <chrono>
#include <thread>
#include <future>

using namespace std;

unsigned long long fact(int n){
  unsigned long long result = 1;
  for(int i = 1; i<=n; i++){
    result *= i;
  }
  return result;
}

int findFirst(vector<int> vect, int val, bool direct=true){
  int res = -1;
  if(direct){
    for(int i =0; i<vect.size(); i++){
      if(vect[i]==val){
        res = i;
        break;
      }
    }
  }else{
    for(int i =vect.size()-1; i>=0; i--){
      if(vect[i]==val){
        res = i;
        break;
      }
    }
  }
  return res;
}

bool unique(vector<int> v){
  int nums[10] = {1, 2, 3,4,5,6,7,8,9,10};
  bool result = true;
  for(int i=0; i<v.size(); i++){
    if(findFirst(v,nums[i]) != findFirst(v,nums[i],false)){
      result = false;
      break;
    }
  }
  return result;
}

vector<int> genset(unsigned long long num,int len){
  int nums[10] = {1, 2, 3,4,5,6,7,8,9,10};
  vector<int> res = {};
  vector<int>::iterator it;
  if(len == 1) {
    return {nums[0]};
  }
  if(num == 0){
    res.push_back(nums[0]);
  }else{
    while(num>0){
      int last = num % len;
      it = res.begin();
      res.insert(it, nums[last]);
      num = num / len;
    }
  }
  int left = len - res.size();
  if(left){
    for(int i=0; i<left; i++){
      it = res.begin();
      res.insert(it, nums[0]);
    }
  }
  return res;
}

void printv(vector<int> v){
  cout << "\t";
  for(int i=0; i < v.size(); i++){
    cout << " " << v[i];
  }

  cout << endl;
}

vector<vector<int>> partial(int n, unsigned long long start, unsigned long long end, int threadnum){
  string msg;
  vector<int> v = {};
  vector<vector<int>> res = {};
  int mod = -1;
  int counter = 0;
  for(unsigned long long i = start; i < end; i++){
    v = genset(i,n);
    //cout << "ПОТОК " << threadnum << endl;
    //printv(v);
    //cout << endl;
    if(unique(v)){
      res.push_back(v);
      //counter++;
      //cout << "ПОТОК " << threadnum << ": обнаружено " << counter << " уникальных комбинаций" << endl;
    }
    mod = (i-start) % ((end-start)/10)+1;
    if(mod == 10){
      counter = 100 * (i-start) / ((end-start));
      msg = "ПОТОК " + to_string(threadnum) + " >>> перебрано ~" + to_string(counter) + "% комбинаций";
      cout << msg << endl;
    }
  }
  return res;
}

vector<vector<int>> combos(int n){
  vector<int> v = {};
  vector<vector<int>> res = {};
  bool early = false;
  cout << "Считаем кол-во уникальных перестановок";
  unsigned long long total = fact(n);
  cout << '\t' << n << "! = " << total<<endl;
  cout << "Считаем кол-во всех перестановок";
  unsigned long long counter = 0;
  unsigned long long totalraw = pow(n,n);
  cout << '\t' << n << "^" << n << " = " << totalraw << endl;
  for(unsigned long long i = 0; i < totalraw; i++){
    //cout << "Генерируем очередную перестановку   (" << i <<" / "<< totalraw << ")" << endl;
    v = genset(i,n);
    if(unique(v)){
      res.push_back(v);
      counter++;
      //cout << endl << endl << endl;
      //cout << "Добавлено " << counter << " из " << total << " перестановок" << endl;
      //cout << endl << endl << endl;
    }
    if(i % (totalraw / 100) == 0){ // по 1% общего числа перестановок
    //if(res.size() % (total / 100) == 0){ // по 1% уникального числа перестановок
      //cout << fixed <<"Обработано ≈" << (i / (totalraw / 100)) <<"% общего количества перестановок" << endl;
      cout << fixed << "Найдено "<< res.size() << "/" << total << " ≈" << ((res.size() * 100)/total) << "% уникальных перестановок";
      if(res.size()==total){
        cout << endl << "Все уникальные перестановки найдены раньше, чем закончился перебор всех перестановок. Пропущено " << totalraw - i <<"/" << totalraw << " (" <<(totalraw-i)*100/totalraw<< "%) перестановок " << endl;
        early = true;
        break;
      }else{
        cout << '\r';
      }
    }
  }
  if(!early){
    cout << "Перебрано " << totalraw << " перестановок" << endl;
    cout << "Из них " << res.size() << " уникальных (без повторений)" << endl;
  }
  return res;
}

bool isGood(vector<int> set){
  int nums[10] = {1, 2, 3,4,5,6,7,8,9,10};
  int good = 0;
  for(int i = 0; i < set.size(); i++){
    if(set[i] == nums[i]){
      good++;
    }
  }
  if(good == 0){
    return false;
  }else{
    return true;
  }
}

unsigned long long countGood(vector<vector<int>> combs){
  unsigned long long counter = 0;
  for(unsigned long long i = 0; i < combs.size(); i++){
    if(isGood(combs[i])){
      counter++;
    }
  }
  return counter;
}

void forecast(int n, double time, int target, int threads){
  unsigned long long rawn = pow(n,n);
  double speed = rawn / time;
  
  cout << "Для " << n << " шариков процесс занял ≈" << (time/60) << " минут (" << time <<" секунд)" << endl;
  cout << "При:"<< endl;
  cout <<"- ручной генерации всех перестановок ("<< n <<"^"<< n<<"="<<rawn<<" наборов)" << endl; 
  cout <<"- ручном исключении содержащих повторы (до "<< n <<"!="<< fact(n) <<" наборов без повторений)" << endl;
  cout <<"- использовании " << threads << " поток(а,ов) (async)" << endl;
  cout << "Аналогичный процесс для " << target << " шариков займет ";
  unsigned long long rawt = pow(target,target);
  double eta = rawt / speed;
  string etastr = "";
  if(eta<=60){
    etastr += to_string(eta) + " секунд ";
  }
  if(eta <= 3600){
    etastr += to_string(eta/60) + " минут ";
  }
  if(eta <= 86400){
    etastr += to_string(eta/3600) + " часов ";
  }
  if(eta > 86400){
    etastr += to_string(eta/86400) + " дней ";
  }

  etastr += "(" + to_string(eta) + " секунд, обрабатывая ~"+to_string(lround(speed))+" наборов в секунду)";
  cout << etastr << endl << endl;
}

void doMath(int n){
  // https://ru.wikipedia.org/wiki/Беспорядок_(перестановка)
  //https://en.wikipedia.org/wiki/Derangement#Counting_derangements
  unsigned long long chaotic = 0;
  unsigned long long total = pow(n,n);
  unsigned long long factorial = fact(n);
  if(n>=1){
    chaotic = factorial;
    for(int i=1; i<=n; i++){
      chaotic += (pow(-1,i) * factorial)/fact(i);
    }
  }
  cout << "Математический метод для " << n << " шариков:" << endl;
  cout << "Всего наборов (с повторениями): " << n << "^" << n << "=" << total << endl; 
  cout << "Наборов, где каждый номер встречается единожды (без повторений): factorial("<< n << ")" << "="  << factorial <<endl;
  cout << "Хаотичных наборов (также называемых \"беспорядками\" - когда все шарики находятся на местах, не соответствующих их номеру): subfactorial("<< n << ")" << "=" << chaotic << endl;
  cout << "Уникальные наборы минус беспорядки равно количеству удовлетворяющих условию комбинаций: " << factorial << " - " << chaotic << " = " << (factorial - chaotic) << endl;
  cout << endl;
}

int main(int argc, char *argv[])
{
  // long start = time(NULL);
  // int n = 8;
  // vector<vector<int>> combs = combos(n);
  // cout << "Для "<< n <<" шариков найдено " << countGood(combs) << " случаев, когда номер хотя бы одного вынутого шарика совпадает с порядковым номером действия \"вынимания\"" << endl << endl;
  // long end = time(NULL);
  // cout << string(20,'-') << endl;
  // int sec = end - start;
  // float min = sec / 60.;
  // cout << "Процесс занял ≈" << min << " минут (" << sec <<"±1 секунд)" << endl;

  // Входные данные
  int threads = 1;
  int n = 7;
  
  chrono::time_point<std::chrono::system_clock> start = chrono::system_clock::now();
  
  vector<future<vector<vector<int>>>> tasks = {};
  unsigned long long mult = (pow(n,n) / threads);
  unsigned long long startnum = -mult, endnum = 0;
  for(int i=0; i<threads; i++){
    startnum += mult;
    endnum += mult;
    tasks.push_back(async(launch::async, partial, n,startnum,endnum,i+1));
  }
  unsigned long long goodcombs = 0;
  for(int i=0; i<threads; i++){
    goodcombs += countGood(tasks[i].get());
  }

  chrono::time_point<std::chrono::system_clock> end = chrono::system_clock::now();
  chrono::duration<double> diff = end - start;
  cout << "Для "<< n <<" шариков найдено " << goodcombs << " случаев, когда номер хотя бы одного вынутого шарика совпадает с порядковым номером действия \"вынимания\"" << endl << endl;
  cout << string(50,'-') << endl << endl;
  forecast(n,diff.count(),10,threads);
  cout << string(50,'-') << endl << endl;
  doMath(n);
  cout << string(50,'-') << endl << endl;
  doMath(10);
}