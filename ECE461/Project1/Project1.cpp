#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

/*---------- Start variable declaration ----------*/
const int n = 5500; //Number of events
const double lambda = 8.0; //mean rate of arrival
const double phi = 0.5; //probability of arrival to link 1
const double mu1 = 5.0; //mean rate of service
const double mu2 = 5.0; //mean rate of service

vector<double> times(n);
vector<int> link(n);
vector<double> arrivalEventList(n);
//vector<double> departureEventList(n);

vector< vector<double> > departureEventList(2, vector<double>(n));
vector<int> packetCount(2);
vector<int> buffer(2);

double startTime;
double interarrivalTime = 0.0;
double serviceTime;

int totalDroppedPackets = 0;
int totalServicedPackets = 0;
double blockingProbability = 0.0;

vector<double> avgDelay(2);
vector<double> avgThroughput(2);
vector<int> linkThroughput(2);

double averageNumberPackets = 0.0;
double avgSystemThroughput = 0.0;

double diagnosticStartTime = 0.0;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);

exponential_distribution<double> arrivalDistribution(lambda);
binomial_distribution<int> linkDistribution(1,1-phi);
exponential_distribution<double> serviceLink1Distribution(mu1);
exponential_distribution<double> serviceLink2Distribution(mu2);
/*---------- End variable declaration ----------*/

void printHeaders();
void getArrivalTime(int x);
void getLink(int x);
void getServiceTime(int x);
void getDepartureTime(int x);
void printData(int x);
void diagnostics();
void printDiagnostics();

int main() {

	/*---------- Start variable instantiation ----------*/
	avgDelay[0] = 0.0;
	avgDelay[1] = 0.0;
	avgThroughput[0] = 0.0;
	avgThroughput[1] = 0.0;
	linkThroughput[0] = 0;
	linkThroughput[1] = 0;
	packetCount[0] = 0;
	packetCount[1] = 0;
	buffer[0] = 20;
	buffer[1] = 20;
	/*---------- End variable instantiation ----------*/
	
	//Generate first arrival time  
  	getArrivalTime(0);
	
	//Determine link for first arrival time
	getLink(0);
  
  	//Depending on the link, generate a service time for
	//the respective mu
	getServiceTime(0);

	//Add the initial packet to the departureEventList	
	getDepartureTime(0);

	//Print the headers for the columns
	printHeaders();

	for (int i=1; i<n; i++) {
		
		//Generate interarrival time
		getArrivalTime(i);
		
		//Determine link for incoming packet
		getLink(i);
		
		//Depending on the link, generate a service time for
		//the respective mu
		getServiceTime(i);
		
		//Add the packet to the departureEventList
		getDepartureTime(i);
		
		//Print the data for the packet
		printData(i);
	}
	
	//Run the diagnostics
	diagnostics();

	//Print the diagnostics
	printDiagnostics();
	
	return 0;
}

void printHeaders() {
	//Formatting the headers for the columns
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
					setw(20) << departureEventList[link[0]][0] <<
						setw(10) << 0 <<
							setw(10) << 0 << endl;
}

void getArrivalTime(int x) {
	
	if (x == 0) {
		//Generate first arrival time
		times[x] = arrivalDistribution(generator);
		startTime = times[x];
	}
	else {
		//Generate interarrival time
		times[x] = arrivalDistribution(generator);
		interarrivalTime = times[x];
		startTime = startTime + interarrivalTime;
	}
 	
	//Add the packet to the arrivalEventList
	arrivalEventList[x] = startTime;
}

void getLink(int x) {
	link[x] = linkDistribution(generator);
}

void getServiceTime(int x) {
	if (link[x] == 0) {
		serviceTime = serviceLink1Distribution(generator);
	}
	if (link[x] == 1) {
		serviceTime = serviceLink2Distribution(generator);
	}
}

