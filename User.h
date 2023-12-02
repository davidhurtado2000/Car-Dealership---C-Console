#include <iostream>
#include <string>
using namespace std;

class User {
    private:
        string name;
        int pin;

    public:
        User(string, int);

        void setName(string);
        void setPin(int);
        string getName();
        int getPin();

};