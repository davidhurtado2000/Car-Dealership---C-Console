#include <iostream>
#include <string>
using namespace std;

class Car {
    private:
        string make;
        string model;
        int price;
    public:
        Car(string, string, int);

        string getMake();
        string getModel();
        int getPrice();

        void setMake(string make);
        void setModel(string model);
        void setPrice(int price);
};

