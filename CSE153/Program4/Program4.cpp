#include <iostream>

using namespace std;

int main() {
	
	double nickelMin = 0.8183;
	double nickelMax = 0.8517;
	double dimeMin = 0.6909;
	double dimeMax = 0.7191;
	double quarterMin = 0.9359;
	double quarterMax = 0.9741;
	double input;
	double balance = 0.0;
	cout.precision(3);
	
	cout << "Acceptable width of a nickel is from " << nickelMin << " to " << nickelMax << endl;
	cout << "Acceptable width of a dime is from " << dimeMin << " to " << dimeMax << endl;
	cout << "Acceptable width of a quarter is from " << quarterMin << " to " << quarterMax << endl;
	cout << endl;
	
	cin >> input;
	while (input != 0.0) {
		if ((input >= nickelMin) && (input <= nickelMax)) {
			balance += 0.05;
		}
		else if ((input >= dimeMin) && (input <= dimeMax)) {
			balance += 0.10;
		}
		else if ((input >= quarterMin) && (input <= quarterMax)) {
			balance += 0.25;
		}
		else {
			cout << "invalid coin" << endl;
		}
			
		cin >> input;
	}
	
	cout << "\nvalue of coins entered: $" << balance << endl;
	
	return 0;
}