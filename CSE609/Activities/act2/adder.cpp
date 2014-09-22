#include <iostream>
int numbers;
int sum = 0;
int main() {
  std::cout << "How many numbers would you like to add? " << std::flush;
  std::cin >> numbers;
  int number [numbers];
  for (int i = 0; i < numbers; i++) {
    std::cout << "Enter next number: " << std::flush;
    std::cin >> number [i];
    sum = sum + number [i];
  }
  std::cout << "Sum of numbers: " << sum <<std::endl;
return 0;
}
