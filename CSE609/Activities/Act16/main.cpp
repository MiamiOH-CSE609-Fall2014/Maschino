using namespace std;

#include <iostream>

#include "Student.h"

int main()

{

  Student student1( "David", 100.0, 92.0, 87.0 );

  Student student2( "Larry", 58.0, 59.0, 61.0);

  cout << "Name: " << student1.getName() << " Test Average: " << student1.computeAverage() << endl;

  cout << "Name: " << student2.getName() << " Test Average: " << student2.computeAverage() << endl;

}
