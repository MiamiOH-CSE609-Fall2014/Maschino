#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <stdio.h>

using namespace std;

double price;
double originalPrice;
double tax = 0.0625;

int taxOnValueCPP();
int taxOnValueC();

int main() {
  int z;
  cin >> z;
  if (z == 0) {
    return  taxOnValueCPP();
  }
  else if (z == 1) {
    return taxOnValueC();
  }
}

int taxOnValueCPP() {
 try {
      cout << "Enter the price: $";
      cin >> originalPrice;
      if (!cin) {
	throw invalid_argument("You must enter a number. Try again later.");
      }
      else {
	price = (tax+1)*originalPrice;
	

	int temp = int(price);
	int digits = 0;
	while (temp > 1) {
	    temp = temp/10;
	    digits++;
	}
	cout << "The original price was:  $" << originalPrice << endl;
	cout << "The tax rate is: " << tax*100 << "%" << endl;
	cout << "The total tax is: $" << setprecision(digits + 1) << tax*originalPrice << endl;
	cout << "The total cost is: $" << setprecision(digits + 3) << price << endl;
	return 0;
      }
   }
  catch (invalid_argument err) {
    cout << err.what() << endl;
  }
}

int taxOnValueC() {

  try {
    printf("Enter the price: $");
      cin >> originalPrice;
      if (!cin) {
	throw invalid_argument("You must enter a number. Try again later.");
      }
      else {
	price = (tax+1)*originalPrice;
	

	int temp = int(price);
	int digits = 0;
	while (temp > 1) {
	    temp = temp/10;
	    digits++;
	}
	tax = tax*100;

	printf("The original price was:  $%4.2f\n", originalPrice);
	printf("The tax is: %4.2f%%\n", tax);
	printf("The total tax is: $%4.2f\n", tax*originalPrice/100);
	printf("The total cost is: $%4.2f\n", price);
	return 0;
      }
   }
  catch (invalid_argument err) {
    cout << err.what() << endl;
  }
}