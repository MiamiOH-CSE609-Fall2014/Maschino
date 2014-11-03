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
	getline(myfile,value[0],',');
	getline(myfile,value[1],',');
	getline(myfile,value[2],'\n');
	info[value[0]] = make_pair(value[1],value[2]);
      }
      myfile.close(); 

      string input;
      while (input!="quit") {
	cin >> input;
	//	p = info.find(input);
	cout << "Name: " << info.begin()->first << endl;
      }

  return 0;
}
