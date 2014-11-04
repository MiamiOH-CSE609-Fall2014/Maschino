#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <fstream>

using namespace std;

void parseFastaFile(string filepath);

int main() {
  parseFastaFile("human22.txt");
  return 0;
}

void parseFastaFile(string filepath) {
  ifstream file(filepath);

  string header;
  //getline(file,header,';');
  //cout << header << endl;

  vector<string> comments;
  string sequence;

  string temp;  
  while(file.good()) {
    getline(file,temp);
    if (temp.length() > 0) {
      if (temp.at(0)=='>') {
	header = temp;
	cout << header << endl;
      }
      else if (temp.at(0)==';') {
	comments.push_back(temp);
	cout << temp << endl;
      }
      else {
	sequence += temp;
      }
    }
      
  }
  cout << sequence << endl;
}
