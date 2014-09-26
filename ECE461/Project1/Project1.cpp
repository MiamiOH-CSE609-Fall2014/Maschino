#include <iostream>
#include <random>


using namespace std;

int main() {

  const int n = 1000; //Number of events
  const double lambda = 8.0; //rate of arrival
  const double phi = 0.2; //probability of arrival to link 1
  const double mu1 = 5.0;
  const double mu2 = 5.0;
  const int buff1 = 5;
  const int buff2 = 20;

  //  cout.precision(4);

  vector<float> time(n);
<<<<<<< HEAD
  //  vector<int> link(n); //0 = link 1, 1 = link 2

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  poisson_distribution<int> distribution(1000*(1/lambda));
  //uniform_distribution<int> linkDistribution(.2);

  for (int i=0; i<n; i++) {
    time[i] = distribution(generator);
    time[i] = time[i]/1000;   
  }
  /*
  for (int i=0; i<n; i++) {
    link[i] = 1;//linkDistribution(linkGenerator);
  }

  /*for (int i=0; i<n; i++) {
     cout << "Arrival time: " << time[i] << endl;
     cout << "Link used: " << link[i] << endl;
     }*/
=======
  vector<int> link(n);
  vector<float> service(n);

  vector<float> arrivalEventList(n);
  vector<float> departureEventList(n);

  float startTime;
  float interarrivalTime;
  double serviceTime;

  int count1 = 0;
  int count2 = 0;

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
 
  poisson_distribution<int> arrivalDistribution(1000*(1/lambda));
  binomial_distribution<int> linkDistribution(1,phi);
  exponential_distribution<double> serviceLink1Distribution(mu1);
  exponential_distribution<double> serviceLink2Distribution(mu2);
  
  time[0] = arrivalDistribution(generator);
  time[0] = time[0]/1000;
  interarrivalTime = 0;
  startTime = time[0] + interarrivalTime;
  link[0] = 1;//linkDistribution(1,phi) + 1;
  
  if (link[0] == 1) {
    serviceTime = serviceLink1Distribution(generator);
  }
  if (link[0] == 2) {
    serviceTime = serviceLink2Distribution(generator);
  }

  arrivalEventList[0] = startTime;
  departureEventList[0] = startTime + serviceTime;

  cout << "Packet\tArrival Time\tService Time\tDeparture Time\tLink" << endl;
  cout << 1 << "\t" << arrivalEventList[0] << "\t\t" << serviceTime << "\t\t" << departureEventList[0] << "\t\t" << link[0] << endl;

  for (int i=1; i<n; i++) {

    time[i] = arrivalDistribution(generator);
    time[i] = time[i]/1000;
    interarrivalTime = time[i];
    startTime = startTime + interarrivalTime;
>>>>>>> 6a3d9c95c2a9a513e1d05ea72aa55a8d3cf831b5

    link[i] = 1;//linkDistribution(generator)+1;
    
   if (link[i] == 1) {
      serviceTime = serviceLink1Distribution(generator);
   }
   if (link[i] == 2) {
      serviceTime = serviceLink2Distribution(generator);
    }
    
   arrivalEventList[i] = startTime;
   //   departureEventList[i] = arrivalEventList[i] + serviceTime;
    
      //Is the new packet arriving before the previous packet has left service?
   if (arrivalEventList[i] <= departureEventList[i-1] ) {
     count1 = 0;
     for (int j = i; 0 < j; j--) {
       if (arrivalEventList[i] <= departureEventList[j-1]) {
	 count1++;
       }
       if (count1 > buff1) {
	 departureEventList[i] = -1;
       }
       else {
	 departureEventList[i] = departureEventList[i-1] + serviceTime;
       }
     }
   }
    
   //Is the new packet arriving after the previous packet has left service?
   if((arrivalEventList[i] > departureEventList[i-1]) && (departureEventList[i-1]!=0) ) {
     departureEventList[i] = arrivalEventList[i] + serviceTime;
   }
   
   cout << i+1 << "\t" << arrivalEventList[i] << "\t\t" << serviceTime << "\t\t";
   if (departureEventList[i] == -1) {
     cout << "drop";
   }
   else {
     cout << departureEventList[i];
   }

   cout << "\t\t" << link[i] << "\t";

   /* if (count1 >  buff1) {
     cout << "drop" << endl;
     }*/
   // else {
     cout << count1 << endl;
     // }
  }
  return 0;
}
