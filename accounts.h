#ifndef accounts_h
#define accounts_h

using namespace std;

struct Customer {
    string name, ic, contact, password;};

// Function Declaration
void customerRegister();
void customerLogin();
void customerinterface();

#endif