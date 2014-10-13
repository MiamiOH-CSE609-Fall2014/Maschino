#include <iostream>
#include <fstream>

using namespace std;

char* input;
int bytes = 0;
ifstream myfile;

int main(int argc, char* argv[]) {
  

  input = argv[1];

  //  cout << "\n" << input << endl;

  ifstream myfile(input);
  string input;
  while (getline(myfile,input)) {
    bytes = input.size();
  }
  
  myfile.close();

  cout << "Size of the file: " << bytes << endl;
  return 0;
}
