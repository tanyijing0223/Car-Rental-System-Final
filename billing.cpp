#include "main.h"
#include "accounts.h"
#include "admin.h"
#include "billing.h"
#include "errorhandling.h"
#include "rentals.h"
#include "menu.h"

//Big function of customer renting car here
void rentCar(Customer c) {
    clearScreen();

    //show car menu to the customer
    viewCars();
    string carID;

    //customer selects a car that he/she is interested to rent
    cout << "\nSelect your preferred car to rent (enter Car ID): "; cin >> carID;
    while (carID != "1" && carID != "2" && carID != "3" && carID != "4" && carID != "5" && 
        carID != "6" && carID != "7" && carID != "8" && carID != "9" && carID != "10"){
            cout << "Invalid input! Pls enter (1-10) only:";
            cin >> carID;}

    //check if the car selected have stocks or not
    ifstream file("car.txt");
    Car car;
    bool found = false;
    while (file >> car.id >> car.model >> car.color >> car.price >> car.gear >> car.quantity) {
        if (car.id == carID) { found = true; break; }}
    file.close();
    if (!found || car.quantity <= 0) {
        cout << "\nThis car is currently out of stock!"; 
        cout << "\nPress enter to return to the main menu..."; 
        cin.ignore(); cin.get(); return;}

    //check if the customer rent the SAME CAR MODEL without returning the previous car yet
    ifstream checkFile("rental.txt");
    Rental tempR;
    bool alreadyRented = false;
    while (checkFile >> tempR.customerIC >> tempR.carID >> tempR.carModel >> tempR.status >> tempR.dateRented >> tempR.dateReturned >> tempR.days) {
        if (tempR.customerIC == c.ic && tempR.carID == carID && tempR.status == "Not_Yet_Returned") {
            alreadyRented = true;
            break;}}
    checkFile.close();

    if (alreadyRented) {
        cout << "\n[ERROR] You are currently renting this car model!" << endl;
        cout << "You must return it before renting the same model again." << endl;
        cout << "\nPress enter to return to the menu...";
        cin.ignore(); cin.get();
        return;}
    
    //renting process starts here
    string dateR;
    int days;
    cout << "\nEnter Date Rented (dd/mm/yyyy): "; cin >> dateR;

    while (!isValidDate(dateR)) {
        cout << "[ERROR] Invalid format! Please use dd/mm/yyyy (e.g., 01/01/2024): ";
        cin >> dateR;}

    cout << "How many days are you renting? ";
    cin >> days;
    // While the input fails OR the number is not logical (0 or less)
    while (days <= 0) {
        cout << "[ERROR] Invalid input! Please enter a positive number: ";
        cin >> days;}
    
    //ask for add-ons
    double addOnTotal = 0;
    string opt;
    cout << "--------------------" << endl;
    cout << "Add Ons (Optional)"<< endl;
    cout << "--------------------" << endl;
    cout << "Add Insurance (RM20)? (y/n): "; cin >> opt;
    while (opt !="y" && opt !="n"){
        cout << "Invalid input! Pls enter y or n only:";
        cin >> opt;}
    if (opt == "y") addOnTotal += 20;
    cout << "Add Child Seat (RM15)? (y/n): "; cin >> opt;
    while (opt !="y" && opt !="n"){
        cout << "Invalid input! Pls enter y or n only:";
        cin >> opt;}
    if (opt == "y") addOnTotal += 15;

    double rentTotal = car.price * days;
    double deposit = 100;
    
    //check out starts here
    clearScreen();
    cout << "------------------------------------" << endl;
    cout << "          RENTAL BILLING            " << endl;
    cout << "------------------------------------" << endl;
    cout << "Customer:      " << c.name << endl;
    cout << "Car Rented:    " << car.model << endl;
    cout << "Date Rented:   " << dateR << endl;
    cout << "------------------------------------" << endl;
    cout << "Rental Fee:    RM " << rentTotal << endl;
    cout << "Add-ons:       RM " << addOnTotal << endl;
    cout << "Deposit:       RM " << deposit << " (Refundable)" << endl;
    cout << "------------------------------------" << endl;
    cout << "TOTAL TO PAY:  RM " << (rentTotal + addOnTotal + deposit) << endl;
    cout << "------------------------------------" << endl;
    cout << "Confirm Transaction? (y/n): "; cin >> opt;
    while (opt !="y" && opt !="n"){
        cout << "Invalid input! Pls enter y or n only:";
        cin >> opt;}

    if (opt == "y") {
        ofstream rFile("rental.txt", ios::app);
        rFile << c.ic << " " << carID << " " << car.model << " " << " Not_Yet_Returned " << dateR << " N/A " << days << endl;
        rFile.close();
        updateCarQuantity(carID, -1); // From Admin.h
        cout << "\nCar Rented Successfully!";}

    else{
        cout << "\nTransaction Cancelled. Press enter to return to the main menu..."; }
    cin.ignore(); cin.get();
}

