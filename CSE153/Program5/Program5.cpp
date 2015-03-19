/*Program 5: Develop a program that takes in user input for widths of coins.
* The input is analyzed and, using decisions, computed the total sum of all
* coins entered. In the event that a coin is not a valid width, the system
* does not consider it in the final total. A '0' is used to tell the system
* to stop looping and print out the running total.
* CSE 153
* Tyler Maschino
*/

// Include external libraries
#include <iostream>

// Use the 'standard' namespace
using namespace std;

// Main function of program
int main() {
	
	// Declare necessary variables
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
	
	// List acceptable width and weight ranges
	cout << "Acceptable width of a nickel is from " << nickelWidthMin << " to " << nickelWidthMax << endl;
	cout << "Acceptable width of a dime is from " << dimeWidthMin << " to " << dimeWidthMax << endl;
	cout << "Acceptable width of a quarter is from " << quarterWidthMin << " to " << quarterWidthMax << endl;
	cout << "Acceptable weight of a nickel is from " << nickelWeightMin << " to " << nickelWeightMax << endl;
	cout << "Acceptable weight of a dime is from " << dimeWeightMin << " to " << dimeWeightMax << endl;
	cout << "Acceptable weight of a quarter is from " << quarterWeightMin << " to " << quarterWeightMax << endl;
	cout << endl;
	

	// Get user input for number of tests
	cout << "How many tests do you want to do? ";
	cin >> tests;
	
	// Loop through each test
	for (int i = 0; i < tests; i++) {

		// Reset the balance
		balance = 0;

		// Print out the test number
		cout << "Test " << i+1 << endl;
		cout << endl;
		
		// Get coin width and weight
		cin >> width;
		cin >> weight;
		
		// Add balance of a nickel, dime, or quarter, depending on entered widths
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
	
		// Display the value of the coins entered
		cout << "\nvalue of coins entered: $" << balance << endl;
	}
	
	// Pause the program before exiting to show inputs/outputs
	cin.get();
	cin.get();
	
	return 0;
}