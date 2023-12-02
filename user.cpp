#include "User.h"
#include <iostream>

using namespace std;

User::User(string name, int pin) : name(name), pin(pin) {
}
    void User::setName(string name) {
        this->name = name;
    }

    void User::setPin(int pin) {
        this->pin = pin;
    }

    string User::getName() {
        return name;
    }

    int User::getPin() {
        return pin;
    }