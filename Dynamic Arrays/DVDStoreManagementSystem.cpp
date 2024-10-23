/* sec2-Yunus-Gunay-22203758 */

#include <string>
#include <iostream>
using namespace std;

#include "DVDStoreManagementSystem.h"


DVDStoreManagementSystem::DVDStoreManagementSystem() {
    dvd_array = nullptr;
    dvd_size = 0;

    customer_array = nullptr;
    customer_size = 0;

    transaction_array = nullptr;
    transaction_size = 0;
}


DVDStoreManagementSystem::~DVDStoreManagementSystem() {
    delete[] dvd_array;
    delete[] customer_array;
    delete[] transaction_array;
}


void DVDStoreManagementSystem::addDVD( const string serialNo, const string title, const string director ) {
    for(int i = 0; i < dvd_size; i++) {
        if( dvd_array[i].getSerialNo() == serialNo ) {
            cout << "Cannot add DVD. DVD with serial number " << serialNo << " already exists." << endl;
            return;
        }
    }

    DVD* temp = dvd_array;
    dvd_array = new DVD[dvd_size + 1];
    for(int j = 0; j < dvd_size; j++) {
        dvd_array[j] = temp[j];
    }
    dvd_array[dvd_size].setSerialNo(serialNo);
    dvd_array[dvd_size].setTitle(title);
    dvd_array[dvd_size].setDirector(director);
    cout << "DVD with serial number " << serialNo << " successfully added." << endl;

    delete[] temp;
    dvd_size++;
}


void DVDStoreManagementSystem::removeDVD( const string serialNo ) {
    int removingIndex = -1;
    for(int i = 0; i < dvd_size; i++) {
        if( dvd_array[i].getSerialNo() == serialNo ){
            removingIndex = i;
            i = dvd_size;
        }
    }

    if( removingIndex == -1 ) {
        cout << "Cannot remove DVD. DVD with serial number " << serialNo << " not found." << endl;
        return;
    } else if( dvd_array[removingIndex].getIsRented() ) {
        cout << "Cannot remove DVD. DVD with serial number " << serialNo << " is currently rented by a customer." << endl;
        return;
    }

    DVD* temp = dvd_array;
    dvd_array = new DVD[dvd_size - 1];
    for(int j = 0, k = 0; j < dvd_size; j++) {
        if( j != removingIndex ) {
            dvd_array[k] = temp[j];
            k++;
        }
    }
    cout << "DVD with serial number " << serialNo << " successfully removed." << endl;

    delete[] temp;
    dvd_size--;
}


void DVDStoreManagementSystem::addCustomer( const int customerID, const string name ) {
    for(int i = 0; i < customer_size; i++) {
        if( customer_array[i].getID() == customerID ) {
            cout << "Cannot add customer. Customer with ID " << customerID << " already exists." << endl;
            return;
        }
    }

    Customer* temp = customer_array;
    customer_array = new Customer[customer_size + 1];

    for(int j = 0; j < customer_size; j++) {
        customer_array[j] = temp[j];
    }
    customer_array[customer_size].setID(customerID);
    customer_array[customer_size].setName(name);
    cout << "Customer with ID " << customerID << " successfully added." << endl;

    delete[] temp;
    customer_size++;
}


void DVDStoreManagementSystem::removeCustomer( const int customerID ) {
    bool hasRented = false;
    for(int i = 0; i < dvd_size; i++) {
        if( dvd_array[i].getLastRentedByCustomerID() == customerID && dvd_array[i].getIsRented() ) {
            hasRented = true;
            i = dvd_size;
        }
    }

    int removingIndex = -1;
    for(int i = 0; i < customer_size; i++) {
        if( customer_array[i].getID() == customerID ) {
            removingIndex = i;
            i = customer_size;
        }
    }

    if( removingIndex == -1 ) {
        cout << "Cannot remove customer. Customer with ID " << customerID << " not found." << endl;
        return;
    } else if ( hasRented ) {
        cout << "Cannot remove customer. Customer with ID " << customerID << " has rented DVDs." << endl;
        return;
    }

    Customer* temp = customer_array;
    customer_array = new Customer[customer_size - 1];
    for(int j = 0, k = 0; j < customer_size; j++) {
        if( j != removingIndex ) {
            customer_array[k] = temp[j];
            k++;
        }
    }
    cout << "Customer with ID " << customerID << " successfully removed." << endl;

    delete[] temp;
    customer_size--;
}


void DVDStoreManagementSystem::rentDVD( const int customerID, const string serialNo ) {
    bool customerExists = false;
    bool dvdExists = false;
    bool dvdAvailable = false;

    int customerIndex = -1;
    for(int i = 0; i < customer_size; i++) {
        if( customer_array[i].getID() == customerID ) {
            customerExists = true;
            customerIndex = i;
            break;
        }
    }

    int dvdIndex = -1;
    for(int j = 0; j < dvd_size; j++) {
        if( dvd_array[j].getSerialNo() == serialNo ) {
            dvdExists = true;
            if( !dvd_array[j].getIsRented() ) {
                dvdAvailable = true;
                dvdIndex = j;
            }
            break;
        }
    }

    if( !customerExists && !dvdExists ) {
        cout << "Cannot rent DVD. Customer with ID " << customerID << " and DVD with serial number " << serialNo << " not found."<< endl;
        return;
    } else if ( !customerExists ) {
        cout << "Cannot rent DVD. Customer with ID " << customerID << " not found." << endl;
        return;
    } else if ( !dvdExists ) {
        cout << "Cannot rent DVD. DVD with serial number " << serialNo << " not found." << endl;
        return;
    } else if ( !dvdAvailable ) {
        cout << "Cannot rent DVD. DVD with serial number " << serialNo << " is not available." << endl;
        return;
    }
    dvd_array[dvdIndex].setIsRented(true);
    dvd_array[dvdIndex].setLastRentedByCustomerID(customerID);
    customer_array[customerIndex].rentDVD();

    Transaction* temp = transaction_array;
    transaction_array = new Transaction[transaction_size + 1];

    for(int k = 0; k < transaction_size; k++) {
        transaction_array[k] = temp[k];
    }
    transaction_array[transaction_size] = Transaction("Rental", customerID, serialNo);
    cout << "DVD with serial number " << serialNo << " successfully rented by customer with ID " << customerID << "." << endl;

    delete[] temp;
    transaction_size++;
}


