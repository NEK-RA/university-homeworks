#include "letters.h"

bool isLetter(char ch) {
  int num = ch;
  int startSmall = 'a', endSmall = 'z';
  int startBig = 'A', endBig = 'Z';
  if ((num >= startSmall && num <= endSmall) ||
      (num >= startBig && num <= endBig)) {
    return true;
  }
  return false;
}

bool sortLetters() {
  string sequence = "", input = "";
  cout << "Введите последовательность букв:" << endl;
  while (sequence.size() < 30) {
    getline(cin, input);
    int added = 0;
    for (int i = 0; i < input.size(); i++) {
      if (isLetter(input[i])) {
        sequence += input[i];
        added++;
      }
    }
    if (added != input.size()) {
      cout << "Символы, не являющиеся английскими буквами, были отброшены "
              "(проигнорированы)"
           << endl;
    }
    if (sequence.size() < 30) {
      cout << "Осталось ввести еще " << 30 - sequence.size() << " символов"
           << endl;
    }
  }
  cout << "Результат (" << sequence.size() << " символов): " << sequence
       << endl;
  bool sorted = false;
  //int counter = 1;
  while(!sorted){
    sorted = true;
    for (int i = 0; i < sequence.size() - 1; i++) {
      char current = sequence[i];
      char next = sequence[i+1];
      if(next < current){
        sorted = false;
        char tmp = next;
        sequence[i+1] = sequence[i];
        sequence[i] = tmp;
      }
    }
    //cout << "Пройдена итерация " << counter << endl;
    //cout << "Текущий результат: " << sequence << endl << endl;
    //counter++;
  }
  cout << "Отсортированная строка: " << endl << sequence << endl;
  return true;
}