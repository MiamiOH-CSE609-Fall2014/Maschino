#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;

#include "linear.h"

class PresidentData {
public:
    string name;
    int date;
    bool operator == (PresidentData right) {
	return this->name == right.name;
    }
};

int main( int argc, char ** argv ) {
    if (argc != 2 ) return -1;
    fstream dataFile;
    dataFile.open(argv[1], fstream::in);
    string name;
    vector<PresidentData> presidents;

    char buf[80];
    class PresidentData temp;
    while ( dataFile.getline(buf, 80) )
    {
	temp.name = string(buf);
	dataFile.getline(buf, 80);
	temp.date = atoi(buf);
	presidents.push_back( temp );
    }
/*
    for ( int i=0; i<presidents.size(); i++)
    {
	cout << presidents.at(i).name << " date: " << presidents.at(i).date << endl;
    }
*/
    int answer;
    do {
	cout << "Name: " ;
	cin >> name;
	if ( name == "quit" ) return 0;
	temp.name = name;
	temp.date = 0;
	answer = linearSearch( presidents, temp );
	if ( answer == -1 ) {
	    cout << "Name not found!" << endl;
	} else {
	    cout << name << " was inaugurated in  " << presidents.at(answer).date << endl;
	}
    } while ( name != "quit" );
  
    return 0;
} 