void getDepartureTime(int x) {
	if (x == 0) {	
	departureEventList[link[x]][x] = startTime + serviceTime;
	}
	else {
		int i = x;
		packetCount[link[i]] = 0;
		for (int j = 0; j < i; j++) {
			if (packetCount[link[i]]>=buffer[link[i]]) {
				departureEventList[link[i]][i] = -1;
			}
			if (departureEventList[link[i]][i-1]==-1 && departureEventList[link[i]][i]!=-1) {
				if (departureEventList[link[i]][j]!=-1) {
					departureEventList[link[i]][i] = departureEventList[link[i]][j] + serviceTime;
				}
				if (arrivalEventList[i] < departureEventList[link[i]][i-j-1]) {
					packetCount[link[i]]++;
				}
			}
			else if ((packetCount[link[i]] < buffer[link[i]])) {
				if (arrivalEventList[i] < departureEventList[link[i]][i-j-1]) {
					packetCount[link[i]]++;
					departureEventList[link[i]][i] = departureEventList[link[i]][i-1] + serviceTime;
				}
				if (arrivalEventList[i] >= departureEventList[link[i]][i-1]) {
					departureEventList[link[i]][i] = arrivalEventList[i] + serviceTime;
					continue;
				}
				else if ((arrivalEventList[i] >= departureEventList[link[i]][j])) {
					departureEventList[link[i]][i] = departureEventList[link[i]][i-1] + serviceTime;
				}
			}
			
		}
	}
}

void printData(int x) {
	int i = x;
	cout << left << setw(15) << i+1 <<
		setw(20) << arrivalEventList[i] <<
			setw(10) << link[i]+1;
				

	if (departureEventList[link[i]][i] == -1) {
		cout << left << setw(20) << "drop" <<
			setw(20) << "drop";
		if(i >= 500) {
			totalDroppedPackets++;
		}
	}
	else {
		cout << left << setw(20) << serviceTime << 
			setw(20) << departureEventList[link[i]][i];
		
		if(i >= 500) {
				linkThroughput[link[i]]++;
				if (departureEventList[link[i]][i] > arrivalEventList[i]) {
					avgDelay[link[i]] += (departureEventList[link[i]][i] - arrivalEventList[i]);
				}
				if (i == 500) {
					diagnosticStartTime = arrivalEventList[i];
				}
		}
	}

	cout << left << setw(10) << packetCount[0] <<
		setw(10) <<  packetCount[1] << endl;
}

void diagnostics() {
	totalServicedPackets = n-500-totalDroppedPackets;
	blockingProbability = double(totalDroppedPackets)/(n-500);
	
	if (phi == 0.0) {
		avgThroughput[1] = double(linkThroughput[1])/(arrivalEventList[n-1]-diagnosticStartTime);
		avgSystemThroughput = avgThroughput[1];
	}
	else if (phi == 1.0) {
		avgThroughput[0] = double(linkThroughput[0])/(arrivalEventList[n-1]-diagnosticStartTime);
		avgSystemThroughput = avgThroughput[0];
	}
	else {
		avgThroughput[0] = double(linkThroughput[0])/(arrivalEventList[n-1]-diagnosticStartTime);
		avgThroughput[1] = double(linkThroughput[1])/(arrivalEventList[n-1]-diagnosticStartTime);
		avgSystemThroughput = avgThroughput[0]+avgThroughput[1];
	}
	
	
	if (linkThroughput[0] > 0) {
		avgDelay[0] = avgDelay[0]/linkThroughput[0];		
	}

	if (linkThroughput[1] > 0) {
		avgDelay[1] = avgDelay[1]/linkThroughput[1];		
	}
}

void printDiagnostics() {
	cout << "Total serviced packets: " << totalServicedPackets << endl;
	cout << "Total dropped packets: " << totalDroppedPackets << endl;
	cout << "Bocking probability: " << blockingProbability << " = " << blockingProbability*100 << "%" << endl;
	cout << "Average system throughput (pkts/sec): " << avgSystemThroughput << endl;
	cout << "Average number of packets in the system: " << lambda*(1-blockingProbability)*(avgDelay[0] + avgDelay[1]) << endl;
	cout << endl;
	cout << "Link 1 throughput: " << linkThroughput[0] << endl;
	cout << "Link 1 average throughput (pkts/sec): " << avgThroughput[0] << endl;
	cout << "Link 1 average delay (sec): " << avgDelay[0] << endl;
	cout << endl;
	cout << "Link 2 throughput: " << linkThroughput[1] << endl;
	cout << "Link 2 average throughput (pkts/sec): " << avgThroughput[1] << endl;
	cout << "Link 2 average delay (sec): " << avgDelay[1] << endl;
	cout << endl;
}