//Customer return the cars they have rented
void returnCar(Customer c) {
    clearScreen();
    ifstream file("rental.txt");
    vector<Rental> rentals;
    Rental r;
    bool foundAny = false;

    //show the cars they haven't return yet only
    cout << "--- YOUR ACTIVE RENTALS ---" << endl;
    cout << "--------------------------------" << endl;
    cout << left << setw(10) << "CAR ID" << setw(15) << "CAR MODEL" << setw(15) << "DATE RENTED" << endl;

    while (file >> r.customerIC >> r.carID >> r.carModel >> r.status >> r.dateRented >> r.dateReturned >> r.days) {
        if (r.customerIC == c.ic && r.status == "Not_Yet_Returned") {
            cout << left
                 << setw(10) << r.carID
                 << setw(15) << r.carModel
                 << setw(15) << r.dateRented << endl;
            foundAny = true;}
        rentals.push_back(r);}
    file.close();

    if (!foundAny) {
        cout << "No cars to return."; cin.ignore(); cin.get(); return;}

    //returning process starts here
    string returnID, dateRet;
    cout << "\nEnter Car ID to return: "; cin >> returnID;
    bool carFound = false; // 1. Create a flag
    
    //ask for customer return date
    for (auto &rec : rentals) {
        if (rec.customerIC == c.ic && rec.carID == returnID && rec.status == "Not_Yet_Returned") {
            carFound = true;
            cout << "Enter Today's Date (dd/mm/yyyy): "; cin >> dateRet;
            while (!isValidDate(dateRet)) {
        cout << "[ERROR] Invalid format! Please use dd/mm/yyyy (e.g., 01/01/2024): ";
        cin >> dateRet;}
        
        //count if there is a late return or not
        int actualDays = daysBetween(rec.dateRented, dateRet);
        int lateDays = actualDays - rec.days;

        if (lateDays > 0) {
            cout << "Late for " << lateDays << " days. Charge: RM " << lateDays * 20 << endl;} 
        else {
            cout << "Returned on time." << endl;}

        rec.status = "Returned";
        rec.dateReturned = dateRet;
        updateCarQuantity(returnID, 1);
        cout << "\nCar Returned! Deposit of RM100 Refunded." << endl;
        cout << "\nThank you for choosing us." << endl;
        cout << "\nPress enter to return to menu..." << endl;
        break;}
    }

    //if customer enter a random car id which he/she didn't rent that car
    if (!carFound) {
        cout << "\nInvalid Car ID! You do not have an active rental with ID: " << returnID << endl;
        cout << "Press enter to return to menu...";
        cin.ignore(); cin.get();
        return; // Exit the function without rewriting the file
    }

    ofstream outFile("rental.txt");
    for (auto const& rec : rentals) {
        outFile << rec.customerIC << " " << rec.carID << " " << rec.carModel << " " << rec.status << " " 
                << rec.dateRented << " " << rec.dateReturned << " " << rec.days << endl;}
    outFile.close();
    cin.ignore(); cin.get();
}

//function to calculates the differences between two date strings
int daysBetween(string start, string end) {
    time_t d1 = toTime(start);
    time_t d2 = toTime(end);
    return difftime(d2, d1) / (60 * 60 * 24);
}

//Converts the date string entered by user to something that system can perform date operations
time_t toTime(string date) {
    tm t = {};
    t.tm_mday = stoi(date.substr(0, 2));
    t.tm_mon  = stoi(date.substr(3, 2)) - 1;
    t.tm_year = stoi(date.substr(6, 4)) - 1900;
    return mktime(&t);
}