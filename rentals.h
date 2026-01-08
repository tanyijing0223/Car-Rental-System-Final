#ifndef rentals_h
#define rentals_h

using namespace std;

struct Rental {
    string customerIC, carID, carModel, status, dateRented, dateReturned;
    int days;
};

// Function Declaration
void viewMyRentals(Customer c);
void viewAllRentals();

#endif