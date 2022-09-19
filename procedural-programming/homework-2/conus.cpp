#include "conus.h"

bool calcConus() {
  float R = 0, r = 0, h = 0;
  cout << "Укажите параметры усеченного конуса:" << endl;
  cout << "Внимание: любые отрицательные значения будут взяты по модулю, по причине того, что любой объект не может иметь отрицательных размеров." << endl;
  cout << "Радиус нижнего основания (R): ";
  if (cin >> R) {
    if(R<0){
      R = abs(R);
    }
    cout << "Радиус верхнего основания (r): ";
    if (cin >> r) {
      if(r<0){
        r = abs(r);
      }
      cout << "Высота конуса (h): ";
      if (cin >> h) {
        if(h<0){
          h = abs(h);
        }
        // Вычисление образующей
        float small = R - r;
        float l = sqrt(h * h + small * small);
        // Вычисление объема
        float v = (1. / 3) * M_PI * h * (R * R + R * r + r * r);
        cout << "Объем: " << v << endl;
        // Вычисление площади
        float s = M_PI * (R * R + (R + r) * l + r * r);
        cout << "Полная поверхность: " << s << endl;
        return true;
      } else {
        cout << "Ошибка ввода: необходимо вводить только числа.  Программа "
                "будет перезапущена."
             << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
      }
    } else {
      cout << "Ошибка ввода: необходимо вводить только числа.  Программа будет "
              "перезапущена."
           << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      return false;
    }
  } else {
    cout << "Ошибка ввода: необходимо вводить только числа.  Программа будет "
            "перезапущена."
         << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    return false;
  }
}