#include <iostream>

using namespace std;

int main() {
	
	double nickelWidthMin = 0.8183;
	double nickelWidthMax = 0.8517;
	double dimeWidthMin = 0.6909;
	double dimeWidthMax = 0.7191;
	double quarterWidthMin = 0.9359;
	double quarterWidthMax = 0.9741;
	
	double nickelWeightMin = 4.95;
	double nickelWeightMax = 5.05;
	double dimeWeightMin = 2.24532;
	double dimeWeightMax = 2.29068;
	double quarterWeightMin = 5.6133;
	double quarterWeightMax = 5.7267;
	
	double width;
	double weight;
	double balance = 0.0;
	
	int tests;
	cout.precision(3);
	
	cout << "Acceptable width of a nickel is from " << nickelWidthMin << " to " << nickelWidthMax << endl;
	cout << "Acceptable width of a dime is from " << dimeWidthMin << " to " << dimeWidthMax << endl;
	cout << "Acceptable width of a quarter is from " << quarterWidthMin << " to " << quarterWidthMax << endl;
	cout << "Acceptable width of a nickel is from " << nickelWeightMin << " to " << nickelWeightMax << endl;
	cout << "Acceptable width of a dime is from " << dimeWeightMin << " to " << dimeWeightMax << endl;
	cout << "Acceptable width of a quarter is from " << quarterWeightMin << " to " << quarterWeightMax << endl;
	cout << endl;
	
	cout << "How many tests do you want to do? ";
	cin >> tests;
	
	for (int i = 0; i < tests; i++) {
		balance = 0;
		cout << "Test " << i+1 << endl;
		cout << endl;
		
		cin >> width;
		cin >> weight;
		
		while ((width != 0.0) && (weight != 0.0)) {
			if ((width >= nickelWidthMin) && (width <= nickelWidthMax) && (weight >= nickelWeightMin) && (weight <= nickelWeightMax))  {
				balance += 0.05;
			}
			else if ((width >= dimeWidthMin) && (width <= dimeWidthMax) && (weight >= dimeWeightMin) && (weight <= dimeWeightMax))  {
				balance += 0.10;
			}
			else if ((width >= quarterWidthMin) && (width <= quarterWidthMax) && (weight >= quarterWeightMin) && (weight <= quarterWeightMax))  {
				balance += 0.25;
			}
			else {
				cout << "invalid coin" << endl;
			}
			
			cin >> width;
			cin >> weight;
		}
	
		cout << "\nvalue of coins entered: $" << balance << endl;
	}
	
	
	
	return 0;
}