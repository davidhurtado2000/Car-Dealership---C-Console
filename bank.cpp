#include "Bank.h"
#include <iostream>
using namespace std;

Bank::Bank(string _name, int _pin, float _balance, bool _canTakeOutLoan) : User(_name, _pin) {
    balance = _balance;
    canTakeOutLoan = _canTakeOutLoan;
}

float Bank::getBalance() {
    return balance;
}

bool Bank::getLoanStatus() {
    return canTakeOutLoan;
}

void Bank::setBalance(float balance) {
    this->balance = balance;
}

void Bank::setLoanStatus(bool canTakeOutLoan) {
    this->canTakeOutLoan = canTakeOutLoan;
}