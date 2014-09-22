#include <iostream>

using namespace std;

void menu();

int main() {

  char selection;
  cout << "\nPlease enter a single character to make a choice from the menu." << endl;
  menu();
  while (selection != 'q') {
    cin >> selection;
    switch(selection) {
    case 'p' : cout << "\nPrinting information for existing customer..." << endl;
      menu();
      break;
    case 'a' : cout << "\nAdding information for new customer..." << endl;
      menu();      
      break;
    case 'e' : cout << "\nEditing information for existing customer..." << endl;
      menu();
      break;
    case 'd' : cout << "\nDeleting information for existing customer..." << endl;
      menu();      
      break;
    case 'q' : cout << "\nThank you for using the program. Goodbye." << endl;
      break;
    default : cout << "\nInvalid input. Please enter your selection again." << endl;
      menu();
    }
  }
}
  void menu() {
  cout << "\nMenu:" << "\n" << "'p' - print" <<  endl;
  cout << "'a' - add" << "\n'e' - edit" << endl;
  cout << "'d' - deleted" << "\n'q' - quit\n" << endl;
}
