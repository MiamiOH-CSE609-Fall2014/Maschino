#include <iostream>
#include <fstream>

using namespace std;

int main() {
  
  string filename;
  string input;
  cout << "\nEnter a file name: ";
  cin >> filename;
  cin.ignore();

  ofstream myfile;
  filename = filename + ".txt";

  cout <<"\nFile name is: " << filename << endl;
  myfile.open(filename.c_str());
  if (myfile.is_open()) {
  while(getline(cin,input)) {

    myfile << input << "\n";

  }
  myfile.close();
  }
  return 0;

}
