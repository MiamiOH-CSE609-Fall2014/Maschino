#include <iostream>
#include <random>


using namespace std;

int main() {

  const int n = 10; //Number of events
  const double lambda = 8.0; //rate of arrival
  const double phi = 0.2; //probability of arrival to link 1
  const int mu1 = 5;
  const int mu2 = 5;
  const int buff1 = 20;
  const int buff2 = 20;
  vector<float> time(n);
  vector<int> link(n);

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
 
  poisson_distribution<int> arrivalDistribution(1000*(1/lambda));
  binomial_distribution<int> linkDistribution(1,phi);
  for (int i=0; i<n; i++) {
    time[i] = arrivalDistribution(generator);
    time[i] = time[i]/1000;
    link[i] = linkDistribution(generator)+1;
    
    cout << endl;
    cout << "Packet " << i+1 << ":" << endl;
    cout << "Arrival rate: " << time[i] << endl;
    cout << "Link used: " << link[i] << endl;
  }

  return 0;
}
