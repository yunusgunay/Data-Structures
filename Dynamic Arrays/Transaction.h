/* sec2-Yunus-Gunay-22203758 */

#include <string>
#include <iostream>
using namespace std;

#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED

class Transaction {
public:
    Transaction( string type = "", int customerID = 0, string serialNo = "" );
    string getType() const;
    int getCustomerID() const;
    string getSerialNo() const;

private:
    string type;
    int customerID;
    string serialNo;
};

#endif
