#include "bankAccount.h"
#include <string>
#include <iostream>
#include <exception>

using namespace std;

void bankAccount::deposit(float amount) {
  accountBalance += amount;
}
void bankAccount::withdraw(float amount) {
  // try {
    if (amount > accountBalance) {
      //      throw invalid_argument("Overdraw error. Session terminated.");
    }
    else {
      setBalance(accountBalance-amount);
    }
    // }
  // catch(invalid_argument e) {
  // cout << e.what() << endl;
    // }
}

void bankAccount::printBalance() {
  cout << "Hi " << getName() << "." << endl;
  cout << "Your account balance is: $" << getBalance() << endl;
}

float bankAccount::getBalance() {
  return accountBalance;
}

void bankAccount::setBalance(float balance) {
  accountBalance = balance;
}

int bankAccount::getAccountNumber() {
  return accountNumber;
}

void bankAccount::setAccountNumber(int num) {
  accountNumber = num;
}

string bankAccount::getName() {
  return name;
}

void bankAccount::setName(string in) {
  name = in;
}

