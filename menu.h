#ifndef menu_h
#define menu_h

using namespace std;

void mainMenu();
void adminMenu();
void customerMenu(Customer currentCust);
void viewCars();

struct Car {
    string id, model, color, gear;
    double price;
    int quantity;
};

#endif