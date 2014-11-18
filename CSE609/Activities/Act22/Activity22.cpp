#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include "time.h"
#include "/usr/include/gsl/gsl_vector.h"
#include "gsl/gsl_sort_double.h"
#include "/usr/include/gsl/gsl_sort_vector_double.h"

using namespace std;

int main() {

  int input;
  srand(time(NULL));
  cout << "Enter a number: ";
  try {
    cin >> input;
    //istringstream s (input);
    //int x;
    //char c;
    //if (!(s>>x) || (s>>c)) {
    //  throw invalid_argument("You did not enter a number. Program aborted.");
    //}
  }

  catch (invalid_argument e) {
    cout << e.what() << endl;
    return 0;
  }
  int n = input;
  gsl_vector * v = gsl_vector_alloc (n);

  for (int i = 0; i < n; i++) {
    int temp = rand() % 100;
    gsl_vector_set(v,i,temp);
  }

  gsl_sort_vector(v);
  cout << endl;
  cout << "Vector contains: " << endl;
  for (int i = 0; i < n; i++) {
    cout << gsl_vector_get(v,i) << endl;
  }
  return 0;
}
