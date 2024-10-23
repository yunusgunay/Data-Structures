/* sec2-Yunus-Gunay-22203758 */

#include <string>
#include <iostream>
using namespace std;

#include "Transaction.h"

Transaction::Transaction( const string type, int customerID, const string serialNo )
    : type(type), customerID(customerID), serialNo(serialNo) {}

string Transaction::getType() const {
    return type;
}

int Transaction::getCustomerID() const {
    return customerID;
}

string Transaction::getSerialNo() const {
    return serialNo;
}
