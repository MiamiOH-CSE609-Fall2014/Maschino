#include <iostream>
#include <stdexcept>

using namespace std;

const int max_values = 1000;
const int max_columns = 200;
const int max_rows = 100;

int rows;
int columns;

void getInput(int &r, int &c);

int main() {
  
  getInput(rows,columns);
}

void getInput(int &r, int &c) {
   
  try {
   
    cout << "Enter the rows: ";
    cin >> r;
    cout << "Enter the columns: ";
    cin >> c;

     if (r > max_rows) {
       throw out_of_range("Matrix rows are greater than the maximum allowed.");
    }
     if (c > max_columns) {
       throw out_of_range("Matrix columns are greater than the maximum allowed.");
     }
     if ((r * c) > max_values) {
       throw range_error("The total size of the matrix exceeds the total allowed size.");
     }
     else {
       int matrix[rows][columns];
       cout << "A " << rows << " x " << columns << " matrix has been created." << endl;
     }
  }
  catch (out_of_range err) {
    cout << err.what() << "\nTry again? Enter y or n" << endl;
    char c;
    cin >> c;
    if (c == 'y') {
      getInput(rows,columns);
    }
  }
  catch (range_error err) {
    cout << err.what() << "\nTry again? Enter y or n" << endl;
    char c;
    cin >> c;
    if (c == 'y') {
      getInput(rows,columns);
    }
  }
}
