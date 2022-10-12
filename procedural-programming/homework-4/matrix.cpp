#include "matrix.h"

void multiplyMatrix() {
  int a[3][4] = {
    {5,2,0,10},
    {3,5,2,5},
    {20,0,0,0}
  }; // первая матрица, строки = продавцы, столбцы = товары

  float b[4][2] = {
    {1.2, 0.5},
    {2.8, 0.4},
    {5, 1},
    {2, 1.5}
  }; // вторая матрица, строки = товары, столбцы = (стоимость, комиссионные)
  /*
  Перемножение возможно только когда кол-во столбцов первой матрицы
  совпадают с количеством строк второй матрицы. Результирующая матрица
  будет иметь размеры:
  - кол-во строк из первой матрицы
  - кол-во столбцов из второй матрицы
  
  Пример:
  A(3x4) * B(4x2) = C(3x2)

  Пример:
  / a,b,c,d \    / m,n \    / (a*m+b*o+c*q+d*s) (a*n+b*p+c*r+d*t) \
  | e,f,g,h | *  | o,p | =  | (e*m+f*o+g*q+h*s) (e*n+f*p+g*r+h*t) |
  \ i,j,k,l /    | q,r |    \ (i*m+j*o+k*q+l*s) (i*n+j*p+k*r+l*t) /
                 \ s,t /
  */
  /* Перемножено вручную
  float target[3][2] = {
    {
      a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] + a[0][3]*b[3][0],
      a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1] + a[0][3]*b[3][1]
    },
    {
      a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0] + a[1][3]*b[3][0],
      a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1] + a[1][3]*b[3][1]
    },
    {
      a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0] + a[2][3]*b[3][0],
      a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1] + a[2][3]*b[3][1]
    }
  };
  */
  
  // внешний цикл - строки первой матрицы
  // вложенный цикл - столбцы второй матрицы
  // внутренний цикл - строки второй матрицы
  float loop[3][2] = {0};
  float sum = 0;
  for(int i=0;i<3;i++){
    for(int j=0;j<2;j++){
      sum = 0;
      for(int k=0;k<4;k++){
        sum += a[i][k] * b[k][j];
      }
      // cout << sum << " ";
      loop[i][j] = sum;
    }
    // cout << endl;
  }
  cout << "Итог перемножения матриц: " << endl;
  cout << "Прод.\tЦена\t\tКомис." << endl;
  for(int i=0; i<3;i++){
    cout << "Пр. " << (i+1) << "\t";
    for(int j=0; j<2;j++){
      cout << fixed << loop[i][j] << "\t";
    }
    cout << endl;
  }
  cout << "-----------------------------" << endl;
  
  int max = 0, min = 0;
	for(int i=1; i < 3; i++){
		if(loop[i][0] > loop[max][0]){
			max = i;
		}
		if(loop[i][0] < loop[min][0]){
			min = i;
		}
	}
	cout << "1. Больше всего денег выручил продавец " << (max+1) << endl;
	cout << "   Меньше всего денег выручил продавец " << (min+1) << endl;
	cout << endl;

	max = 0;
	min = 0;
	for(int i=1; i < 3; i++){
		if(loop[i][1] > loop[max][1]){
			max = i;
		}
		if(loop[i][1] < loop[min][1]){
			min = i;
		}
	}
	cout << "2. Наибольшие комиссионные получил продавец " << (max+1) << endl;
	cout << "   Наименьшие комиссионные получил продавец " << (min+1) << endl;
	cout << endl;

	float earned = 0, comission = 0;

	for(int i=0; i<3; i++){
    earned += loop[i][0];
  }

  for(int i=0; i<3; i++){
    comission += loop[i][1];
  }

	cout << "3. Всего выручено: " <<  earned << endl << endl;
  
  cout << "4. Всего комиссионных получили продавцы: " <<  comission << endl << endl;

  cout << "5. Общая сумма денег, прошедших через руки продавцов: " <<  (earned + comission) << endl;
}
