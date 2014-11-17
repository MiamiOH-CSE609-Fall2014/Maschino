#include "exp.h"
#include "fact.h"
#include <iostream>

using namespace std;

int base;
int exponent;
int factorial;

int main() {
  cin >> base;
  cin >> exponent;
  cin >> factorial;

  cout << exp(base,exponent) << endl;
  cout << fact(factorial) << endl;
  return 0;
}
