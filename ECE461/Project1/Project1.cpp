#include <iostream>
#include <random>


using namespace std;

int main() {

  const int n = 10; //Number of events
  const double lambda = 8.0; //rate of arrival
  const int mu1 = 5;
  const int mu2 = 5;
  const int buff1 = 20;
  const int buff2 = 20;
  vector<float> time(n);

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  poisson_distribution<int> distribution(1000*(1/lambda));

  for (int i=0; i<n; i++) {
    time[i] = distribution(generator);
    time[i] = time[i]/1000;
    cout << time[i] << endl;
  }

  return 0;
}
