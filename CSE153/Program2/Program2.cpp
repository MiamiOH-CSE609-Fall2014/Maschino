#include <iostream>
#include <math.h>

void PartA();
void PartB();

using namespace std;

int main() {
  
  	PartA();
	PartB();

	return 0;
}

void PartA() {
	int a, b, c;
	double a2b2;
	double c2;
	
	cout << "Enter three integers" << endl;
	cout << "\ta = ";
	cin >> a;
	cout << "\tb = ";
	cin >> b;
	cout << "\tc = ";
	cin >> c;
	
	a2b2 = pow(a,2) + pow(b,2);
	c2 = pow(c,2);
	
	if (a2b2 == c2) {
		cout << "\n\n" << a << "^2 + " << b << "^2 = " << c << "^2" << endl;
		cout << "The integers " << a << ", " << b << ", and " << c << " represent a Pythagorean Triple\n" << endl;
	}
	else {
		cout << "\n\n" << a << "^2 + " << b << "^2 = " << c << "^2" << endl;
		cout << "The integers " << a << ", " << b << ", and " << c << " do not represent a Pythagorean Triple\n" << endl;
	}
}

void PartB() {
	int pH;
	cout << "Enter a pH value: ";
	cin >> pH;

	if (pH < 3) {
		cout << "Solution is very acidic" << endl;
	}
	else if ((pH >= 3) && (pH < 7)) {
		cout << "Solution is acidic" << endl;
	}
	else if (pH == 7) {
		cout << "Solution is neutral" << endl;
	}
	else if ((pH > 7) && (pH < 12)) {
		cout << "Solution is alkaline" << endl;
	}
	else {
		cout << "Solution is very alkaline" << endl;
	}
}