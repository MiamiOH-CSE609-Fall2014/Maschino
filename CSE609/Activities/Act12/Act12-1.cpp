#include <iostream>
#include <fstream>

using namespace std;

int main() {
  
  string filename;
  string input;
  cout << "\nEnter a file name:";
  cin >> filename;
  fstream myfile;
  filename = filename + ".txt";

  cout <<"\nFile name is: " << filename << endl;
  myfile.open(filename.c_str());

  while(getline(cin,input)) {

    myfile << input << endl;

  }
  myfile.close();
  return 0;

}
