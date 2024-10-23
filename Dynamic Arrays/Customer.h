/* sec2-Yunus-Gunay-22203758 */

#include <string>
#include <iostream>
using namespace std;

#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

class Customer {
public:
    Customer();
    void setID( const int& customerID );
    void setName( const string& name );
    void rentDVD();
    void returnDVD();

    int getID() const;
    string getName() const;
    int getDvdsRented() const;

private:
    int customerID;
    string name;
    int dvdsRented;
};

#endif

