#include "main.h"
#include "accounts.h"
#include "admin.h"
#include "billing.h"
#include "errorhandling.h"
#include "rentals.h"
#include "menu.h"

//Verify the identity of admin
void adminLogin() {
    string pin;
    int attempts = 3; //3 chances given
    clearScreen();
    cout << "------------------------------------" << endl;
    cout << "        ADMIN VERIFICATION          " << endl;
    cout << "------------------------------------" << endl;

    while (attempts>0){
        cout << "Enter Admin PIN (xxxx): ";
        cin >> pin;

        if (pin == "6666") {
            adminMenu();
            break;}
        else {
            attempts--;
            if (attempts > 0) {
                cout << "Wrong PIN. You have " << attempts << " attempt(s) left." << endl;
                cout << "------------------------------------" << endl;}
            else {
                cout << "0 attempts left. Access Denied!" << endl;
                cout << "------------------------------------" << endl;
                cout << "Press enter to return to the main menu..." << endl;
                cin.ignore(); cin.get();}}}
}

//Prompt for asking admin wan to add cars or not
void restock(){
    string choice, carID;
    int amount;
    cout << "\nAre you restocking any cars? (y/n):";
    cin >> choice;

    while (choice !="y" && choice !="n"){
        cout << "Invalid input! Pls enter y or n only:";
        cin >> choice;}
        
    if (choice=="y"){
        cout << "Please select carID to restock:";
        cin >> carID;
        while (carID != "1" && carID != "2" && carID != "3" && carID != "4" && carID != "5" && 
        carID != "6" && carID != "7" && carID != "8" && carID != "9" && carID != "10"){
            cout << "Invalid input! Pls enter (1-10) only:";
            cin >> carID;}
        while (true) {
            cout << "Please enter quantity to restock (e.g: to add: +2, to subtract: -2):";
            cin >> amount;
            if (cin.fail()) {
                cin.clear(); // clear error state
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                cout << "Wrong input. Please enter an INTEGER only.\n";}
            else {
                updateCarQuantity(carID,amount);
                cout << "Restock done, press enter to return to the main menu...";
                break;}}}
    else {
        cout << "Not Restocking..." << endl;
        cout << "\nPress enter to return to the main menu..." << endl;}
}

//This function can change the quantity of cars in cat.txt
void updateCarQuantity(string id, int change) {
    ifstream file("car.txt");
    vector<Car> cars;
    Car c;
    while (file >> c.id >> c.model >> c.color >> c.price >> c.gear >> c.quantity) {
        if (c.id == id) c.quantity += change;
        cars.push_back(c);}
    file.close();

    ofstream outFile("car.txt");
    for (auto const& car : cars) {
        outFile << car.id << " " << car.model << " " << car.color << " "
                << car.price << " " << car.gear << " " << car.quantity << endl;}
    outFile.close();
}