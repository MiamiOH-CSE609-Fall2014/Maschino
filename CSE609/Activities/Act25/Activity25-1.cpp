#include <iostream>
#include <climits>
#include <cfloat>

using namespace std;

int main() {
  
  int prevInt = 0;
  int i = 0;
  while (0 <= i) {
    prevInt = i;
    i++;
  }
  cout << "Calculated largest integer: " << prevInt << endl;
  cout << "Pre-made function for largest integer: " << INT_MAX << endl;

  long prevLongInt = 0;
  long i_long = 0;
  while (0 <= i_long) {
    prevLongInt = i_long;
    i_long++;
  }
  cout << "Calculated largest long integer: " << prevLongInt << endl;
  cout << "Pre-made function for largest long integer: " << LONG_MAX << endl;

  short prevShortInt = 0;
  short i_short = 0;
  while (0 <= i_short) {
    prevShortInt = i_short;
    i_short++;
  }
  cout << "Calculated largest short integer: " << prevShortInt << endl;
  cout << "Pre-made function for largest short integer: " << SHRT_MAX << endl;

  float prevFloat = 0;
  float i_float = 1;
  while (0 < i_float) {
    prevFloat = i_float;
    i_float = i_float/2;
  }
  cout << "Calculated smallest float: " << prevFloat << endl;
  cout << "Pre-made function for smallest float: " << FLT_MIN << endl;

  double prevDouble = 0;
  double i_double = 1;
  while (0 < i_double) {
    prevDouble = i_double;
    i_double = i_double/2;
  }
  cout << "Calculated smallest double: " << prevDouble << endl;
  cout << "Pre-made function for smallest double: " << DBL_MIN << endl;


  return 0;
}
