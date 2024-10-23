/* sec2-Yunus-Gunay-22203758 */

#include <string>
#include <iostream>
using namespace std;

#include "Customer.h"

Customer::Customer() : customerID(0), name(""), dvdsRented(0) {}

void Customer::setID( const int& customerID ) {
    this->customerID = customerID;
}

void Customer::setName( const string& name ) {
    this->name = name;
}

void Customer::rentDVD() {
    dvdsRented++;
}

void Customer::returnDVD() {
    if (dvdsRented > 0)
        dvdsRented--;
}

int Customer::getID() const {
    return customerID;
}

string Customer::getName() const {
    return name;
}

int Customer::getDvdsRented() const {
    return dvdsRented;
}
