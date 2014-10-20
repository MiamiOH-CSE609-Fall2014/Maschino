#include "bankAccount.h"
#include <iostream>
#include <exception>

using namespace std;

int main() {
  bankAccount myAccount;
  //  myAccount.name = "Tyler";
  myAccount.deposit(100);
  myAccount.printBalance();
  return 0;
}
