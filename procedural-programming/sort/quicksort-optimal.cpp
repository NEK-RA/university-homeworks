#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
using namespace std;

void swap(int &a, int &b){
  int tmp = a;
  a = b;
  b = tmp;
}

// вывод вектора
void printVector(vector<int> &a, int point=-1, string comment = ""){
  // напечатать комментарий если есть
  if(comment != ""){
    cout << comment << endl;
  }
  // вывести сам вектор через пробел
  // выводится с шириной поля для каждого числа в 5 символов
  for(int i=0; i<a.size();i++){
    cout << setw(5) << a[i] << " ";
  }
  cout << endl;
  // Если надо указать на какой то элемент вектора
  // то под ним делается строка содержащая какой либо символ
  // который был принят для указания (^^^^^ в данном случае)
  if((point != -1) && (point >= 0) && (point <= a.size()-1) && (a.size() <= 15)){
    string pointline = "";
    for(int i=0; i<a.size(); i++){
      if(i!=point){
        pointline += string(6,' ');
      }else{
        pointline += string(5,'^');
        // pointline += "T"; // unicode - ▲, ascii - !,^,|,T 
      }
    }
    // вывод строки с указателем
    cout << pointline << endl;
  }
}

// Разбиение Хоара
int partition(vector<int> &a, int low, int high, bool detailed){
  // Опорным элементом берется серединный для текущих границ
  int pivot = a[(low+high)/2];
  int i = low;
  int j = high;
  if(detailed){
    cout << "Значение элемента посередине (между элементами с индексами low=" << low << " и high= " << high << "): " << pivot << endl;
    cout << "Движемся с обоих сторон, слева от i=" << i <<", справа от j=" << j << endl; 
  }
  while(true){
    // Сначала движемся с левой стороны, до тех пор
    // пока не попадется элемент, значение которого
    // больше или равно значению серединного
    if(detailed){
      cout << endl << endl << "Движемся слева с индекса low=" << i << endl << endl;
    }
    while(a[i] < pivot){
      if(detailed){
        printVector(a,i);
        cout << "a[" << i << "]=" << a[i] << " все еще меньше серединного ("<< pivot << "), идем дальше" << endl << endl;
      }
      i++;
    }
    // Аналогично движемся с правой стороны
    if(detailed){
      cout << "Нашелся a[" << i << "]=" << a[i] << " значение которого равно значению серединного("<< pivot << "), или превышает его" << endl << endl;
      cout << endl << endl << "Теперь движемся справа с индекса high=" << j << endl << endl;
    }
    while(a[j] > pivot){
      if(detailed){
        printVector(a,j);
        cout << "a[" << j << "]= " << a[j] << " все еще больше серединного(" << pivot << "), идем дальше" << endl << endl;
      }
      j--;
    }
    if(detailed){
      cout << "Нашелся a[" << j << "]=" << a[j] << " значение которого равно значению серединного("<< pivot << "), или меньше него" << endl << endl;
    }
    
    // Если индексы пересеклись, значит больше менять 
    // в текущем разбиении нечего, и возвращаем j 
    // как индекс элемента, который разделяет 2 участка массива

    if(detailed){
      cout << "Проверяем, не пересеклись ли индексы (i>=j): " << i << ">=" << j << "? ";
    }
    if(i >= j){
      if(detailed){
        cout << "Да, пересеклись ==> возвращаем точку разбиения массива как j=" << j << endl << endl << string(30,'-') << endl << endl;
      }
      return j;
    }

    // Если же индексы не пересеклись, то обнаруженные элементы
    // не соответствующие условию, т.е. находящиеся не в той
    // части массива относительно серединного элемента
    // меняются местами

    if(detailed){
      cout << "Нет, не пересеклись ==> меняем значениями a[" << i << "]=" << a[i] << " и a[" << j << "]=" << a[j] << ", после чего увеличиваем i и уменьшаем j" << endl;
      printVector(a,i,"a[i] для замены: ");
      printVector(a,j,"a[j] для замены: ");
    }
    
    swap(a[i++],a[j--]);

    if(detailed){
      printVector(a,-1,"Итог: ");
    }
  }
}

// Функция quicksort принимает вектор, а так же границы сортируемого участка
void quicksort(vector<int> &a, int low, int high, bool detailed){
  // Сортировка идет рекурсивно и заканчивается
  // когда границы сортируемого участка сравняются
  if(low < high){
    // Выбирается опорный элемент
    // Фактически, сама сортировка происходит в функции
    // разбиения массива на части
    int p = partition(a, low, high, detailed);
    // Рекурсивно сортируется участок до опорного
    quicksort(a,low,p,detailed);
    // Рекурсивно сортируется участок после опорного
    quicksort(a,p+1,high,detailed);
  }
}

int main() {
  // https://ru.wikipedia.org/wiki/Быстрая_сортировка#Разбиение_Хоара
  long timestamp = chrono::duration_cast<std::chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
  srand(timestamp);
  cout << "Время запуска: " << timestamp << endl;
  cout << "Проверить можно:" << endl
    << "> https://ya.ru/?q=" << timestamp << endl
    << "> https://ddg.gg/?q=timestamp+" << timestamp << endl
    << "> Указав время запуска на https://timestamp.online/" << endl << endl;
  
  int len = 2000000;
  int mod = 100000;
  bool detailed = false;
  cout << "Создадим массив A из " << len << " элементов со значениями от 0 до " << mod << ":" << endl;
  // vector<int> a = {3,7,8,5,2,1,9,5,4}; //wikipedia example
  vector<int> a;
  for(long unsigned int i=0; i < len; i++){
    a.push_back(rand() % mod);
  }
  printVector(a,-1,"До сортировки:");
  cout << endl << endl << string(30,'-') << endl << endl;
  chrono::time_point<chrono::system_clock> sortstart = chrono::system_clock::now();
  quicksort(a, 0, a.size()-1, detailed);
  chrono::time_point<chrono::system_clock> sortfinish = chrono::system_clock::now();
  chrono::duration<double> diff = sortfinish - sortstart;

  printVector(a,-1,"После сортировки:");
  cout << "Сортировка заняла: " << fixed << diff.count() << " секунд(ы)" << endl;
  if(detailed){
     cout << "Причем большая часть этого времени потрачена только на вывод хода работы программы в консоль" << endl;
  }

}

// Для сравнения производительности оптимальной и неоптимальной реализации
// данная (оптимальная реализация) для тех же входных данных требует и выполняется

// Для вектора типа int из 2 млн элементов
// (2 000 000 * 4 ~ 7.6мб) задействовано порядка 11мб оперативной памяти
// Отбросив все строки и прочие нюансы используемых структур
// получаем фактическое отсутствие дублирования в памяти
// А так же большую скорость выполнения: всего чуть меньше 2 секунд
// Что почти в 13 раз быстрее при условии использования
// той же структуры vector, что и в неоптимальной реализации
