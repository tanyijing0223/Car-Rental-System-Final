#include "main.h"
#include "accounts.h"
#include "admin.h"
#include "billing.h"
#include "errorhandling.h"
#include "rentals.h"
#include "menu.h"

//to show the rental records specifically for "that" customer in table form
void viewMyRentals(Customer c) {
    ifstream file("rental.txt");
    Rental r;
    cout << "\n--- YOUR HISTORY ---" << endl;
    cout << left
         << setw(10) << "CAR ID"
         << setw(15) << "CAR NAME"
         << setw(20) << "STATUS"
         << setw(15) << "RENT DATE"
         << setw(15) << "RETURN DATE"
         << endl;    
    while (file >> r.customerIC >> r.carID >> r.carModel >> r.status
                >> r.dateRented >> r.dateReturned >> r.days) {
        if (r.customerIC == c.ic) {
        cout << left
             << setw(10) << r.carID
             << setw(15) << r.carModel
             << setw(20) << r.status
             << setw(15) << r.dateRented
             << setw(15) << r.dateReturned
             << endl; }}
    file.close();
    cout << "Press enter to return to the main menu..."; 
}

//to show ADMIN the renal records for all customer in table form 
void viewAllRentals() {
    clearScreen();
    ifstream file("rental.txt");
    Rental r;
    cout << "\n--- ALL CUSTOMER RENTALS ---" << endl;
    cout << left
         << setw(15) << "CUSTOMER IC"
         << setw(10) << "CAR ID"
         << setw(15) << "CAR NAME"
         << setw(20) << "STATUS"
         << setw(15) << "RENT DATE"
         << setw(15) << "RETURN DATE"
         << endl;

    while (file >> r.customerIC >> r.carID >> r.carModel >> r.status
                >> r.dateRented >> r.dateReturned >> r.days) {
        cout << left
             << setw(15) << r.customerIC
             << setw(10) << r.carID
             << setw(15) << r.carModel
             << setw(20) << r.status
             << setw(15) << r.dateRented
             << setw(15) << r.dateReturned
             << endl; }
    file.close();
    cout << "\n\nPress enter to return to the main menu...";
}