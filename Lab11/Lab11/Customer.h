#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <iostream>
#include <set>
#include "Drink.h";

using std::cout; using std::endl;
using std::string; using namespace std; using std::set;

class Customer {

public:
    void notify(Drink* readyDrink) {

        if (readyDrink->getCustomerName() == name_) {
            cout << readyDrink->getCustomerName() << ", your" << readyDrink->getName() << "is ready!" << endl;
        }

    }
	void setName(string name) { name_ = name; }
private:
	string name_;
};

#endif