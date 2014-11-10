#include <string>
#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

int main() {
  
  cout << "Enter a string: ";
  string input;
  cin >> input;

  stack<char> chars;
  //  const char *cstr = new char[input.length()+1];
  //strcpy(cstr,input.c_str());
  for (string::iterator it = input.begin(); it!=input.end(); it++) {
    // string temp = *it;
    // char *cstr = new char[temp.length()+1];
    // strcpy(cstr,temp.c_str());
    chars.push(*it);
  }


  while(!chars.empty()) {
    cout << chars.top() <<endl;
    chars.pop();
  }

  return 0;  
}
