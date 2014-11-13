#include "Connection.h"
#include "Wavelength.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <map>

#include <lemon/path.h>
#include <lemon/concepts/graph.h>
#include <lemon/list_graph.h>
#include <lemon/bfs.h>

using namespace std;
using namespace lemon;

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
uniform_int_distribution<int> nodeDistribution(0,12);
exponential_distribution<double> arrivalDistribution(lambda);
exponential_distribution<double> durationDistribution(mu);


ListGraph graph;
vector<ListGraph::Node> nodes(13);
vector<ListGraph::Edge> edges(15);
map<int,pair<string,ListGraph::Node> > locations;
typedef ListGraph Graph_t;
typedef Path<Graph_t> Path_t;



void initializeGraph();
int getEdgeID(int n1, int n2);
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
	
	
	
	initializeGraph();
	
	
	
	/*
	graph.erase(edges[0]);
	bfs.init();
	bfs.addSource(get<1>(locations.find(0)->second));
	bfs.start();

	cout << bfs.path(get<1>(locations.find(23)->second)).length() << endl;

	cout << graph.id(graph.v(edges[1])) << endl;
	*/
	
	
	
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






		Bfs<ListGraph> bfs(graph);

		//Obtain shortest path
		bfs.init();
		bfs.addSource(get<1>(locations.find(connections[i].getNode1())->second));
		bfs.start();
		//bfs.run(AMES1) ---> if true, path exists
	
	
		//Store path
		Path<Graph_t> p(bfs.path(get<1>(locations.find(connections[i].getNode2())->second)));
	
		/*
		//Print out the path length
		cout << endl;
		cout << "Path length: ";
		cout << p.length() << endl;
		*/
	
		//Part A --------------------------------------------------------------------
		/*
		int n1Past;
		int n2Past;
		for (int j = 0; j < w; j++) {
			int count = 0;
			for (int k = 0; k < p.length(); k++) {
				//Pull nodes from edge	
				int n1 = min(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
				int n2 = max(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
		
				/* This code used for debugging
				if (i > 0) {
				if (n1Past == n1 || n2Past == n1) {
				//cout << locations.find(n2)->first << ", ";
				cout << (locations.find(n2)->first) << endl;
				}
				else if (n1Past == n2 || n2Past == n2) {
				//cout << locations.find(n1)->first << ", ";
				cout << (locations.find(n1)->first) << endl;
				}
				}
				if (k == 0 && p.length() > 1) {
				if ((graph.id(graph.v(p.nth(k+1))) == n1) || (graph.id(graph.u(p.nth(k+1))) == n1)) {
				//cout << locations.find(n1)->first << ", ";
				cout << "Node 1: " << (locations.find(n2)->first) << endl;
				cout << "Node 2: " << (locations.find(n1)->first) << endl;
				}
				else if ((graph.id(graph.v(p.nth(k+1))) == n2) || (graph.id(graph.u(p.nth(k+1))) == n2)) {
				//cout << locations.find(n2)->first << ", ";
				cout << "Node 1: " << (locations.find(n1)->first) << endl;
				cout << "Node 2: " << (locations.find(n2)->first) << endl;
				}
				}
				if (k == 0 && p.length() == 1) {
				cout << "Node 1: " << (locations.find(connections[k].getNode1())->first) << endl;
				cout << "Node 2: " << (locations.find(connections[k].getNode2())->first) << endl;
				}
				n1Past = min(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
				n2Past = max(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
				*/
				
				
				//cout << "Edge ID: " << getEdgeID(n1,n2) << endl;
		/*
				if (!wavelengths[j].checkPath(getEdgeID(n1,n2),connections[i].getArrivalTime())) {
					count++;
				}
				
			}
			
			if (count == p.length()) {
				for (int k = 0; k < p.length(); k++) {
					int n1 = min(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
					int n2 = max(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
					
					wavelengths[j].setPath(getEdgeID(n1,n2),connections[i].getDepartureTime());
					connections[i].setWavelength(j);
				}
				break;
			}
			
		}
		*/
		//---------------------------------------------------------------------------	
	
		//Part D --------------------------------------------------------------------
		
		//Set counter to 0
		int tempWaveCount = 0;

		//Loop through the wavelength vectors and compare listed
		//departure time with arrival time of current connection
		for (int k = 0; k < p.length(); k++) {
			
			int n1 = min(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
			int n2 = max(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
			
			for (int j = 0; j < wavelengths.size(); j++) {

				//If the connection can occur on this fiber,
				//increment the counter and exit the current loop.
				if (!wavelengths[j].checkPath(getEdgeID(n1,n2),connections[i].getArrivalTime())) {
					tempWaveCount++;
					j=w;
				}
			}
		}

		//If the counter equals the number of fibers between node 1
		//and node 2, run through the loop again and set the end time
		//in the wavelength vector(s) to be the departure time for the
		//current connection, then break the loop
		if (tempWaveCount == (p.length())) {
			connections[i].setWavelength(-1);
			for (int k = 0; k < p.length(); k++) {
				
				int n1 = min(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
				int n2 = max(graph.id(graph.v(p.nth(k))),graph.id(graph.u(p.nth(k))));
				
				for (int j = 0; j < wavelengths.size(); j++) {
					if (!wavelengths[j].checkPath(getEdgeID(n1,n2),connections[i].getArrivalTime())) {
						wavelengths[j].setPath(getEdgeID(n1,n2),connections[i].getDepartureTime());
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

void initializeGraph() {
	
	
	for (int i = 0; i<13; i++) {
		nodes[i] = graph.addNode();
	}
	
	ListGraph::Node ANN_ARBOR = nodes[0];
	ListGraph::Node	ATLANTA = nodes[1];
	ListGraph::Node	BOULDER = nodes[2];
	ListGraph::Node	CHAMPAIGN = nodes[3];
	ListGraph::Node	HOUSTON = nodes[4];
	ListGraph::Node	ITHACA = nodes[5];
	ListGraph::Node	LINCOLN = nodes[6];
	ListGraph::Node	PALO_ALTO = nodes[7];
	ListGraph::Node	PITTSBURGH = nodes[8];
	ListGraph::Node	PRINCETON = nodes[9];
	ListGraph::Node	SALT_LAKE_CITY = nodes[10];
	ListGraph::Node	SAN_DIEGO = nodes[11];
	ListGraph::Node	SEATTLE = nodes[12];
	
	


	locations[0] = make_pair("ANN_ARBOR",ANN_ARBOR);
	locations[1] = make_pair("ATLANTA",ATLANTA);
	locations[2] = make_pair("BOULDER",BOULDER);
	locations[3] = make_pair("CHAMPAIGN",CHAMPAIGN);
	locations[4] = make_pair("HOUSTON",HOUSTON);
	locations[5] = make_pair("ITHACA",ITHACA);		
	locations[6] = make_pair("LINCOLN",LINCOLN);
	locations[7] = make_pair("PALO_ALTO",PALO_ALTO);
	locations[8] = make_pair("PITTSBURGH",PITTSBURGH);
	locations[9] = make_pair("PRINCETON",PRINCETON);
	locations[10] = make_pair("SALT_LAKE_CITY",SALT_LAKE_CITY);
	locations[11] = make_pair("SAN_DIEGO",SAN_DIEGO);
	locations[12] = make_pair("SEATTLE",SEATTLE);


	

		
	//Connections
	edges[0] = graph.addEdge(ANN_ARBOR, CHAMPAIGN);
	edges[1] = graph.addEdge(ANN_ARBOR, PALO_ALTO);
	edges[2] = graph.addEdge(ANN_ARBOR, PITTSBURGH);
	edges[3] = graph.addEdge(ANN_ARBOR, ITHACA);
	
	edges[4] = graph.addEdge(ATLANTA, HOUSTON);
	edges[5] = graph.addEdge(ATLANTA, PRINCETON);
	
	edges[6] = graph.addEdge(BOULDER, CHAMPAIGN);
	edges[7] = graph.addEdge(BOULDER, SALT_LAKE_CITY);
	edges[8] = graph.addEdge(BOULDER, SEATTLE);
	
	edges[9] = graph.addEdge(CHAMPAIGN, LINCOLN);
	edges[10] = graph.addEdge(CHAMPAIGN, HOUSTON);
	
	edges[11] = graph.addEdge(HOUSTON, SAN_DIEGO);
	
	edges[12] = graph.addEdge(ITHACA, PRINCETON);	

	edges[13] = graph.addEdge(PALO_ALTO, SAN_DIEGO);	
	edges[14] = graph.addEdge(PALO_ALTO, SEATTLE);
}

int getEdgeID(int n1, int n2) {
	
	for (int i = 0; i < edges.size(); i++) {
		if ((graph.id(graph.u(edges[i])) == n1) && (graph.id(graph.v(edges[i])) == n2)) {
			return i;
		}
	}
	
	return -1;
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