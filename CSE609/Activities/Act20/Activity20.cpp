#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <list>
#include <sstream>
#include <stdexcept>

using namespace std;

int main() {
  string length;
  srand(time(NULL));
  cout << "Enter the length of the list: ";
  try {
    cin >> length;
    istringstream s (length);
    int x;
    char c;
    if (!(s>>x) || (s>>c)) {
      throw invalid_argument("You did not enter a number. Program aborted.");
    }
  }
  catch (invalid_argument e) {
    cout << e.what() << endl;
    return 0;
  }
  list<int> nums;
  int l = atoi(length.c_str());
  int num;
  for (int i=0; i<l; i++) {
     num = rand() % 10 + 1;
     nums.push_back(num);
  }

  cout << endl;
  cout << "Here is your list:" << endl;
  
  for (list<int>::iterator it = nums.begin(); it != nums.end(); it++) {
    cout << *it << endl;
  }

  nums.sort();


  cout << endl;
  cout << "Here is your sorted list:" << endl;
  for (list<int>::iterator it = nums.begin(); it != nums.end(); it++) {  
    cout << *it << endl;
  }

  list<int>:: iterator it = nums.begin();

  advance(it,(l/2));

  nums.insert(it,-1);

  cout << endl;
  cout << "Here is your list with a negative number in the middle:" << endl;
  for (list<int>::iterator it = nums.begin(); it != nums.end(); it++) {  
    cout << *it << endl;
  }
  return 0;
}
