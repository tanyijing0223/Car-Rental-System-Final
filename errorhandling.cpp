#include "main.h"
#include "accounts.h"
#include "admin.h"
#include "billing.h"
#include "errorhandling.h"
#include "rentals.h"
#include "menu.h"

//check if the IC number entered is 12 digits of integers or not
bool isValidIC(const string& ic) {
    if (ic.length() != 12) return false;
    for (char c : ic) {
        if (!isdigit(c)) return false;}
    return true;
}

//check if the contact number entered is all integers or not
bool isValidContact(const string& contact) {
    for (char c : contact) {
        if (!isdigit(c)) return false;}
    return true;
}

//check if this IC number is already registered or not
bool isDuplicateIC(const string& ic) {
    ifstream file("customer.txt");
    string name, fileIC, contact, password;
    
    while (file >> name >> fileIC >> contact >> password) {
        if (fileIC == ic) {
            file.close();
            return true; }}
    file.close();
    return false;
}

//check if the date entered is in correct format or not
bool isValidDate(const string& date) {
    // 1. Check length (dd/mm/yyyy is 10 chars)
    if (date.length() != 10) return false;

    // 2. Check positions of '/'
    if (date[2] != '/' || date[5] != '/') return false;

    // 3. Check if everything else is a digit
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; 
        if (!isdigit(date[i])) return false;}

    // 4. Extract numbers to check logic
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (year < 2024) return false; // Basic check for current/future years

    return true;
}
