/* sec2-Yunus-Gunay-22203758 */

#include <string>
#include <iostream>
using namespace std;

#ifndef DVD_H_INCLUDED
#define DVD_H_INCLUDED

class DVD {
public:
    DVD();
    void setSerialNo( const string& serialNo );
    void setTitle( const string& title );
    void setDirector( const string& director );
    void setIsRented( bool status );
    void setLastRentedByCustomerID( int customerID );

    string getSerialNo() const;
    string getTitle() const;
    string getDirector() const;
    bool getIsRented() const;
    int getLastRentedByCustomerID() const;

private:
    string serialNo;
    string title;
    string director;
    bool isRented;
    int lastRentedByCustomerId;
};

#endif
