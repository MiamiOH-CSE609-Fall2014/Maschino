#include <iostream>

using namespace std;

int main() {
  string string1,string2,string3,string4,string5;
  
  getline(cin,string1);
  getline(cin,string2);
  getline(cin,string3);
  getline(cin,string4);
  getline(cin,string5);

  cout << string1 << endl;
  cout << string2 << endl;
  cout << string3 << endl;
  cout << string4 << endl;
  cout << string5 << endl;

  cout << string1 << "^" << string2 << "^" << string3 << "^" << string4 << "^" << string5 << endl;

  return 0;
}
