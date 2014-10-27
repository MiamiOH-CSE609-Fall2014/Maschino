#include <string>

using namespace std;

class Student{
 private:
  string name;
  float score1;
  float score2;
  float score3;
  float average;
 public:
  Student();
  Student(string n, float s1, float s2, float s3);
  string getName();
  float getTest1();
  float getTest2();
  float getTest3();
  float computeAverage();
};
