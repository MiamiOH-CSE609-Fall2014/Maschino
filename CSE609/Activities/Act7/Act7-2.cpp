#include <iostream>

using namespace std;

int main() {
  
  string string1,string2;
  getline(cin,string1);
  getline(cin,string2);

  if(string1==string2) {
    cout << "equal" << endl;
  }
  else {
    cout << "not equal" << endl;
    cout << "length of string one is: " << string1.length() << endl;
    cout << "length of string two is: " << string2.length() << endl;
  }

  return 0;
}
