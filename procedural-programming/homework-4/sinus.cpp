#include "sinus.h"

void printSinusoid(){
  cout << "ГРАФИК SIN(X)" << endl;
  string plot[29][161] = {"-"};
  int centery = 14, centerx = 80;
  for(int i = 0; i < 29; i++){
    for(int j = 0; j < 161; j++){
      plot[i][j] = " ";
    }
  } 

  for(int i = 0; i < 29; i++){
    plot[i][centerx] = "|";
  }

  for(int i = 0; i < 161; i++){
    plot[centery][i] = "-";
  }

  plot[centery][centerx]="+";

  int y = 0;
  int scale = 10;
  int posx = 0, posy = 0;
  for(float x=-8; x<8; x+=0.1){
    y = round(sin(x) * (scale+4));
    // cout << x << "  " << y << endl;
    posx = centerx + x*scale;
    posy = centery + y;
    plot[posy][posx] = "*";
  }

  for(int i = 0; i < 29; i++){
    for(int j = 0; j < 161; j++){
      cout << plot[i][j];
    }
    cout << endl;
  }
}
