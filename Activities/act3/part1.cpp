#include <iostream>
#include <climits>
#include <cfloat>

int main() {
 
  std::cout << "char (" << sizeof(char) << ") " << CHAR_MIN << " to " << CHAR_MAX << std::endl;

 std::cout << "int (" << sizeof(int) << ") " << INT_MIN << " to " << INT_MAX << std::endl;

 std::cout << "long (" << sizeof(long) << ") " << LONG_MIN << " to " << LONG_MAX << std::endl;

 std::cout << "float (" << sizeof(float) << ") " << FLT_MIN << " to " << FLT_MAX << std::endl;

 std::cout << "double (" << sizeof(double) << ") " << DBL_MIN << " to " << DBL_MAX << std::endl;

 return 1;
}
