#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void parseFile(string filepath);
void getHeaders(string info);

int main(int argc, char* argv[]) {
	
	parseFile(argv[1]);
	
	return 0;
}

void parseFile(string filepath) {
	ifstream file(filepath);
	string temp;
	
	getline(file,temp);
	getHeaders(temp);
	
	while(file.good()) {
		getline(file,temp);
		if (temp.length() > 0) {
			if (temp.at(0)=='>') {
				// header = "('" + temp + "',";
			}
			else if (temp.at(0)==';') {
				// string comment;
				//if (comments.size() == 0) {
				// comment = "['" + temp;
				//}
				//else {
				// comment = "'" + temp;
				//}
				// comments.push_back(comment);
			}
			else {
				// sequence += temp;
			}
		}   
	}
	
	// // cout << header << endl;
	// 	for (int i=0; i<comments.size()-1;i++) {
	// 		comments[i] += "',";
	// 		// cout << comments[i] << endl;
	// 	}
	// 	comments[comments.size()-1] += "'],";
	// 	// cout << comments[comments.size()-1] << endl;
	// 	// cout << "'" << sequence << "')" << endl;
	//
	// 	DNA = make_tuple(header,comments,sequence);
}

void getHeaders(string info) {
	
	//Get the original header
	//STATION,STATION_NAME,ELEVATION,LATITUDE,LONGITUDE,DATE,EMXP,MXSD,DSNW,TPCP,TSNW,EMXT,EMNT,MMXT,MMNT,MNTM
	string temp = info;
	
	int numHeaders = 0;
	while (info.find(',') != string::npos) {
		numHeaders++;
		info = 	info.substr(info.find(',')+1,info.length());
	}
	numHeaders++;
	cout << numHeaders << endl;
	info = temp;

	//Remove STATION and STATION_NAME
	info = 	info.substr(info.find(',')+1,info.length());
	info = 	info.substr(info.find(',')+1,info.length());
	
	int i = 1;
	cout << info.substr(0,info.find(',')) << endl;
	while (i < numHeaders-2) {
		info = 	info.substr(info.find(',')+1,info.length());
		cout << info.substr(0,info.find(',')) << endl;
		i++;		
	}
}