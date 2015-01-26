#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include "gnuplot-iostream.h"


using namespace std;

int numHeaders = 0;
int numLines = 0;
vector< vector<string> > data;
ifstream file;

void resetFile(string filepath);
int menu();
void writeData(vector< vector<string> > data,int choice);
void printData(vector< vector<string> > data);
void gnuplot();
vector< vector<string> > parseFile(string filepath);
void getHeaders(string info);

int main(int argc, char* argv[]) {
	
	int choice = menu();
	data = parseFile(argv[1]);
	writeData(data,choice);
	printData(data);
	gnuplot();
	
	return 0;
}

void resetFile(string filepath) {
	//Reset file stream
	file.close();
	file.open(filepath);
}

int menu() {
	string temp,choice;
	system("say 'Welcome!'");
	cout << "\nWelcome! What is your name?" << endl;
	cin >> temp;
	system(("say 'Hello "+temp+"'").c_str());
	
	cout << "Visualization Menu:" << endl;
	cout << "\t1 - Extreme maximum daily precipitation within month (EMXP):" << endl;
	cout << "\t2 - Maximum snow depth reported during month (MXSD):" << endl;
	cout << endl;
	cout << "\t4 - Total monthly precipitation (TPCP):" << endl;
	cout << "\t5 - Total monthly snowfall (TSNW):" << endl;
	cout << "\t6 - Extreme Maxmimum temperature (EMXT):" << endl;
	cout << "\t7 - Extreme minimum temperature (EMNT):" << endl;
	cout << "\t8 - Monthly mean maximum temperature (MMXT):" << endl;
	cout << "\t9 - Monthly mean minimum temperature (MMNT):" << endl;
	cout << "\t10 - Monthly mean temperature (MNTM):" << endl;
	system("say 'What would you like to do with this data?'");
	cin >> choice;
	return stoi(choice,nullptr);
}

void printData(vector< vector<string> > data) {
	
	system("say 'I am now printing out the data for your reference.'");
	
	//Print out data
	for (int i = 0; i < numLines; i++) {
		for (int j = 0; j < numHeaders-1; j++) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
}

void writeData(vector< vector<string> > data,int choice) {
	ofstream output;
	output.open("weather_data.txt");
	system("say 'The data has been written to the file weather_data.txt.'");
	for (int i = 0; i < numLines; i++) {
		
			output << "\n" << data[i][0] << "\t";
			output << data[i][1] << "\t";
			output << data[i][choice+1];
			
			if (i < numLines-2 && (data[i][0]!=data[i+1][0])) {
				output << "\n";
			}
	}
	
	output.close();
}

void gnuplot() {
	Gnuplot gp("tee plot.gp | gnuplot -persist");
	gp << "set terminal png\n";
	gp << "set output 'plot_1.png'\n";
	gp << "reset\n";
	// gp << "set xtics 1\n";
	// 	gp << "set x2tics 1\n";
	// 	gp << "set autoscale xfix\n";
	// 	gp << "set autoscale x2fix\n";
	// 	gp << "set x2range [2001:2013]\n";
	// set xlabel 'P'\n
	// 	set ylabel 'T'\n
	// 	set x2label 'V'\n";
	
	//gp << "set xrange [2001:2013]\nset yrange [0:100]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
    
	//gp << "plot sin(x)/x\n";
	//gp << "plot '-' using 3:2 with linespoints lw 2 title 'pts_A'\n";//, '-' with linespoints title 'pts_B'\n";
	//gp.send1d(boost::make_tuple(year, minTemp, month));//, pts_B_dx, pts_B_dy));
	
	
	
	gp << "set surface\n\
		set contour base\n\
			set view 60, 30, 1, 1\n\
				set key right\n\
					set dgrid3d\n\
						set grid xtics ytics ztics lc rgb '#cccccc'\n\
							set title 'Multi-Year Weather Data from NOAA' font 'Arial-Bold'\n\
								set xlabel 'Year' rotate parallel offset 0,-1  font 'Arial-Bold'\n\
									set ylabel 'Month' rotate parallel  font 'Arial-Bold'\n\
										 set zlabel 'Magnitude' rotate parallel font 'Arial-Bold'\n\
											set xrange [1948:2014]\n";
	gp << "splot 'weather_data.txt' using 1:2:3 notitle with pm3d\n";
	//gp.send1d(boost::make_tuple(year,month, minTemp));//, pts_B_dx, pts_B_dy));
	
	system("say 'The file has been created.'");
	system("open 'plot_1.png'");
}

vector< vector<string> > parseFile(string filepath) {
	
	//Open the file stream
	file.open(filepath);
	
	//Identify total number of data points
	string temp;
	for (numLines = 0; std::getline(file, temp); numLines++);
	
	resetFile(filepath);
	
	//Pull out the headers for the file
	getline(file,temp);
	getHeaders(temp);
	
	//Generate empty vector of vectors
	vector< vector<string> > data(numLines,vector<string>(numHeaders-1));
	
	//Begin parsing file
	int i = 0;
	while(file.good()) {
		//Obtain a new line of the file
		getline(file,temp);
		//Check to see that it is an actual line
		if (temp.length() > 0) {
			
			//If,anywhere in the parsing process, we see -9999, that\
			signifies that NOAA was unable to collect data for that\
				time interval and we will delete that row from the vector\
					of vectors
			if (temp.find("-9999") != string::npos) {
				unsigned rowToDelete = i;
				if (data.size() > rowToDelete) {
					data.erase( data.begin() + rowToDelete);
					numLines--;
					continue;
				}
			}
			else {
				//Loop through the content and break up the CSV file\
				by header/type and time
				for (int j = 0; j < numHeaders-1; j++) {
					temp = 	temp.substr(temp.find(',')+1,temp.length());
					
					//Special case to break up the date provided by NOAA\
					into two individual columns
					if (j==0) {
						data[i][j] = temp.substr(0,temp.find(',')).substr(0,4);
						data[i][j+1] = temp.substr(0,temp.find(',')).substr(4,temp.find(','));
						j=1;
					}
					
					//Otherwise just pull the whole column up to the delimeter
					else {
						data[i][j] = temp.substr(0,temp.find(','));					
					}
				}
			}
		}
		i++;
	}
	//Close the file
	file.close();
	return data;
}

void getHeaders(string info) {
	
	//Get the original header
	//STATION,DATE,EMXP,MXSD,DSNW,TPCP,TSNW,EMXT,EMNT,MMXT,MMNT,MNTM
	
	//Parse the header
	string temp = info;
	while (info.find(',') != string::npos) {
		numHeaders++;
		info = 	info.substr(info.find(',')+1,info.length());
	}
	numHeaders+=2;
	//cout << numHeaders << endl;
	
	
	//Look for the carriage return to count the total number of lines
	info = temp;
	int numLines = 0;
	while (info.find(13) != string::npos) {
		numLines++;
		info = 	info.substr(info.find(13)+1,info.length());
	}
	numLines++;
	//cout << numLines << endl;
	
	
	info = temp;

	//Remove STATION and DATE headers
	info = 	info.substr(info.find(',')+1,info.length());
	info = 	info.substr(info.find(',')+1,info.length());
	
	
	//Print out al of the headers
	int i = 0;
	cout << "YR" << "\t";
	cout << "MO" << "\t";
	cout << info.substr(0,info.find(',')) << "\t";
	while (i < numHeaders-4) {
		info = 	info.substr(info.find(',')+1,info.length());
		cout << info.substr(0,info.find(',')) << "\t";
		i++;		
	}
	cout << endl;
}