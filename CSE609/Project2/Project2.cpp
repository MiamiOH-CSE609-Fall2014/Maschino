#include <iostream>
#include <string>
#include <vector>

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
void getInput();
void printScale();

int main() {
  
  cout << string(100, '\n');

  welcome();
  getInput();

  //  section.push_back(student());

  cout << "Student's name is: " << section[0].name << endl;

  cout << endl;
  return 0;
}

void welcome() {
  cout << "\nWelcome to ClassCurv2.0" << endl;
  cout << "To begin using this tool, type";
  cout << " a name and press ENTER: ";
  
}

void getInput() {
  getline(cin, section[0].name);
}

void printScale() {
  cout << "\nGrading Scale" << endl;
  cout << "\nA" << "\tabove 92.3%" << endl;
  cout << "\nB" << "\t82.1% - 92.3%" << endl;
  cout << "\nC" << "\t72.0% - 82.1%" << endl;
  cout << "\nD" << "\t61.8% - 72.0%" << endl;
  cout << "\nF" << "\tbelow 61.8%" << endl;
}
