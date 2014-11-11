#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <fstream>

using namespace std;

string header;
vector<string> comments;
string sequence;

vector<string> symbols = \
	{"AA","AG","AC","AT",\
		"GA","GG","GC","GT",\
			"CA","CG","CC","CT",\
				"TA","TG","TC","TT"};
tuple<string, vector<string>, string> DNA;

void parseFastaFile(string filepath);
map<string,int> digramFreqScores(string s);
int countDigram(string s, string digram);
vector< vector<int> > digramFreqMatrix(map<string,int> d);
vector< vector<int> > parseScoringFile(string filepath);
pair<int,int> scoreSequence(string haystack, string needle, vector< vector<int> > scoring_m);
tuple<int,int,string> findHighScore(string haystack, vector<string> needles, vector< vector<int> > scoring_m);

int main(int argc, char* argv[]) {
	parseFastaFile(argv[1]);
	map<string,int> d = digramFreqScores(get<2>(DNA));
	digramFreqMatrix(d);
	vector< vector<int> > scoring_m = parseScoringFile(argv[2]);
	
	//pair<int,int> score = scoreSequence(sequence,"TAATCTCAGCACTTTGAGAGGCCGAGGCAT",scoring_m);

	string in;
	cout << endl;
	cout << "How many sequences would you like to score?" << endl;

	try {
		cin >> in;
		istringstream s (in);
		int x;
		char c;
		if (!(s>>x) || (s>>c)) {
			throw(invalid_argument("That was not a number."));
		}
		if (atoi(in.c_str())<1) {
			throw(invalid_argument("That was not a number greater than 0."));
		}
	}
	catch (invalid_argument e){
		cout << e.what() << endl;
		return 0;
	}
	vector<string> str(atoi(in.c_str()));
	
	for (int i = 0; i < str.size(); i++) {
		cout << endl;
		cout << "Enter the sequence: ";
		cin >> in;
		str[i] = in;
	}
	
	//vector<string> str = {"TAATCTCAGCACTTT", "GAGAGGCCGAGGCAT"};
	
	tuple<int,int,string> score2 = findHighScore(sequence,str,scoring_m);
	
	//cout << "(" << get<0>(score) << ", " << get<1>(score) << ")" << endl;
	cout << "(" << get<0>(score2) << ", " << get<1>(score2) << ", '" << get<2>(score2) << "')" << endl;
	
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
	
	cout << "{";
	for (int i = 0; i < symbols.size()-1; i++) {
		d.insert(pair<string,int>(symbols[i],countDigram(s,symbols[i])));
		cout << "'" << symbols[i] << "': " << d.find(symbols[i])->second << ", ";
	}
	d.insert(pair<string,int>(symbols[symbols.size()-1],\
		countDigram(s,symbols[symbols.size()-1])));
	cout << "'" << symbols[symbols.size()-1] << "': " \
		<< d.find(symbols[symbols.size()-1])->second << "}" << endl;
	
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

vector< vector<int> > digramFreqMatrix(map<string,int> d) {
	vector< vector<int> > m(4,vector<int>(4));
	
	typedef map<string,int>::iterator it_type;
	
	for (int k = 0; k < symbols.size(); k++) {
		for (it_type it=d.begin(); it!=d.end(); it++) {
			if ((it->first)==symbols[k]) {
				m[k/4][k%4] = it->second;
			}
		}
	}
		
	cout << "[";
	for (int i =0; i < 4; i++) {
		cout << "[";
		for (int j = 0; j<4; j++) {
			cout << m[i][j];
			if (j!=3) {
				cout << ", ";
			}
		}
		cout << "]";
		if (i!=3) {
			cout << ", ";
		}
	}
	cout << "]" << endl;
	
	return m;
}

vector< vector<int> > parseScoringFile(string filepath) {
	vector< vector<int> > score_matrix(4,vector<int>(4));
	
	ifstream file(filepath);
	string temp;
	string sub;
	for (int i = 0; i < 4; i++) {
		getline(file,temp);
		for (int j = 0; j < 4; j++) {
			score_matrix[i][j] = atoi(temp.substr(0,1).c_str());
			if (j!=3) {
				temp = temp.substr(temp.find(",")+1);
			}
		}
	}
	// cout << "[";
	// 	for (int i =0; i < 4; i++) {
	// 		cout << "[";
	// 		for (int j = 0; j<4; j++) {
	// 			cout << score_matrix[i][j];
	// 			if (j!=3) {
	// 				cout << ", ";
	// 			}
	// 		}
	// 		cout << "]";
	// 		if (i!=3) {
	// 			cout << ", ";
	// 		}
	// 	}
	// 	cout << "]" << endl;
	
	return score_matrix;
}

pair<int,int> scoreSequence(string haystack, string needle, vector< vector<int> > scoring_m) {
	pair<int,int> highestScore;
	
	for (int i = 0; i < haystack.length()-needle.length()+1; i++) {
		int score = 0;
		for (int j = 0; j < needle.length(); j++) {
			string hay (1,haystack.at(i+j));
			string need (1,needle.at(j));
			string key = hay + need;
			for (int k = 0; k < symbols.size(); k++) {
				if (key==symbols[k]) {
					score += scoring_m[k/4][k%4];
					k = symbols.size();
				}
			}
			
		}
		if (score >= get<1>(highestScore)) {
			highestScore = make_pair(i,score);
		}
		
	}
	return highestScore;
}

tuple<int,int,string> findHighScore(string haystack, vector<string> needles, vector< vector<int> > scoring_m) {
	tuple<int,int,string> highestScore;
	for (int z = 0; z < needles.size(); z++) {
		for (int i = 0; i < haystack.length()-needles[z].length()+1; i++) {
			int score = 0;
			for (int j = 0; j < needles[z].length(); j++) {
				string hay (1,haystack.at(i+j));
				string need (1,needles[z].at(j));
				string key = hay + need;
				for (int k = 0; k < symbols.size(); k++) {
					if (key==symbols[k]) {
						score += scoring_m[k/4][k%4];
						k = symbols.size();
					}
				}
			
			}
			//NOTE: > yields first needle, >= yields second needle
			if (score > get<1>(highestScore)) {  
				highestScore = make_tuple(i,score,needles[z]);
			}
		
		}
	}
	
	return highestScore;
}
