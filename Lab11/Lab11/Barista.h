#pragma once
#ifndef BARISTA_H
#define BARISTA_H
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include "Customer.h"
#include "Drink.h";

using std::cout; using std::endl;
using std::string; using namespace std; using std::set; using std::vector;

set <Customer*> customers;
vector <Drink*> drinks;

class Barista {
public:
	Barista(Barista* replacement = nullptr) : replacement_(replacement) {}
    //process an order
	virtual void processOrder(Customer* customer) = 0;
    void notifyCustomers() {
        //randomly preparing a drink
        int index = rand() % drinks.size();
        Drink* readyDrink = drinks[index];
        //notifying all customers
        for (auto customer : customers) {
            customer->notify(readyDrink);
        }
        //removing ready drink from the vector
        drinks.erase(drinks.begin() + index);

    }

protected:
	Barista* replacement_;
};



class Manager : public Barista {

public:
	Manager(Barista* replacement = nullptr) : Barista(replacement) {}
    void processOrder(Customer* customer) override {
        //getting the last drink from the vector that needs milk foam
        Drink* drink = drinks.back();
        drinks.pop_back();

        cout << "I'm the manager, I will process and add milk foam to your coffee" << endl;
        //adding milk foam to drink
        drink = new MilkFoam(drink);
        char topping = 'a';
        while (topping != 'd') {
            cout << "Would you like to add [s]ugar, [c]ream, milk [f]oam, or [d]one? ";
            cin >> topping;
            switch (topping)
            {
            case 's':
                drink = new Sugar(drink);
                break;

            case 'c':
                drink = new Cream(drink);
                break;

            case 'f':
                drink = new MilkFoam(drink);
                break;
            }
        }


        cout << "What is your name? ";
        string name;
        cin >> name;

        customer->setName(name);
        drink->setCustomerName(name);
        cout << drink->getCustomerName() << ", your" << drink->getName() << " it will be $" << drink->getPrice() << ", please." << endl;

        cout << "We will notify you when your order is ready!" << endl;
        drinks.push_back(drink);
        customers.insert(customer);
    }

};

class SeniorBarista : public Barista {
public:
	SeniorBarista(Barista* replacement = nullptr) : Barista(replacement) {}
    void processOrder(Customer* customer) override{

        // Getting the most recent order drink in vector
        Drink* drink = drinks.back();
        drinks.pop_back();
        cout << "I'm a senior barista, I will process your order" << endl;
        char topping = 'a';
        while (topping != 'd' && topping != 'f') {
            cout << "Would you like to add [s]ugar, [c]ream, milk [f]oam, or [d]one? ";
            cin >> topping;
            switch (topping)
            {
            case 's':
                //adding sugar
                drink = new Sugar(drink);
                break;

            case 'c':
                //adding cream
                drink = new Cream(drink);
                break;
            }
        }
        //Manager will process order with milk foam
        if (topping == 'f') {
            cout << "I cannot do milk foam as a senior barista, my manager will gladly process your order" << endl;
            drinks.push_back(drink);
            replacement_->processOrder(customer);
        }
        else {

            cout << "I will gladly process your order as a senior barista" << endl;
            cout << "What is your name? ";
            string name;
            cin >> name;

            customer->setName(name);
            drink->setCustomerName(name);
            cout << drink->getCustomerName() << ", your" << drink->getName() << " will be $" << drink->getPrice() << ", please." << endl;

            cout << "We will notify you when your order is ready!" << endl;
            drinks.push_back(drink);
            customers.insert(customer);

        }

    }

};

class JuniorBarista : public Barista {
public:
	JuniorBarista(Barista* replacement = nullptr) : Barista(replacement) {}
    void processOrder(Customer* customer) override {

        Drink* drink{};

        cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
        char drinkSize;
        cin >> drinkSize;

        switch (drinkSize)
        {
        case 'l':
            drink = new Drink(DrinkType::large);
            break;

        case 'm':
            drink = new Drink(DrinkType::medium);
            break;

        case 's':
            drink = new Drink(DrinkType::small);
            break;
        }

        cout << "Would you like to add toppings to your coffee? [y/n] ";
        char response;
        cin >> response;

        //if yes order will be process by senior barista
        if (response == 'y') {
            cout << "I'm a junior barista, I cannot process your order" << endl;
            // adding the drink to drinks vector
            drinks.push_back(drink);
            // Send to next person in chain of responsibility
            replacement_->processOrder(customer);
        }
        else {
            cout << "I'm a junior barista, I will process your order" << endl;
            cout << "What is your name? ";
            string name;
            cin >> name;

            customer->setName(name);
            drink->setCustomerName(name);
            cout << drink->getCustomerName() << ", your" << drink->getName() << " will be $" << drink->getPrice() << ", please." << endl;

            cout << "We will notify you when your order is ready!" << endl;
            drinks.push_back(drink);
            customers.insert(customer);
        }

    }
};


#endif