#include "Connection.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>

using namespace std;

vector< Connection> connections;
const int n = 10; //Number of events
const int w = 2;
//vector< Wavelength> wavelengths;
const double lambda = 5.0; //arrival rate (requests/sec)
const double mu = 1.0; //duration




unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
uniform_int_distribution<int> nodeDistribution(0,9);
exponential_distribution<float> arrivalDistribution(lambda);
exponential_distribution<float> durationDistribution(mu);

int generateNode();
float generateArrival();
float generateDuration();

float totalTime = 0;
int main() {

	//Set up vector of wavelengths
	// for (int j = 0; j < w; j++) {
// 		Wavelength wavelength;
// 		wavelengths.push_back(wavelength);
//
// 		//cout << wavelengths[j].getFiber(1) << endl;
// 	}
	
	//Print out the header
	cout << left << setw(15) << "Connection #";
	cout << setw(15) << "Start node";
	cout << setw(15) << "End node";
	cout << setw(15) << "Wavelength";
	cout << setw(15) << "Fiber";
	cout << setw(15) << "Arrival";
	cout << setw(15) << "Duration";
	cout << setw(15) << "Departure" << endl;
	
	//Main loop
	for (int i = 0; i < n; i++) {
		
		//Add a connection to the connections list
		Connection connection;
		connections.push_back(connection);
		
		//Determine and set nodes
		connections[i].setNode1(generateNode());
		int node2 = generateNode();
		while (node2 == connections[i].getNode1()) {
			node2 = generateNode();
		}
		connections[i].setNode2(node2);
		
		//Generate arrival time
		totalTime += generateArrival();
		connections[i].setArrivalTime(totalTime);
		
		//Generate duration
		float temp = generateDuration();
		//totalTime +=temp;
		connections[i].setDuration(temp);
		
		//Determine departure time
		connections[i].setDepartureTime(totalTime+temp);
		
		
		
		
		
		
		
		
		// //Check fiber from node to node for each wavelength
// 		//The first wavelength available will be set
// 		int tempMin = min(connections[i].getNode1(),connections[i].getNode2());
// 		int tempMax = max(connections[i].getNode1(),connections[i].getNode2());
// 		for (int j = 0; j < w; j++) {
// 			if (wavelengths[j].checkFiber(tempMin,tempMax)) {
// 				connections[i].setWavelength(j);
// 				break;
// 			}
//
// 		}
		
		//If it couldn't find any vacant wavelengths
		//between the nodes, the request is dropped
		// if (connections[i].getWavelength() < 0) {
// 			connections[i].setDrop(true);
// 		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		//Print out the current connection #
		cout << left << setw(15) << connections.size();
		cout << setw(15) << connections[i].getNode1()+1;
		cout << setw(15) << connections[i].getNode2()+1;
		cout << setw(15) << connections[i].getWavelength();
		cout << setw(15) << connections[i].getFiber();
		cout << setw(15) << connections[i].getArrivalTime();
		cout << setw(15) << connections[i].getDuration();
		cout << setw(15) << connections[i].getDepartureTime() << endl;
	}
}

int generateNode() {
	return nodeDistribution(generator);
}

float generateArrival() {
	return arrivalDistribution(generator);
}

float generateDuration() {
	return durationDistribution(generator);
}
