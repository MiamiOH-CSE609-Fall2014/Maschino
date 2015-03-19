/*Program 4: Develop a program that takes in user input for widths of coins.
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
	double nickelMin = 0.8183;
	double nickelMax = 0.8517;
	double dimeMin = 0.6909;
	double dimeMax = 0.7191;
	double quarterMin = 0.9359;
	double quarterMax = 0.9741;
	double input;
	double balance = 0.0;
	cout.precision(3);
	
	// List acceptable width ranges
	cout << "Acceptable width of a nickel is from " << nickelMin << " to " << nickelMax << endl;
	cout << "Acceptable width of a dime is from " << dimeMin << " to " << dimeMax << endl;
	cout << "Acceptable width of a quarter is from " << quarterMin << " to " << quarterMax << endl;
	cout << endl;
	
	// Get user input for coin widths
	cin >> input;
	while (input != 0.0) {

		// Add balance of a nickel, dime, or quarter, depending on entered widths
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
	
	// Display the value of the coins entered
	cout << "\nvalue of coins entered: $" << balance << endl;

	// Pause the program before exiting to show inputs/outputs
	cin.get();
	cin.get();
	
	return 0;
}