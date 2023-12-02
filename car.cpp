#include "Car.h"
#include <iostream>

using namespace std;

Car::Car(string make, string model, int price) : make(make), model(model), price(price) {
}
string Car::getMake() {
    return make;
}

string Car::getModel() {
    return model;
}

int Car::getPrice() {
    return price;
}

void Car::setMake(string make) {
    this->make = make;
}

void Car::setPrice(int price) {
    this->price = price;
}

