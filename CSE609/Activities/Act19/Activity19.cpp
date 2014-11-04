#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
//#include <pair>


using namespace std;

int main() {

  map<string,pair<string,string> > info;
  pair<string,string> p;
  vector<string> value(3);

  ifstream myfile ("students.csv");

      while (myfile.good() ) {
	string temp;
	getline(myfile,temp,'\n');

	//cout << temp << endl;

	int s = temp.find(",");	
	value[0] = temp.substr(0,s);
	//cout << value[0] << endl;

	s = temp.substr(s+1,temp.length()-1).find(",");
	value[1] = temp.substr(value[0].length()+1,s);
	//cout << value[1] << endl;

	value[2] = temp.substr(value[1].length()+value[0].length()+2,temp.length()-1);
	//cout << value[2] << endl;
	info[value[0]] = make_pair(value[1],value[2]);
      }
      myfile.close(); 

      string input;
      while (input!="quit") {
	cin >> input;
	try {
	  if (input!="quit") {
	    if (info.count(input) < 1) {
	      throw invalid_argument("Please enter a valid name.");
	    }
	    else {
	      cout << "Name: " << info.find(input)->first << endl;
	      cout << "Major: " << get<0>(info.find(input)->second) << endl;
	      cout << "GPA: " << get<1>(info.find(input)->second) << endl;
	    }
	  }
	}
	catch (invalid_argument e) {
	  cout << e.what() << endl;
	}
      }

  return 0;
}
