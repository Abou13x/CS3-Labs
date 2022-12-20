// drink class to be used in Coffee Shack lab
#ifndef DRINK_H
#define DRINK_H
#include <string>
#include <iostream>

using std::cout; using std::endl;
using std::string; using namespace std;

enum class DrinkType { small, medium, large };
//component
class Drink {
public:
    Drink(DrinkType type = DrinkType::small, int price = 0) :
        type_(type), price_(price) {
        //initializing drink variables
        switch (type_)
        {
        case DrinkType::large:
            drinkSize_ = " large coffee";
            largeDrinkPrice_ = 10;
            break;

        case DrinkType::medium:
            drinkSize_ = " medium coffee";
            mediumDrinkPrice_ = 7;
            break;

        case DrinkType::small:
            drinkSize_ = " small coffee";
            smallDrinkPrice_ = 5;
            break;
        }
    }
    //returning the price of an order
    virtual int getPrice() const {
        switch (type_)
        {
        case DrinkType::large:
            return largeDrinkPrice_;
            break;

        case DrinkType::medium:
            return mediumDrinkPrice_;
            break;

        case DrinkType::small:
            return smallDrinkPrice_;
            break;
        }
    }
    //returning the size of + topings of an order
    virtual string getName()const {
        return drinkSize_;
    }
    //returning the name of a customer
    string getCustomerName() const {
        return customerName_;
    }
    void setCustomerName(string name) {
        customerName_ = name;
    }
   
    
private:
    string customerName_;
    string drinkSize_;
    int largeDrinkPrice_;
    int smallDrinkPrice_;
    int mediumDrinkPrice_;
    int price_;
    DrinkType type_;
};



//sugar decorator
class Sugar : public Drink {
public:
    Sugar(Drink* drink) : drink_(drink) {}

    int getPrice()const override {
        return drink_->getPrice() + 1;//cost of sugar
    }
    string getName() const override {
        return drink_->getName() + " sugar ";
    }

private:
    Drink* drink_;
};
//cream decorator
class Cream : public Drink {
public:
    Cream(Drink* drink) : drink_(drink) {}

    int getPrice()const override {
        return drink_->getPrice() +  2;//cost of cream
    }
    string getName() const override {
        return drink_->getName() + " cream ";
    }

private:
    Drink* drink_;
};

//Milk Foam decorator
class MilkFoam : public Drink {
public:
    MilkFoam(Drink* drink) : drink_(drink) {}

    int getPrice()const override {
        return drink_->getPrice() + 3;//cost of milk foam
    }
    string getName() const override {
        return drink_->getName() + " milk foam ";
    }

private:
    Drink* drink_;
};


#endif