void DVDStoreManagementSystem::returnDVD( const int customerID, const string serialNo ) {
    bool customerExists = false;
    bool dvdExists = false;
    bool correctRenter = false;

    int customerIndex = -1;
    for(int i = 0; i < customer_size; i++) {
        if( customer_array[i].getID() == customerID ) {
            customerExists = true;
            customerIndex = i;
            break;
        }
    }

    int dvdIndex = -1;
    for(int j = 0; j < dvd_size; j++) {
        if( dvd_array[j].getSerialNo() == serialNo ) {
            dvdExists = true;
            if( dvd_array[j].getIsRented() && dvd_array[j].getLastRentedByCustomerID() == customerID ) {
                correctRenter = true;
                dvdIndex = j;
                break;
            }
        }
    }

    if( !customerExists && !dvdExists ) {
        cout << "Cannot return DVD. Customer with ID " << customerID << " and DVD with serial number " << serialNo << " not found." << endl;
        return;
    } else if( !customerExists ) {
        cout << "Cannot return DVD. Customer with ID " << customerID << " not found." << endl;
        return;
    } else if ( !dvdExists ) {
        cout << "Cannot return DVD. DVD with serial number " << serialNo << " not found." << endl;
        return;
    } else if ( !correctRenter ) {
        cout << "Cannot return DVD. DVD with serial number " << serialNo
             << " not rented by customer with ID " << customerID << "." << endl;
        return;
    }
    dvd_array[dvdIndex].setIsRented(false);
    dvd_array[dvdIndex].setLastRentedByCustomerID(-1);
    customer_array[customerIndex].returnDVD();

    Transaction* temp = transaction_array;
    transaction_array = new Transaction[transaction_size + 1];

    for(int k = 0; k < transaction_size; k++) {
        transaction_array[k] = temp[k];
    }
    transaction_array[transaction_size] = Transaction("Return", customerID, serialNo);
    cout << "DVD with serial number " << serialNo << " successfully returned by customer with ID " << customerID << "." << endl;

    delete[] temp;
    transaction_size++;
}


void DVDStoreManagementSystem::showAllDVDs() const {
    cout << "DVDs in the system:" << endl;
    if( dvd_size == 0 ) {
        cout << "None" << endl;
        return;
    }

    for(int i = 0; i < dvd_size; i++) {
        cout << "DVD: " << dvd_array[i].getSerialNo() << ", Title: " << dvd_array[i].getTitle()
             << ", Director: " << dvd_array[i].getDirector() << ", " << (dvd_array[i].getIsRented() ? "Rented" : "Available") << endl;
    }
}


void DVDStoreManagementSystem::showAllCustomers() const {
    cout << "Customers in the system:" << endl;
    if( customer_size == 0 ) {
        cout << "None" << endl;
        return;
    }

    for(int i = 0; i < customer_size; i++) {
        cout << "Customer: " << customer_array[i].getID() << ", Name: " << customer_array[i].getName()
             << ", DVDs Rented: " << customer_array[i].getDvdsRented() << endl;
    }
}


void DVDStoreManagementSystem::showDVD( const string serialNo ) const {
    for(int i = 0; i < dvd_size; i++) {
        if( dvd_array[i].getSerialNo() == serialNo ) {
            cout << "DVD: " << dvd_array[i].getSerialNo()
                 << ", Title: " << dvd_array[i].getTitle()
                 << ", Director: " << dvd_array[i].getDirector()
                 << ", " << (dvd_array[i].getIsRented() ? "Rented" : "Available") << endl;
            return;
        }
    }
    cout << "DVD with serial number " << serialNo << " not found." << endl;
}


void DVDStoreManagementSystem::showCustomer( const int customerID ) const {
    for(int i = 0; i < customer_size; i++) {
        if( customer_array[i].getID() == customerID ) {
            cout << "Customer: " << customer_array[i].getID()
                 << ", Name: " << customer_array[i].getName()
                 << ", DVDs Rented: " << customer_array[i].getDvdsRented() << endl;
            return;
        }
    }
    cout << "Customer with ID " << customerID << " not found." << endl;
}


void DVDStoreManagementSystem::showTransactionHistory() const {
    cout << "Transactions in the system:" << endl;
    if( transaction_size == 0 ) {
        cout << "None" << endl;
        return;
    }

    for(int i = 0; i < transaction_size; i++) {
        cout << "Transaction: " << transaction_array[i].getType()
             << ", Customer: " << transaction_array[i].getCustomerID()
             << ", DVD: " << transaction_array[i].getSerialNo() << endl;
    }
}

