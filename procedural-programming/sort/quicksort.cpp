#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <cstdlib>
using namespace std;

// Функция для отображения элементов вектора через пробел
void printVector(vector<int> v){
  for(long unsigned int i=0;i<v.size();i++){
    cout << v[i] << " ";
  }
  cout << endl;
}

// Функция сортировки, принимает вектор в качестве сортируемой структуры
// аргумент verbose необходим чтобы показать сообщения о процессе сортировки
// которые будут не упорядочены, т.к. алгоритм работает рекурсивно
// аргумент level сделан только для сообщений о процессе сортировки
vector<int> sort(vector<int> array, bool verbose, int level=0){
  // Сообщения о процессе выводятся по принципу: если verbose имеет значение true
  // то текст будет выведен, а так же все рекурсивные вызовы получает verbose=true
  if(verbose){
    cout << "Уровень " << level << ": разбиение на группы начинается" << endl;
  }
  // Если массив состоит из одного элемента, либо вообще пуст - сортировать тут нечего
  // Он будет возвращен как есть.
  if(array.size() < 2){
    if(verbose) {
        cout << "Всего один элемент, возвращается как есть" << endl;
    }
    return array;
  }
  // В ином случае пойдет разделение на левую и правую части массива
  vector<int> left = {};
  vector<int> right = {};
  // Для разделения берется т.н. опорный элемент, причем известно несколько способов его взять
  // в данном случае берется элемент из середины массива
  int mid = array.size()/2;
  bool midskip = true;
    if(verbose) {
      cout << "Средний (по очереди) элемент в массиве имеет значение: " << array[mid] << endl;
    }
  // Как только опорный элемент определен, происходит само разбиение на части 
  for(long unsigned int i=0; i<array.size(); i++){
    if(array[i]==array[mid]){
      // Необходимо проверять встречался ли уже элемент эквивалентный серединному
      if(midskip){
        // Если встретился единожды, пропускаем его, т.к. серединный элемент и так будет добавлен в последствии
        midskip = false;
        continue;
      }else{
        // Если серединный элемент встречается уже не в первый раз, то его необходимо добавить в любую часть(левую или правую)
        left.push_back(array[i]);
      }
      // Это делается потому, что если при проверке использовать для одной из частей нестрогое равенство
      // то в зависимости от содержимого массива может случиться бесконечный цикл:
      // например серединный элемент оказался максимальным, а эквивалентные ему ложатся в левую часть
      // тогда каждый раз все элементы массива будут попадать в левую часть и каждая последующая
      // сортировка этой части будет приводить к тому же результату
    }else if(array[i]<array[mid]){
        if(verbose) {
          cout << array[i] << " меньше чем " << array[mid] << " поэтому идет в левый список" << endl;
        }
      left.push_back(array[i]);
    }else if(array[i]>array[mid]){
        if(verbose) {
          cout << array[i] << " больше чем " << array[mid] << " поэтому идет в правый список" << endl;
        }
      right.push_back(array[i]);
    }
  }
  // Полученные в итоге левая и правая части массива так же отправляются на сортировку
  // по тому же принципу
  if(verbose) {
    cout << "Уровень " << level << ": разбиение на группы завершено" << endl;
    cout << "Левая часть: ";
    printVector(left);
    cout << "Середина: " << array[mid] << endl;
    cout << "Правая часть: ";
    printVector(right);
    cout << endl << endl;
  }
  left = sort(left,verbose,level+1);
  right = sort(right,verbose,level+1);
  // Так происходит до тех пор, пока левая и правая части не будут состоять из 0-1 элемента
  if(verbose){
    cout << "На уровне " << level << " левая и правая части отсортированы" << endl;
    cout << "Левая часть: ";
    printVector(left);
    cout << "Середина: " << array[mid] << endl;
    cout << "Правая часть: ";
    printVector(right);
    cout << endl << endl;
  }
  // Как только такое состояние будет достигнуто в рекурсии, начинает складываться результат
  // Создаем результирующий массив
  vector<int> result = {};
  // Добавляем в его начало отсортированную правую часть
  vector<int>::iterator it = result.begin();
  result.insert(it,right.begin(),right.end());
  // Затем добавляем в начало серединный элемент
  it = result.begin();
  result.insert(it,array[mid]);
  // Наконец добавляем в начало левую часть
  it = result.begin();
  result.insert(it,left.begin(),left.end());
    if(verbose) {
      cout << "Текущий результат: ";
      printVector(result);
    }
  // Итак, с самых нижних уровней рекурсии начинают возвращаться отсортированные фрагменты
  // Пояснение: пусть на нижний уровень поступил фрагмент [5, 3]
  // Длинна массива 2, 2/2=1 - индекс "среднего" элемента, его значение в данном случае 3
  // 5 > 3 - 5 попадает в правую часть
  // 3 как средний элемент, встретившийся единожды, рассматривается отдельно
  // больше элементов нет, поэтому левая часть пустая. Составляем результат:
  // [] + [3] + [5] => [3,5] - отсортированный фрагмент 
  return result;
}

