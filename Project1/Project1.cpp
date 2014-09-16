#include <iostream>
#include <vector>

//Use the standard namespace
using namespace std;

//Set up prototype functions 
vector <vector <int> > multiply(vector <vector <int> > Matrix1, vector <vector <int> > Matrix2);
void displayMatrix(vector <vector <int> > Matrix);

//Main function                           
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

  //Multiply the two matrices
  Matrix3 = multiply(Matrix1,Matrix2);
  
  //Display output of multiplication
  displayMatrix(Matrix3);
  return 0;
}

//Matrix multiplication function
vector< vector <int> > multiply(vector <vector <int> > Matrix1, vector <vector <int> > Matrix2) {
  
  //Declaration of function-level variables
  int m1rows,m1columns,m2rows,m2columns;

  //Skip a line
  cout << endl;
  
  //Fill function-level variables
  m1rows = Matrix1.size();
  m1columns = Matrix1[0].size();
  m2rows = Matrix2.size();
  m2columns = Matrix2[0].size();
  
  //Declare and size the output matrix
  vector< vector <int> > Matrix3(m1rows,vector <int>(m2columns));
 
  //Loop through the two matrices to multiply them and store
  //the result in the output matrix
  for (int i = 0; i < m2columns; i++) {
    for (int j = 0; j < m2rows; j++) {
      for (int k = 0; k < m1rows; k++) {
	Matrix3[k][i] += Matrix1[k][j]*Matrix2[j][i];
      }
    }
  }
  //Return the output matrix
  return Matrix3;
}

//Display matrix function
void displayMatrix(vector <vector<int> > Matrix) {
 
  //Declare and fill function-level variables
  int MatrixRows = Matrix.size();
  int MatrixColumns = Matrix[0].size();
 
  //Loop through matrix to display contents element by element
  for (int i = 0; i < MatrixRows; i++) {
    for (int j = 0; j < MatrixColumns; j++) {
      //Print contents of matrix cell                                          
      cout << Matrix[i][j] << " ";
    }
    //Jump to next line for printing                                           
    cout << "\n"; 
  }
}
