#include <string>
#include <iostream>
#include <map>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <fstream>

using namespace std;

string header;
vector<string> comments;
string sequence;

tuple<string, vector<string>, string> DNA;

void parseFastaFile(string filepath);
map<string,int> digramFreqScores(string s);
int countDigram(string s, string digram);
void digramFreqMatrix(map<string,int> d);

int main() {
	parseFastaFile("human22.txt");
	map<string,int> d = digramFreqScores(get<2>(DNA));
	digramFreqMatrix(d);
	return 0;
}

void parseFastaFile(string filepath) {
	ifstream file(filepath);
	string temp;  
	while(file.good()) {
		getline(file,temp);
		if (temp.length() > 0) {
			if (temp.at(0)=='>') {
				header = "('" + temp + "',";			
			}
			else if (temp.at(0)==';') {
				string comment;
				if (comments.size() == 0) {
					comment = "['" + temp; 
				}
				else {
					comment = "'" + temp; 
				}
				comments.push_back(comment);
			}
			else {
				sequence += temp;
			}
		}   
	}
	
	cout << header << endl;
	for (int i=0; i<comments.size()-1;i++) {
		comments[i] += "',";
		cout << comments[i] << endl;
	}
	comments[comments.size()-1] += "'],";
	cout << comments[comments.size()-1] << endl;
	cout << "'" << sequence << "')" << endl;
	
	DNA = make_tuple(header,comments,sequence);
}

map<string,int> digramFreqScores(string s) {
	map<string,int> d;
	
	d.insert(pair<string,int>("AA",countDigram(s,"AA")));
	cout << "{'AA': " << d.find("AA")->second << ", ";
	d.insert(pair<string,int>("AC",countDigram(s,"AC")));
	cout << "'AC': " << d.find("AC")->second << ", ";
	d.insert(pair<string,int>("AT",countDigram(s,"AT")));
	cout << "'AT': " << d.find("AT")->second << ", ";
	d.insert(pair<string,int>("GA",countDigram(s,"GA")));
	cout << "'GA': " << d.find("GA")->second << ", ";
	d.insert(pair<string,int>("GG",countDigram(s,"GG")));
	cout << "'GG': " << d.find("GG")->second << ", ";
	d.insert(pair<string,int>("GC",countDigram(s,"GC")));
	cout << "'GC': " << d.find("GC")->second << ", ";
	d.insert(pair<string,int>("GT",countDigram(s,"GT")));
	cout << "'GT': " << d.find("GT")->second << ", ";
	d.insert(pair<string,int>("CA",countDigram(s,"CA")));
	cout << "'CA': " << d.find("CA")->second << ", ";
	d.insert(pair<string,int>("CG",countDigram(s,"CG")));
	cout << "'CG': " << d.find("CG")->second << ", ";
	d.insert(pair<string,int>("CC",countDigram(s,"CC")));
	cout << "'CC': " << d.find("CC")->second << ", ";
	d.insert(pair<string,int>("CT",countDigram(s,"CT")));
	cout << "'CT': " << d.find("CT")->second << ", ";
	d.insert(pair<string,int>("TA",countDigram(s,"TA")));
	cout << "'TA': " << d.find("TA")->second << ", ";
	d.insert(pair<string,int>("TG",countDigram(s,"TG")));
	cout << "'TG': " << d.find("TG")->second << ", ";
	d.insert(pair<string,int>("TC",countDigram(s,"TC")));
	cout << "'TC': " << d.find("TC")->second << ", ";
	d.insert(pair<string,int>("TT",countDigram(s,"TT")));
	cout << "'TT': " << d.find("TT")->second << "}" << endl;
	
	return d;
}

int countDigram(string s, string digram) {
	int occurences = 0;
	int start = 0;
	
	while ((start = s.find(digram,start)) != string::npos) {
		occurences++;
		start += digram.length()-1;
	}
	return occurences;
}

void digramFreqMatrix(map<string,int> d) {
	vector< vector<int> > m(4,vector<int>(4));
	
	typedef map<string,int>::iterator it_type;
	
	// it_type it = d.begin();
// 	while (it != d.end()) {
// 		for (int i =0; i < 4; i++) {
// 			for (int j = 0; j<4; j++) {
//  			   m[i][j] = it->second;
//  			   it++;
// 			}
// 		}
// 	}
	// cout << "[";
// 	for (int i =0; i < 4; i++) {
// 		cout << "[";
// 		for (int j = 0; j<4; j++) {
// 			cout << m[i][j];
// 			if (j==3) {
// 				cout << ", ";
// 			}
// 		}
// 		cout << "]";
// 		if (i!=3) {
// 			cout << ", ";
// 		}
// 	}
// 	cout << "]" << endl;
}
