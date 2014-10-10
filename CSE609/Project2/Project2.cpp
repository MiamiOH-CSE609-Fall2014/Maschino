#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;


double A_Scale;
double B_Scale;
double C_Scale;
double D_Scale;
double F_Scale;

struct student {
  string name;
  float grade;
};

vector<student> section;

void welcome();
void getInput(int i);
void printScale();

int main() {
  
  cout << string(100, '\n');

  section.push_back(student());

  welcome();

  cout << "Would you like to add a student to ";
  cout << "the grade distribution? (y/n) " << endl;

  try {
    char input;
    getline(cin, input);
    if (input!='y' || input!='n') {
      throw invalid_argument("Sorry! You need to enter either 'y' or 'n'");
    }  
  }
  catch (exception e) {
    cout << e.what();
    getInput();
  }

  // getInput();

  cout << "Student's name is: " << section[0].name << endl;

  cout << endl;
  return 0;
}

void welcome() {
  cout << "\nWelcome to ClassCurv2.0" << endl;
}

void getInput(int i) {
  getline(cin, section[i].name);

  do {
    cout << "Name: " << endl;
  }
  while(getline(cin
}

void printScale() {
  cout << "\nGrading Scale" << endl;
  cout << "\nA" << "\tabove 92.3%" << endl;
  cout << "\nB" << "\t82.1% - 92.3%" << endl;
  cout << "\nC" << "\t72.0% - 82.1%" << endl;
  cout << "\nD" << "\t61.8% - 72.0%" << endl;
  cout << "\nF" << "\tbelow 61.8%" << endl;
}
