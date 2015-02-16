#include <iostream>
#include <string>

using namespace std;

int main() {

  string name;
  int age;
  int time[3];
  string ageCategory;
  string qualification;

  cout << "Enter a first name and last name (i.e., Bob Jones): ";
  getline(cin,name);

  cout << "Enter an age for " << name << ": ";
  cin >> age;

  cout << "Enter time as hours minutes seconds: ";
  cin >> time[0];
  cin >> time[1];
  cin >> time[2];

  if (age < 13) {
    ageCategory = "Youth";
    if (time[0] <= 1) {
      if (time[1] <= 55) {
	qualification = "State qualifier";
      }
    }
    else if (time[0] <= 2) {
      if (time[1] <= 58) {
	qualification = "District qualifier";
      }
    }
    else if (time[0] > 2) {
      if (time[1] > 58) {
	qualification = "not qualified";
      }
    }
  }
  else if ((age >= 13) && (age < 21)) {
    ageCategory = "Teen";
    if (time[0] <= 1) {
      if (time[1] <= 35) {
	qualification = "State qualifier";
      }
    }
    else if (time[0] <= 2) {
      if (time[1] <= 30) {
	qualification = "District qualifier";
      }
    }
    else if (time[0] > 2) {
      if (time[1] > 30) {
	qualification = "not qualified";
      }
    }
  }
  else if (age >= 21) {
    ageCategory = "Adult";
    if (time[0] <= 1) {
      if (time[1] <= 20) {
	qualification = "State qualifier";
      }
    }
    else if (time[0] <= 1) {
      if (time[1] <= 58) {
	qualification = "District qualifier";
      }
    }
    else if (time[0] > 1) {
      if (time[1] > 58) {
	qualification = "not qualified";
      }
    }
  }

  cout << name << " is in age category " << ageCategory << " (" << age << "), time (" << time[0] << ":" << time[1] << ":" << time[2] << ") is " << qualification << endl;

  return 0;
}
