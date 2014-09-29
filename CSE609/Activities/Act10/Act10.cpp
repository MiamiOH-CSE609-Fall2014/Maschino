#include <iostream>
#include <stdexcept>

using namespace std;

const int max_values = 100;
const int columns = 200;
const int rows = 100;

void getInput(int r, int c);

int main() {
  
  getInput(rows,columns); 
 

}

void getInput(int r, int c) {
  cout << "Enter the rows: ";
  cin >> r;
  cout << "Enter the columns: ";
  cin >> c;

  if (r > rows || c > columns) {
    throw out_of_range("The input is too large");
  }
}
