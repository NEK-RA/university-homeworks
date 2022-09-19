#include "tabs.h"

bool tabFunc(){
  float y;
  for(float x = -4; x < 4; x=x+0.5){
    if(x-1==0){
      cout << "x=" << x << " ... y не имеет значения при данном x" << endl << endl;
      continue;
    }else{
      y = (x*x- 2*x + 2) / (x - 1);
      cout << "x=" << x << " ... y=" << y << endl << endl;
    }
  }
  return true;
}