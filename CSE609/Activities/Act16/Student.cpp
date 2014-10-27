#include "Student.h"
#include <string>

using namespace std;

Student::Student() {
  name = "";
  score1 = 0.0;
  score2 = 0.0;
  score3 = 0.0;
  average = (score1+score2+score3)/3;
}

Student::Student(string n, float s1, float s2, float s3) {
  name = n;
  score1 = s1;
  score2 = s2;
  score3 = s3;
  average = (score1+score2+score3)/3;
}

string Student::getName() {
  return name;
}

float Student::computeAverage() {
  return average;
}

float Student::getTest1() {
  return score1;
}

float Student::getTest2() {
  return score2;
}

float Student::getTest3() {
  return score3;
}
