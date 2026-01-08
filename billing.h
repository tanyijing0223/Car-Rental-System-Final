#ifndef BILLING_H
#define BILLING_H

using namespace std;

// Transaction Functions
void rentCar(Customer c);
void returnCar(Customer c);

// Date Helpers (used for late fees)
int daysBetween(string start, string end);
time_t toTime(string date);

#endif