#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <iomanip>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>

using namespace std;


double A_Scale;
double B_Scale;
double C_Scale;
double D_Scale;

double mean;
double stdDev;

struct student {
	string name;
	float grade;
	char letter;
};

vector<student> section;

void welcome();
void getInput(int i);
void setStudentName(int i);
void setStudentGrade(int i);
void getMean();
void getScale();
void getLetter();
void printScale();
void printStudents();
void printResults();


int main() {
  
	cout << string(100, '\n');

	welcome();

	getInput(0);

	getMean();
	getScale();
	getLetter();
	
	printResults();
	
	cout << endl;
	
	return 0;
}

void welcome() {
	cout << "\nWelcome to ClassCurv2.0" << endl;
	cout << "\nTo end this application, type 'none'";
	cout << "\nwhen prompted for a student name." << endl;
}

void getInput(int i) {
	/*cout << "\nWould you like to add a student to ";
	cout << "the grade distribution? (y/n) " << endl;
	*/
	cout << "\nStudent's name: ";
	
	string input;
	try {
		getline(cin, input);
		if (input!="none") {
			if (input.length()<2 || atof(input.c_str())!=0.0) {
				throw invalid_argument("Please enter a valid name.");
			}
			else {
				
				section.push_back(student());
				section[i].name = input;
				//setStudentName(i);
				setStudentGrade(i);
				getInput(i+1);

			}
		}
//		else if (input!="n") {
//			throw invalid_argument("Sorry! You need to enter either 'y' or 'n'");
//		}
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
		getInput(i);
	}	
	
}

void setStudentName(int i) {
	//section[i].name = input;
	
	// string input;
	// try {
	// 	getline(cin, input);
	// 	if (input.length()<2 || atof(input.c_str())!=0.0) {
	// 		throw invalid_argument("Please enter a valid name.");
	// 	}
	// 	else if (input!="none") {
	// 		section[i].name = input;
	// 	}
	// 	else {
	//
	// 	}
	// }
	// catch (invalid_argument e) {
	// 	cout << e.what() << endl;
	// 	setStudentName(i);
	// }	
}

void setStudentGrade(int i) {
	cout << "\nStudent's grade: ";

	string input;
	try {
		getline(cin,input);
		if (atof(input.c_str())<0.0 || atof(input.c_str())>100) {
			throw invalid_argument("Please enter a value between 0 and 100.");
		}
		else {
			section[i].grade = atof(input.c_str());
		}
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
		setStudentGrade(i);
	}
}

void getMean() {
	for (int i = 0; i < section.size(); i++) {
		mean+=section[i].grade;
	}
	mean = mean/section.size();
}

void getScale() {
	double sum = 0;
	for (int i = 0; i < section.size(); i++) {
		sum += pow((section[i].grade - mean),2);
	}
	stdDev = sqrt(sum/section.size());
	
	A_Scale = (1.5*stdDev)+mean;
	B_Scale = (0.5*stdDev)+mean;
	C_Scale = (-0.5*stdDev)+mean;
	D_Scale = (-1.5*stdDev)+mean;
	
}

void getLetter() {
	for (int i = 0; i < section.size(); i++) {
		if (section[i].grade >= A_Scale) {
			section[i].letter = 'A';
		}
		else if (section[i].grade >= B_Scale) {
			section[i].letter = 'B';
		}
		else if (section[i].grade >= C_Scale) {
			section[i].letter = 'C';
		}
		else if (section[i].grade >= D_Scale) {
			section[i].letter = 'D';
		}
		else {
			section[i].letter = 'F';
		}
	}
}

void printScale() {
	cout << "\nGrading Scale" << endl;
	cout << "\nA" << "\tabove " << setprecision(3) << A_Scale << "%" << endl;
	cout << "\nB" << "\t" << setprecision(3) << B_Scale << "% - " << A_Scale << "%" << endl;
	cout << "\nC" << "\t" << setprecision(3) << C_Scale << "% - " << B_Scale << "%" << endl;
	cout << "\nD" << "\t" << setprecision(3) << D_Scale << "% - " << C_Scale << "%" << endl;
	cout << "\nF" << "\tbelow " << setprecision(3) << D_Scale << "%" << endl;
}

void printStudents() {
	cout << setw(30) << "\nName" << setw(30) << "Score" << setw(25) << "Grade" << endl;
	cout << endl;
	
	for (int i = 0; i < section.size(); i++) {
	  cout << left << setw(2) << (i+1) << ".  " << setw(25) << section[i].name;
		cout << left << section[i].grade << setw(25) << '%';
		cout << left << setw(20) << section[i].letter << endl;
		cout << endl;
	}
	
	cout << "Class average = " << setprecision(4) << mean << "%" << endl;
	
	cout << "Standard Deviation = " << setprecision(4) << stdDev << endl;
	
}

void printResults() {
	if (section.size() > 0) {
		printScale();
		printStudents();
	}
	cout << "\nThank you for using ClassCurv2.0" << endl;
	cout << "Have a great day!" << endl;
}
