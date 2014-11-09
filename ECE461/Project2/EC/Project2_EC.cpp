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
uniform_int_distribution<int> nodeDistribution(0,28);
exponential_distribution<double> arrivalDistribution(lambda);
exponential_distribution<double> durationDistribution(mu);


ListGraph graph;
vector<ListGraph::Node> nodes(29);
vector<ListGraph::Edge> edges(32);
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
	
	
	for (int i = 0; i<29; i++) {
		nodes[i] = graph.addNode();
	}
	
	ListGraph::Node AMES1 = nodes[0];
	ListGraph::Node AMES2 = nodes[1];
	ListGraph::Node ARPA = nodes[2];
	ListGraph::Node AFGWC = nodes[3];
	ListGraph::Node BBN1 = nodes[4];
	ListGraph::Node BBN2 = nodes[5];
	ListGraph::Node BELVOIR = nodes[6];
	ListGraph::Node CARNEGIE = nodes[7];
	ListGraph::Node CASE = nodes[8];
	ListGraph::Node ETAC = nodes[9];
	ListGraph::Node HARVARD = nodes[10];
	ListGraph::Node ILLINOIS = nodes[11];
	ListGraph::Node LINCOLN = nodes[12];
	ListGraph::Node MCCLELLAN = nodes[13];
	ListGraph::Node MIT = nodes[14];
	ListGraph::Node MITRE = nodes[15];
	ListGraph::Node NBS = nodes[16];
	ListGraph::Node NOAA = nodes[17];
	ListGraph::Node RADC = nodes[18];
	ListGraph::Node RAND = nodes[19];
	ListGraph::Node SAAC = nodes[20];
	ListGraph::Node SDC = nodes[21];
	ListGraph::Node SRI = nodes[22];
	ListGraph::Node STANFORD = nodes[23];
	ListGraph::Node TINKER = nodes[24];
	ListGraph::Node UCLA = nodes[25];
	ListGraph::Node UCSB = nodes[26];
	ListGraph::Node USC = nodes[27];
	ListGraph::Node UTAH = nodes[28];
	
	
	locations[0] = make_pair("AMES1",AMES1);
	locations[1] = make_pair("AMES2",AMES2);
	locations[2] = make_pair("ARPA",ARPA);
	locations[3] = make_pair("AFGWC",AFGWC);
	locations[4] = make_pair("BBN1",BBN1);
	locations[5] = make_pair("BBN2",BBN2);
	locations[6] = make_pair("BELVOIR",BELVOIR);
	locations[7] = make_pair("CARNEGIE",CARNEGIE);
	locations[8] = make_pair("CASE",CASE);
	locations[9] = make_pair("ETAC",ETAC);
	locations[10] = make_pair("HARVARD",HARVARD);
	locations[11] = make_pair("ILLINOIS",ILLINOIS);
	locations[12] = make_pair("LINCOLN",LINCOLN);
	locations[13] = make_pair("MCCLELLAN",MCCLELLAN);
	locations[14] = make_pair("MIT",MIT);
	locations[15] = make_pair("MITRE",MITRE);
	locations[16] = make_pair("NBS",NBS);
	locations[17] = make_pair("NOAA",NOAA);
	locations[18] = make_pair("RADC",RADC);
	locations[19] = make_pair("RAND",RAND);
	locations[20] = make_pair("SAAC",SAAC);
	locations[21] = make_pair("SDC",SDC);
	locations[22] = make_pair("SRI",SRI);
	locations[23] = make_pair("STANFORD",STANFORD);
	locations[24] = make_pair("TINKER",TINKER);
	locations[25] = make_pair("UCLA",UCLA);
	locations[26] = make_pair("UCSB",UCSB);
	locations[27] = make_pair("USC",USC);
	locations[28] = make_pair("UTAH",UTAH);
		
	//Connections
	edges[0] = graph.addEdge(AMES1, AMES2);
	edges[1] = graph.addEdge(AMES1, SRI);
	edges[2] = graph.addEdge(AMES2, STANFORD);
	edges[3] = graph.addEdge(ARPA, ETAC);
	edges[4] = graph.addEdge(ARPA, MITRE);
	edges[5] = graph.addEdge(AFGWC, CASE);
	edges[6] = graph.addEdge(AFGWC, NOAA);
	edges[7] = graph.addEdge(BBN1, BBN2);
	edges[8] = graph.addEdge(BBN1,MIT);
	edges[9] = graph.addEdge(BBN2, HARVARD);
	edges[10] = graph.addEdge(BELVOIR, SAAC);
	edges[11] = graph.addEdge(CARNEGIE, BELVOIR);
	edges[12] = graph.addEdge(CARNEGIE, CASE);
	edges[13] = graph.addEdge(CASE, RADC);
	edges[14] = graph.addEdge(ETAC, NBS);
	edges[15] = graph.addEdge(ETAC, TINKER);
	edges[16] = graph.addEdge(HARVARD, NBS);
	edges[17] = graph.addEdge(ILLINOIS, MIT);
	edges[18] = graph.addEdge(LINCOLN, MIT);
	edges[19] = graph.addEdge(LINCOLN, RADC);
	edges[20] = graph.addEdge(ILLINOIS, UTAH);
	edges[21] = graph.addEdge(MITRE, SAAC);
	edges[22] = graph.addEdge(MCCLELLAN, SRI);
	edges[23] = graph.addEdge(MCCLELLAN, UTAH);
	edges[24] = graph.addEdge(NOAA, USC);
	edges[25] = graph.addEdge(RAND, STANFORD);
	edges[26] = graph.addEdge(RAND, TINKER);
	edges[27] = graph.addEdge(RAND, UCLA);
	edges[28] = graph.addEdge(SDC, UCLA);
	edges[29] = graph.addEdge(SDC, USC);
	edges[30] = graph.addEdge(SRI, UCSB);
	edges[31] = graph.addEdge(UCLA, UCSB);
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