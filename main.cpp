//including files
#include "main.h"
#include "accounts.h"
#include "admin.h"
#include "billing.h"
#include "errorhandling.h"
#include "rentals.h"
#include "menu.h"

void clearScreen() { system("cls"); }

//compile prompt: g++ main.cpp accounts.cpp admin.cpp menu.cpp billing.cpp rentals.cpp errorhandling.cpp -o CarRentalSystem
int main() {
    while (true) { 
        string choice;
        mainMenu();
        cin >> choice;

        //runs ONLY if choice is NOT 1, 2, or 3
        while (choice != "1" && choice != "2" && choice != "3") {
            cout << "Invalid input! Pls enter digits (1-3): ";
            cin >> choice;}

        //Once we are here, we know choice is "1", "2", or "3"
        if (choice == "1") {
            adminLogin();}

        else if (choice == "2") {
            customerinterface();}

        else { //we know the input is 3 here
            break; /*Exit the main while(true) loop*/ }
    } 
    return 0;
}




