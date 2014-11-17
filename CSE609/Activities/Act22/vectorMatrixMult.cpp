#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<vector<int> > matrix1;
    vector<vector<int> > matrix2;
    int row1, col1, row2, col2;
    do {
	cout << "Dimensions of matrix #1: (row col):";
	cin >> row1 >> col1;
   
	while ( row1 < 0 || col1 < 0 ) {
	    cout << "Dimensions must be positive. re-enter.\n";
	    cout << "Dimensions of matrix #1: (row col):";
	    cin >> row1 >> col1;
	}
	cout << "row1: " << row1 << " col1: " << col1 << endl;

	cout << "Dimensions of matrix #2: (row col):";
	cin >> row2 >> col2;

	while ( row2 < 0 || col2 < 0 ) {
	    cout << "Dimensions must be positive. re-enter.\n";
	    cout << "Dimensions of matrix #1: (row col):";
	    cin >> row2 >> col2;
	}
	cout << "row2: " << row2 << " col2: " << col2 << endl;
	if ( col1 != row2 ) {
	    cout << "The number of columns of the first matrix must be the same ";
	    cout << "as the number of rows of the second.\nPlease reenter all dimensions.\n";
	}
    } while ( col1 != row2 );

    int value;
    vector<int> row;

    cout << "Enter values for matrix #1:\n";

    for (int i =0; i< row1; i++) {
	for (int j=0; j<col1; j++) {
	    cin >> value;
	    row.push_back(value);
	}
	matrix1.push_back(row);
	row.clear();
    }

    cout << "Enter values for matrix #2:\n";

    for (int i =0; i< row2; i++) {
        for (int j=0; j<col2; j++) {
            cin >> value;
            row.push_back(value);
        }
        matrix2.push_back(row);
        row.clear();
    }
    vector<vector<int> > result;
    row.clear();

    for ( int i = 0; i < row1; i++ ) {
	for (int j = 0; j < col2; j++) {
	    value = 0;
	    for (int k=0; k< col1; k++) {
		value += matrix1[i][k] * matrix2[k][j];
	    }
	    row.push_back(value);
	}
	result.push_back(row);
	row.clear();
    }

    cout << "Matrix #1:\n";
    for (int i =0; i< row1; i++) {
        for (int j=0; j<col1; j++) {
            cout << matrix1[i][j] << " ";
	}
	cout << endl;
    }

    cout << "Matrix #2:\n";
    for (int i =0; i< row2; i++) {
        for (int j=0; j<col2; j++) {
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Result:\n";
    for (int i =0; i< row1; i++) {
        for (int j=0; j<col2; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}
