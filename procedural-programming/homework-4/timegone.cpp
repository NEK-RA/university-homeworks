#include "timegone.h"

void printFlag(){
  int w = 25;
  int h = 13;
  string e = " ";
  string f = "▦"; // ▦ |
  string s = "★"; // ✭ ★ ✪ ✫ *
  string flag[h][w];
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      if(i%2==0){
        flag[i][j] = f;
      }else{
        flag[i][j] = e;
      }
    }
  }
  for(int i=0; i < 6; i++){
    for(int j = 0; j < 8; j++){
      flag[i][j] = s;
    }
  }
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      cout << flag[i][j];
      if(i%2==0 && (i>=6 || j>=8)){
        cout << f;
      }else{
        cout << e;
      }
    }
    cout << endl;
  }
}