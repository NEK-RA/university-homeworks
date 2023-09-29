#include "task1.h"
#include <ios>
#include <string>



void cat(string filename){
  fstream file;
  if(!file.is_open()){
    file.open(filename, ios::in);
  }
  if(file.is_open()){
    string line;
    while(getline(file, line)){
      cout << line << endl;
    }
    file.close();
  }else{
    cout << "Не удалось открыть файл!" << endl;
  }
}

void mkFixedOrRandom(string filename, bool fixedNumbers = true){
  fstream file;
  if(!file.is_open()){
    file.open(filename, ios::out);
  }
  int randomN;
  if(file.is_open()){
    for(int i = 0; i < ((rand() % 50) + 10); i++){
      if(fixedNumbers){
        file << to_string(i);
      }else{
        randomN = rand() % 1000;
        randomN = rand() % 2 ? randomN : randomN*(-1);
        file << to_string(randomN);
      }
      
      if(i % ((rand() % 10)+2) == 4){
        file << endl;
      }else{
        file << " ";
      }
    }
    file.close();
  }else{
    cout << "Не удалось открыть файл!" << endl;
  }
}

void writeFile(string filename, string text, bool append = false){
  fstream file;
  if(!file.is_open()){
    ios_base::openmode om;
    if(append){
      om = ios::out | ios::app;
    }else{
      om = ios::out;
    }    
    file.open(filename, om);
  }
  if(file.is_open()){
    file << text << endl;
    file.close();
  }else{
    cout << "Не удалось открыть файл!" << endl;
  }
}

int readNthNumber(string filename, int n){
  fstream file;
  if(!file.is_open()){
    file.open(filename, ios::in);
  }
  if(file.is_open()){
    int num;
    int counter = 0;
    while(!file.eof()){
      file >> num;
      if(file.fail()){
        file.clear();
        file.ignore(1);
        continue;
      }
      counter++;
      if(counter == n){
        return num;
      }
    }
    file.close();
    cout << "Чисел в файле(" << counter << ") меньше , чем заданное N=" << n << ", поэтому возвращено число 0" << endl;
    return 0;
  }else{
    cout << "Не удалось открыть файл! Возвращено значение 0." << endl;
    return 0;
  }
}

int countNumbers(string filename){
  fstream file;
  int counter = 0;
  if(!file.is_open()){
    file.open(filename, ios::in);
  }
  if(file.is_open()){
    int num;
    while(!file.eof()){
      file >> num;
      if(file.fail()){
        file.clear();
        file.ignore(1);
        continue;
      }
      counter++;
    }
    file.close();
  }else{
    cout << "Не удалось открыть файл! Возвращено значение 0." << endl;
  }
  return counter;
}

double averageNegative(string filename){
  double sum = 0;
  double num;

  fstream file;
  int counter = 0;
  if(!file.is_open()){
    file.open(filename, ios::in);
  }
  if(file.is_open()){
    while(!file.eof()){
      file >> num;
      if(file.fail()){
        file.clear();
        file.ignore(1);
        continue;
      }
      if(num < 0){
        counter++;
        sum += num;
      }
    }
    file.close();
  }else{
    cout << "Не удалось открыть для чтения файл " << filename << endl;
  }
  num = sum/counter;
  cout << "Среднее арифметическое отрицательных чисел: " << num << endl;
  return num;
}

string variantSpecific(string filename){
  // Создать новый файл из значений исходного, увеличив его на среднее арифметическое всех отрицательных чисел исходного файла.
  fstream in, out;
  double num, avneg;
  avneg = averageNegative(filename);
  if(!in.is_open()){
    in.open(filename, ios::in);
  }
  filename = "custom-" + filename;
  if(!out.is_open()){
    out.open(filename, ios::out);
  }
  if(in.is_open() && out.is_open()){
    while(!in.eof()){
      in >> num;
      if(in.fail()){
        in.clear();
        in.ignore(1);
        continue;
      }
      num += avneg;
      out << num << " ";
    }
    in.close();
    out.close();
    return filename;
  }else{
    if(in.is_open()){
      in.close();
    }
    if(out.is_open()){
      out.close();
    }
    cout << "Не удалось открыть для чтения файл " << filename << endl;
  }
  return "";
}

