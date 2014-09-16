#include <iostream>
#include <vector>

using namespace std;

vector< vector <int> > multiply(vector <vector <int> > Matrix1, vector <vector <int> > Matrix2, vector <vector <int> > Matrix3) {
  int m1rows,m1columns,m2rows,m2columns;
  cout << endl;
  
  m1rows = Matrix1.size();
  m1columns = Matrix1[0].size();
  m2rows = Matrix2.size();
  m2columns = Matrix2[0].size();
  
  for (int i = 0; i < m2columns; i++) {
    for (int j = 0; j < m2rows; j++) {
      for (int k = 0; k < m1rows; k++) {
	Matrix3[k][i] += Matrix1[k][j]*Matrix2[j][i];
      }
    }
  }
}

void displayMatrix(vector <vector<int> > Matrix) {
  int MatrixRows = Matrix.size();
  int MatrixColumns = Matrix[0].size();
 
  for (int i = 0; i < MatrixRows; i++) {
    for (int j = 0; j < MatrixColumns; j++) {
      //Print contents of matrix cell                                          
      cout << Matrix[i][j] << " ";
    }
    //Jump to next line for printing                                           
    cout << "\n"; 
  }
}
                            
int main() {

  //Declare matrix-related variables
  int Matrix1Rows,Matrix2Rows,Matrix1Columns,Matrix2Columns,matrixElement;

  //Get user input to define matrix sizes
  cin >> Matrix1Rows;
  cin >> Matrix1Columns;
  cin >> Matrix2Rows;
  cin >> Matrix2Columns;

  //Declare matrix variables
  vector< vector<int> >Matrix1(Matrix1Rows, vector<int>(Matrix1Columns));
  vector< vector<int> >Matrix2(Matrix2Rows, vector<int>(Matrix2Columns));
  vector< vector<int> >Matrix3(Matrix1Columns,vector<int>(Matrix2Rows));
 
  //Loop through first matrix and fill it with user-defined values
  for (int i = 0; i < Matrix1Rows; i++) {
    for (int j = 0; j < Matrix1Columns; j++) {
      //Take user input
      cin >> matrixElement;
      //Fill matrix cell with user input
      Matrix1[i][j] = matrixElement;
    }
  }

  //Loop through second matrix and fill it with user-defined values
  for (int i = 0; i < Matrix2Rows; i++) {
    for (int j = 0; j < Matrix2Columns; j++) {
      //Take user input
      cin >> matrixElement;
      //Fill matrix cell with user input
      Matrix2[i][j] = matrixElement;
    }
  }

  //Skip a line
  cout << endl;
  
  //Display Matrix1
  displayMatrix(Matrix1);
  
  //Skip a line
  cout << endl;
  
  //Display Matrix2
  displayMatrix(Matrix2);

  //Multiply the two matricies
  // Matrix3 = multiply(Matrix1,Matrix2,Matrix3);
  
  //Display output of multiplication
  // displayMatrix(Matrix3);
  return 0;
}
