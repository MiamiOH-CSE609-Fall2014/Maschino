#include <iostream>
#include <string>
#include <exception>

using namespace std;
                 
class bankAccount {
 private:
  string name;
  int accountNumber;
  float accountBalance;
 public:
  string getName();
  void setName(string in);
  float getBalance();
  void setBalance(float amount);
  int getAccountNumber();
  void setAccountNumber(int number);
  void deposit(float amount);
  void withdraw(float amount);
  void printBalance();
};
