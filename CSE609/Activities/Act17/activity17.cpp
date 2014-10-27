#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include "linearSearch.h"
#include "binarySearch.h"

int main( int argc, char ** argv ) {
    if (argc != 2 ) return -1;
    fstream dataFile;
    dataFile.open(argv[1], fstream::in);
    string name;
    vector<string> names;
    vector<string> scores;
    char buf[80];
    while ( dataFile.getline(buf, 80) )
    {
	names.push_back( string(buf));
	dataFile.getline(buf, 80);
	scores.push_back( string(buf));
    }

    int answer;

    cout << "Linear search - 1" << endl;
    cout << "Binary search - 2" << endl;
    cout << "Selection: ";
    int search;
    cin >> search;
    do {
	cout << "Name: " ;
	cin >> name;
	if ( name == "quit" ) return 0;

	if (search == 1) {
	  answer = linearSearch( names, name );
	}
	if (search == 2) {
	  answer = binarySearch( names, name);
	}

	if ( answer == -1 ) {
	    cout << "Name not found!" << endl;
	} else {
	    cout  <<  name << " began his presidency in the year " << scores.at(answer) << endl;
	}
    } while ( name != "quit" );
    return 0;
} 
