#include "main.h"
#include "accounts.h"
#include "admin.h"
#include "billing.h"
#include "errorhandling.h"
#include "rentals.h"
#include "menu.h"

//Asking customers do they have an account or not
void customerinterface(){
    clearScreen(); 
    string custChoice;
    cout << "------------------------------------" << endl;
    cout << "     Already have an account?       " << endl;
    cout << "------------------------------------" << endl;
    cout << "1. Register\n2. Login\n\nChoice: ";
    cin >> custChoice;
    while (custChoice != "1" && custChoice != "2") {
            cout << "Invalid input! Pls enter digits (1-2): ";
            cin >> custChoice;}
    if (custChoice == "1") customerRegister();
    else customerLogin();
}

//Customer register their account here
void customerRegister() {
    Customer c;
    cout << "\n------------------------------------" << endl;
    cout << "        Create your Account         " << endl;
    cout << "------------------------------------" << endl;

    //Driving license validation
    cout << "\nDo you have a valid driving license? (y/n): ";
    string lic;
    cin >> lic;
    while (lic !="y" && lic !="n"){
        cout << "Invalid input! Pls enter y or n only:";
        cin >> lic;}
    if (lic == "n") {
        cout << "\nYou must have a valid driving license to register.";
        cout << "\nPress enter to return to the main menu...";
        cin.ignore();
        cin.get();
        return;}

    //Ask for customer names
    cin.ignore(1000, '\n');
    bool validName = false;
    while (!validName) {
        cout << "Enter Name (in one word) [e.g: John, Taylor_Swift]: ";
        string input;
        getline(cin, input);
        //CHECK FOR SPACES
        if (input.find(' ') != string::npos) {
            cout << "\n[ERROR] Spaces detected! Name must be in one line with no spaces." << endl;}
        else if (input.empty()) {
            cout << "[ERROR] Name cannot be empty!\n" << endl;}
        else {
            c.name = input;
            validName = true;}
    }

    //Ask for customer IC number
    cout << "Enter IC (12 digits): ";
    cin >> c.ic;
    while (!isValidIC(c.ic)){
        cout << "\nInvalid IC. It must be exactly 12 digits.";
        cout << "\nEnter IC again (12 digits):";
        cin >> c.ic;}
    if (isDuplicateIC(c.ic)) {
        cout << "\nError: This IC is already registered!" << endl;
        cout << "You might alreay have an account" << endl;
        cout << "Press enter to return to the main menu..." << endl;
        cin.ignore();
        cin.get();
        return;}

    //Ask for customer contact number
    cout << "Enter Contact (without "-"): "; cin >> c.contact;
    while (!isValidContact(c.contact)){
        cout << "\nInvalid Contact. It must be only in digits.";
        cout << "\nEnter Contact again:";
        cin >> c.contact;}

    //Ask customer to create password for their account
    cout << "Create Password: "; cin >> c.password;
    ofstream file("customer.txt", ios::app);
    file << c.name << " " << c.ic << " " << c.contact << " " << c.password << endl;
    file.close();
    cout << "Registration Successful!";
    cin.ignore(); cin.get();}


//Customer log in to their accounts here
void customerLogin() {
    string ic, pass;
    cout << "\n------------------------------------" << endl;
    cout << "     Login into your Account        " << endl;
    cout << "------------------------------------" << endl;

    //Ask customer to enter account information
    cout << "Enter IC: "; cin >> ic;
    cout << "Enter Password: "; cin >> pass;

    ifstream file("customer.txt");
    Customer c, foundCust;
    bool found = false;
    while (file >> c.name >> c.ic >> c.contact >> c.password) {
        if (c.ic == ic && c.password == pass) {
            found = true;
            foundCust = c;
            break;}}
    file.close();

    if (found) customerMenu(foundCust);
    else { 
        cout << "\nWrong IC or Password. \nPress enter to return to the main menu..."; 
        cin.ignore(); cin.get();}
}