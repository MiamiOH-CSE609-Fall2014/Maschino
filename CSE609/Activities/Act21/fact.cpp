#include <iostream>

using namespace std;

int fact(int val) {
  int temp;
  if (val <= 1) {
    return 1;
  }
  else {
    temp = val*fact(val-1);
    return temp;
  }
}