/*
  1. Разработать программу, управления текстовым файлом.
  1.1. Реализация ввода-вывода на основе файловых потоков С++: ofstream, ifstrim.

++ 1.2. Имя физического файла вводится пользователем и передается в функции обработки через параметр.
  1.3. Разработать функции для выполнения операций над текстовым файлом:
++  1.3.1. создание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке; файл может быть образцовым или введен пользователем;

++ 1.3.2. вывод содержимого текстового файла;
++ 1.3.3. добавление новой строки в конец файла;
++ 1.3.4. прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение;
++ 1.3.5. определить количество чисел в файле.
+ 1.3.6. Создать новый файл из значений исходного, увеличив его на среднее арифметическое всех отрицательных чисел исходного файла.

  1.4. Разработать приложение и выполнить тестирование всех функций. Приложение должно содержать диалоговый интерфейс на основе текстового меню.
  1.5. Приложение должно осуществлять контроль открытия и существования файла в основной программе перед вызовом функций. Перед закрытием файла, проверять отсутствие ошибок ввода и вывода (метод good).
*/

void task1(){
  string filename;
  string line;
  string text;
  int choice = -1;
  int n = 0;
  string menu = "1. Вывести содержимое файла\n"
  "2. Создать файл со фиксированными значениями\n"
  "3. Создать файл со случайными значениями\n"
  "4. Заполнить файл вручную\n"
  "5. Добавить новую строку в конец файла\n"
  "6. Считать N-е число из файла\n"
  "7. Посчитать кол-во чисел в файле\n"
  "8. Создать файл на базе исходного: Увеличить все числа\n\t"
        "на среднее арифметическое отрицательных чисел в исходном файле\n"
  "0. Вернуться назад\n"
  "Ваш выбор: ";
  while(choice != 0){
    cout << endl << menu;
    cin >> choice;
    if(cin.fail()){
      cin.clear();
      cin.ignore(10000, '\n');
      continue;
    }
    line = "";
    text = "";
    switch(choice){
      case 1:
        cout << "Укажите имя файла: ";
        cin >> filename;
        cat(filename);
        break;
      
      case 2:
        cout << "Будет создан файл из 100 чисел от 0 до 99, по 5 через пробел чисел на строке" << endl;
        cout << "Укажите имя файла: ";
        cin >> filename;
        mkFixedOrRandom(filename);
        break;
      
      case 3:
        cout << "Будет создан файл из 100 случайных чисел, по 5 через пробел чисел на строке" << endl;
        cout << "Укажите имя файла: ";
        cin >> filename;
        mkFixedOrRandom(filename, false);
        break;

      case 4:
        cout << "Укажите имя создаваемого файла: ";
        cin >> filename;
        cout << "Введите на новой строке слово \"END\" для завершения ввода." << endl;
        while(getline(cin, line)){
          if(line == "END"){
            break;
          }
          text += line + '\n';
        }
        writeFile(filename, text);
        break;

      case 5:
        cout << "Укажите имя дополняемого файла: ";
        cin >> filename;
        cin.clear();
        cin.ignore(10000, '\n');
        getline(cin, line);
        writeFile(filename, line, true);
        break;
      
      case 6:
        cout << "Укажите имя обрабатываемого файла: ";
        cin >> filename;
        cout << "Укажите порядковый номер искомого числа: ";
        cin >> n;
        n = readNthNumber(filename, n);
        cout << "Итог: " << n << endl;
        break;
      
      case 7:
        cout << "Укажите имя обрабатываемого файла: ";
        cin >> filename;
        n = countNumbers(filename);
        cout << "В " << filename << " содержится " << n << " чисел" << endl;
        break;
      
      case 8:
        cout << "Укажите имя обрабатываемого файла: ";
        cin >> filename;
        filename = variantSpecific(filename);
        cout << "Результат записан в файл " << filename << endl;
        break;
      
      default:
        cout << string(50,'-') << endl;
    }
  }
}
