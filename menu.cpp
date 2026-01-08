#include "main.h"
#include "accounts.h"
#include "admin.h"
#include "billing.h"
#include "errorhandling.h"
#include "rentals.h"
#include "menu.h"

//to show the main menu
void mainMenu(){
    clearScreen();
        cout << "====================================" << endl;
        cout << "         CAR RENTAL SYSTEM          " << endl;
        cout << "====================================" << endl;
        cout << "1. Admin Mode\n2. Customer Mode\n3. Exit\n\nChoice: ";
}

//menu for admin to choose the functions to be executed
void adminMenu() {
    string choice;
    while (true) {
        clearScreen();
        cout << "------------------------------------" << endl;
        cout << "         [ ACCESS GRANTED ]         " << endl;
        cout << "------------------------------------" << endl;
        cout << "1. View Car Details\n2. View Customer Details\n3. View All Rental History\n4. Logout\n\nChoice: ";
        cin >> choice;

        while (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
            cout << "Invalid input! Pls enter digits (1-3): ";
            cin >> choice;}

        if (choice == "1") {
            clearScreen(); 
            viewCars(); 
            restock();
            cin.ignore(); cin.get(); }

        else if (choice == "2") {
            clearScreen();
            ifstream file("customer.txt");
            string n, i, co, p;
            cout << left << setw(15) << "NAME" << setw(15) << "IC NUMBER" << setw(15) << "CONTACT" << endl;
            cout << "---------------------------------------------" << endl;
            while (file >> n >> i >> co >> p)
                cout << left << setw(15) << n << setw(15) << i << setw(15) << co << endl;
            file.close();
            cout << "\nPress enter to return to the main menu...";
            cin.ignore(); cin.get();}

        else if (choice == "3") {
            viewAllRentals(); 
            cin.ignore(); cin.get(); }

        else break;
    }
}

//menu for customer to choose the functions to be executed
void customerMenu(Customer currentCust) {
    string choice;
    while (true) {
        clearScreen();
        cout << "------------------------------------" << endl;
        cout << "       Hello, " << currentCust.name << endl;
        cout << "------------------------------------" << endl;
        cout << "1. Rent a Car\n2. Return a Car\n3. View My History\n4. Logout\n\nChoice: ";
        cin >> choice;

        while (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
            cout << "Invalid input! Pls enter digits (1-4): ";
            cin >> choice;}

        if (choice == "1") rentCar(currentCust);
        else if (choice == "2") returnCar(currentCust);
        else if (choice == "3") { 
            viewMyRentals(currentCust);
            cin.ignore(); cin.get(); }
        else break;
    }
}

//to show the car menu in table form
void viewCars() {
ifstream file("car.txt");
    Car c;
    cout << left << setw(5)  << "ID" 
                     << setw(15) << "MODEL" 
                     << setw(10) << "COLOR" 
                     << setw(12) << "PRICE/DAY" 
                     << setw(10) << "GEAR" 
                     << setw(8)  << "STOCK" << endl;
    cout << string(60, '-') << endl; // Decorative line
    
    while (file >> c.id >> c.model >> c.color >> c.price >> c.gear >> c.quantity) {
        cout << left << setw(5)  << c.id 
             << setw(15) << c.model 
             << setw(10) << c.color 
             << "RM" << setw(10) << c.price 
             << setw(10) << c.gear 
             << setw(8)  << c.quantity << endl;}
    file.close();
}