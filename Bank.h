#include "user.cpp"
#include <iostream>

using namespace std;

class Bank : public User {
    private:
        float balance;
        bool canTakeOutLoan;

    public:
        Bank(string, int, float, bool);
        float getBalance();
        bool getLoanStatus();
        void setBalance(float);
        void setLoanStatus(bool);
};

