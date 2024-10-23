/* sec2-Yunus-Gunay-22203758 */

#include <string>
#include <iostream>
using namespace std;

#include "DVD.h"

DVD::DVD() : serialNo(""), title(""), director(""), isRented(false), lastRentedByCustomerId(-1) {}

void DVD::setSerialNo( const string& serialNo ) {
    this->serialNo = serialNo;
}

void DVD::setTitle( const string& title ) {
    this->title = title;
}

void DVD::setDirector( const string& director ) {
    this->director = director;
}

void DVD::setIsRented( bool status ) {
    isRented = status;
}

void DVD::setLastRentedByCustomerID( int customerID ) {
    lastRentedByCustomerId = customerID;
}

string DVD::getSerialNo() const {
    return serialNo;
}

string DVD::getTitle() const {
    return title;
}

string DVD::getDirector() const {
    return director;
}

bool DVD::getIsRented() const {
    return isRented;
}

int DVD::getLastRentedByCustomerID() const {
    return lastRentedByCustomerId;
}
