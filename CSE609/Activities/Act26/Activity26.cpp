#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

int main(int argc, char* argv[]) {
  srand(time(NULL));
  double count = 0;
  double total = 0;
  for(int i = 0; i < atoi(argv[1]); i++) {

  double x = (rand() % 10000 - 5000)/5000.0;
  double y = (rand() % 10000 - 5000)/5000.0;

  double dist = sqrt(pow(x,2) + pow(y,2));
  if (dist <=1.0) {
    count++;
  }
  total++;
  //cout << x << endl;
  //cout << y << endl;
  //cout << dist << endl;
  }
  double ratio = count/total;
  cout << "Ratio of points: " << ratio << endl;
  cout << "Approximation of pi: " << ratio*4 << endl;
  return 0;
}
