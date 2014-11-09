#include "Connection.h"
#include "Wavelength.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>

using namespace std;

vector< Connection> connections;
const int n = 1000000; //Number of events
const int w = 10;
vector< Wavelength> wavelengths;
const double lambda = 5.0; //arrival rate (requests/sec)
const double mu = 1.0; //duration

int dropCount = 0;
double blockingProb = 0.0;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
uniform_int_distribution<int> nodeDistribution(0,9);
exponential_distribution<double> arrivalDistribution(lambda);
exponential_distribution<double> durationDistribution(mu);

void createWavelengths();
void printHeaders();
int generateNode();
double generateArrival();
double generateDuration();
void printConnections(Connection connection);
void runDiagnostics();
void printDiagnostics();

double totalTime = 0;
int main() {
	
	
	createWavelengths();
	
	//printHeaders();
	
	//Main loop
	for (int i = 0; i < n; i++) {
		
		//Add a connection to the connections list
		Connection connection;
		connections.push_back(connection);
		
		
		//Part A --------------------------------------------------------------------
		
		//Determine and set nodes
		connections[i].setNode1(generateNode());
		int node2 = generateNode();
		while (node2 == connections[i].getNode1()) {
			node2 = generateNode();
		}
		connections[i].setNode2(node2);
		
		//---------------------------------------------------------------------------
			
				
		//Part B --------------------------------------------------------------------
		/*
		connections[i].setNode1(0);
		connections[i].setNode2(9);
		*/
		//---------------------------------------------------------------------------
		
		//Generate arrival time
		totalTime += generateArrival();
		connections[i].setArrivalTime(totalTime);
		
		//Generate duration
		double temp = generateDuration();
		//totalTime +=temp;
		connections[i].setDuration(temp);
		
		//Determine departure time
		connections[i].setDepartureTime(totalTime+temp);
		
		
		//Part A-B ------------------------------------------------------------------
		/*
		for (int j = 0; j < w; j++) {
		if (!wavelengths[j].checkPath(connections[i].getNode1(),\
		connections[i].getNode2(),connections[i].getArrivalTime())) {
				
		wavelengths[j].setPath(connections[i].getNode1(),\
		connections[i].getNode2(),connections[i].getDepartureTime());
		connections[i].setWavelength(j);
		break;
		}
		}
		*/
		//---------------------------------------------------------------------------
		
		
		//Part D --------------------------------------------------------------------
		
		//Obtain nodes in order of magnitude
		int minimum = min(connections[i].getNode1(),connections[i].getNode2());
		int maximum = max(connections[i].getNode1(),connections[i].getNode2());

		//Set counter to 0
		int tempWaveCount = 0;
		
		//Loop through the wavelength vectors and compare listed
		//departure time with arrival time of current connection
		for (int k = minimum; k < maximum; k++) {
			for (int j = 0; j < wavelengths.size(); j++) {
				
				//If the connection can occur on this fiber,
				//increment the counter and exit the current loop.
				if (wavelengths[j].endTime[k] <= connections[i].getArrivalTime()) {
					tempWaveCount++;
					//wavelengths[j].endTime[k] = connections[i].getDepartureTime();
					j=w;
				}
			}
		}
		
		//If the counter equals the number of fibers between node 1
		//and node 2, run through the loop again and set the end time
		//in the wavelength vector(s) to be the departure time for the
		//current connection, then break the loop
		if (tempWaveCount == (maximum-minimum)) {
			connections[i].setWavelength(-1);
			for (int k = minimum; k < maximum; k++) {
				for (int j = 0; j < wavelengths.size(); j++) {
					if (wavelengths[j].endTime[k] <= connections[i].getArrivalTime()) {
						wavelengths[j].endTime[k] = connections[i].getDepartureTime();
						j=w;
					}
				}
			}
		}
		//---------------------------------------------------------------------------
		
		if (connections[i].getWavelength()+1==-1) {
			connections[i].setDrop(true);
			dropCount++;
		}
		
		//printConnections(connections[i]);
	}
	
	runDiagnostics();
	printDiagnostics();
}

void createWavelengths() {
	//Set up vector of wavelengths
	for (int j = 0; j < w; j++) {
		Wavelength wavelength;
		wavelengths.push_back(wavelength);

	}
}

void printHeaders() {
	//Print out the header
	cout << left << setw(15) << "Connection #";
	cout << setw(15) << "Start node";
	cout << setw(15) << "End node";
	cout << setw(15) << "Wavelength";
	// cout << setw(15) << "Fiber";
	cout << setw(15) << "Arrival";
	cout << setw(15) << "Duration";
	cout << setw(15) << "Departure";
	cout << setw(15) << "Drop" << endl;
}

int generateNode() {
	return nodeDistribution(generator);
}

double generateArrival() {
	return arrivalDistribution(generator);
}

double generateDuration() {
	return durationDistribution(generator);
}

void printConnections(Connection connection) {
	//Print out the current connection #
	cout << left << setw(15) << connections.size();
	cout << setw(15) << connection.getNode1()+1;
	cout << setw(15) << connection.getNode2()+1;
	cout << setw(15) << connection.getWavelength()+1;
	cout << setw(15) << connection.getArrivalTime();
	cout << setw(15) << connection.getDuration();
	cout << setw(15) << connection.getDepartureTime();
	cout << setw(15) << connection.getDrop() << endl;
}

void runDiagnostics() {
	blockingProb = double(dropCount)/double(n);
}

void printDiagnostics() {
	cout << "Total requests: " << n << endl;
	cout << "Total drops: " << dropCount << endl;
	cout << "Blocking probability: " << setprecision(4) << blockingProb*100 << "\%" << endl;
}