int main() {
  system("clear");
  /*
  Функция rand требует некоего значения для генерации чисел,
  от которого она будет отталкиваться.
  Если такого значения нет, используется 0.
  При каждом запуске генерируемые случайные числа будут такими же,
  как и в предыдущие запуски.

  Любое, указанное вручную, значение будет иметь тот же эффект,
  что и указание нуля. Поэтому принято использовать самое непостоянное,
  что есть в системе - время.

  Во всех современных системах отсчет времени идет в секундах от
  1 января 1970 года. Это т.н. Unix-эпоха, детали в Wikipedia:
  https://ru.wikipedia.org/wiki/Unix-время

  Итого: каждый запуск происходит в разный момент времени
  т.е. rand() при каждом запуске программы будет отталкиваться
  от разного значения 
  */
  long timestamp = time(NULL);
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
  vector<int> a;
  for(long unsigned int i=0; i < len; i++){
    a.push_back(rand() % mod);
  }
  cout << "Исходный массив: " << endl;
  printVector(a);
  cout << endl << endl;
  long begin = time(NULL);
  cout << "Время начала: " << begin << endl;
  vector<int> sorted = sort(a,detailed);
  timestamp = time(NULL);
  cout << "Время завершения: " << timestamp << endl;
  cout << "Результат сортировки: " << endl;
  printVector(sorted);
  cout << endl << endl;
  cout << "Сортировка заняла: " << timestamp << " - " << begin << " = менее " << (timestamp - begin + 1) << " секунд(ы)" << endl;
  if(detailed){
    cout << "Причем большая часть этого времени потрачена только на вывод хода работы программы в консоль" << endl;
  }

  // Примечание: представленная реализация определенно является неоптимальной
  // Пояснение: Данная реализация жертвует производительностью ради простоты
  // В частности, на каждом уровне вместо взаимодействия с массивом напрямую
  // создаются новые массивы, являющиеся фрагментами исходного массива
  // На первом уровне рекурсии оба фрагмента по итогу дублируют исходный массив
  // На второй уровень передается часть, которая в последствии тоже продублируется
  // и так далее до самого конца. С нижнего уровня рекурсии по левой части
  // потом процесс перейдет на правую часть, где вновь начнется достаточно сильное
  // дублирование данных. В этот момент часть дублированной памяти исчезнет,
  // т.к. останется только отсортированная левая часть
  
  // Для иллюстрации этого нюанса приведены некоторые тестовые данные:
  // Так, на моем устройстве программа сортировки вектора типа int из 2 млн. элементов
  // (2 000 000 * 4 байта ~ 7.63мб) в процессе работы заняла порядка 80мб оперативной памяти
  // Отбросив все константы и нюансы используемых структур, получаем
  // что с учетом дублирования данных возникает практически десятикратное дублирование
  // Затраты времени при этом составили порядка 27 секунд

  // Источники: 
  // https://ru.wikipedia.org/wiki/Быстрая_сортировка
  // https://thecode.media/qsort/
}
