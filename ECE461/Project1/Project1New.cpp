#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

int main() {

	const int n = 5000; //Number of events
	const double lambda = 8.0; //rate of arrival
	const double phi = 0.2; //probability of arrival to link 1
	const double mu1 = 5.0;
	const double mu2 = 5.0;

	vector<float> time(n);
	vector<int> link(n);
	vector<float> service(n);
	vector<float> arrivalEventList(n);
	vector<float> departureEventList(n);
	vector<int> count(2);
	vector<int> buffer(2);

	float startTime;
	float interarrivalTime;
	double serviceTime;

	count[0] = 0;
	count[1] = 0;
	buffer[0] = 5;
	buffer[1] = 5;

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
	link[0] = 0;//linkDistribution(1,phi);
  
	if (link[0] == 0) {
		serviceTime = serviceLink1Distribution(generator);
	}
	if (link[0] == 1) {
		serviceTime = serviceLink2Distribution(generator);
	}

	arrivalEventList[0] = startTime;
	departureEventList[0] = startTime + serviceTime;

	cout << left << setw(15) << "Packet" <<
		setw(20) << "Arrival Time" <<
			setw(10) << "Link" << 
				setw(20) << "Service Time" << 
					setw(20) << "Departure Time" <<
						setw(10) << "Queue 1" <<
							setw(10) << "Queue 2" << endl;
  
	cout << left << setw(15) << 1 <<
		setw(20) << arrivalEventList[0] <<
			setw(10) << link[0]+1 <<
				setw(20) << serviceTime <<
					setw(20) << departureEventList[0] <<
						setw(10) << 0 <<
							setw(10) << 0 << endl;

	for (int i=1; i<n; i++) {

		//Generate interarrival time
		time[i] = arrivalDistribution(generator);
		time[i] = time[i]/1000;
		interarrivalTime = time[i];
		
		
		startTime = startTime + interarrivalTime;

		link[i] = 0;//linkDistribution(generator);
    
		if (link[i] == 0) {
			serviceTime = serviceLink1Distribution(generator);
		}
		if (link[i] == 1) {
			serviceTime = serviceLink2Distribution(generator);
		}
    
		arrivalEventList[i] = startTime;
		
		count[link[i]] = 0;
		for (int j = 0; j < i; j++) {
			if (count[link[i]]>=buffer[link[i]]) {
				departureEventList[i] = -1;
			}
			if (departureEventList[i-1]==-1 && departureEventList[i]!=-1) {
				if (departureEventList[j]!=-1) {
					departureEventList[i] = departureEventList[j] + serviceTime;
				}
				if (arrivalEventList[i] < departureEventList[i-j-1]) {
					count[link[i]]++;
				}
			}
			else if ((count[link[i]] < buffer[link[i]])) {
				if (arrivalEventList[i] < departureEventList[i-j-1]) {
					count[link[i]]++;
					departureEventList[i] = departureEventList[i-1] + serviceTime;
				}
				if (arrivalEventList[i] >= departureEventList[i-1]) {
					departureEventList[i] = arrivalEventList[i] + serviceTime;
					continue;
				}
				else if ((arrivalEventList[i] >= departureEventList[j])) {
					departureEventList[i] = departureEventList[i-1] + serviceTime;
				}
			}
			
		}
   
		cout << left << setw(15) << i+1 <<
			setw(20) << arrivalEventList[i] <<
				setw(10) << link[i]+1;
					
   
		if (departureEventList[i] == -1) {
			cout << left << setw(20) << "drop" <<
				setw(20) << "drop";
		}
		else {
			cout << left << setw(20) << serviceTime << 
				setw(20) << departureEventList[i];
		}

		cout << left << setw(10) << count[link[i]] <<
			setw(10) << 0 << endl;
	}
	return 0;
}
