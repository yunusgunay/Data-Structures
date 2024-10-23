/* sec2-Yunus-Gunay-22203758 */

#include <string>
#include <iostream>
using namespace std;

#ifndef DVDSTOREMANAGEMENTSYSTEM_H_INCLUDED
#define DVDSTOREMANAGEMENTSYSTEM_H_INCLUDED

#include "Customer.h"
#include "DVD.h"
#include "Transaction.h"

class DVDStoreManagementSystem {
public:
    DVDStoreManagementSystem();
    ~DVDStoreManagementSystem();
    void addDVD( const string serialNo, const string title, const string director );
    void removeDVD( const string serialNo );
    void addCustomer( const int customerID, const string name );
    void removeCustomer( const int customerID );
    void rentDVD( const int customerID, const string serialNo );
    void returnDVD( const int customerID, const string serialNo );
    void showAllDVDs() const;
    void showAllCustomers() const;
    void showDVD( const string serialNo ) const;
    void showCustomer( const int customerID ) const;
    void showTransactionHistory() const;

private:
    DVD* dvd_array;
    int dvd_size;
    Customer* customer_array;
    int customer_size;
    Transaction* transaction_array;
    int transaction_size;
};

#endif
