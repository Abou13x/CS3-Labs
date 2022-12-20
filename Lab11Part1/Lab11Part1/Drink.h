// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// 11/7/2022
#ifndef DRINK_H
#define DRINK_H
#include <string>
#include <iostream>

using std::cout; using std::endl;
using std::string; using namespace std;



//component


enum class DrinkType { small, medium, large };
//decorator
class Drink {
public:
    Drink(DrinkType type = DrinkType::small, int price = 0) :
        type_(type), price_(price) {}
    virtual int getPrice() const {
        return price_;
    }
    virtual string getName()const {
        return name_;
    }
    int getToppings() const {
        return numToppings_;
    }
    string getDrinkSize()const {
        return drinkSize_;
    }
    void addToppings() {//maybe
        ++numToppings_;
    }
    void setPrice(const int price) {
        price_ = price;
    }
    void setDrinkName(const string name) {
        name_ = name;
    }
    void setDrinkSize(const char drinkSize); 

private:
    string name_;//name of drink
    string drinkSize_;
    int numToppings_ = 1;
    int price_;
    DrinkType type_;
};

class Coffee : Drink {

    virtual int getPrice() const {
        return price_;
    }
    virtual string getName()const {
        return name_;
    }
    int getToppings() const {
        return numToppings_;
    }
    string getDrinkSize()const {
        return drinkSize_;
    }
    void addToppings() {//maybe
        ++numToppings_;
    }
    void setPrice(const int price) {
        price_ = price;
    }
    void setDrinkName(const string name) {
        name_ = name;
    }
    void setDrinkSize(const char drinkSize);

private:
    string name_;//name of drink
    string drinkSize_;
    int numToppings_ = 1;
    int price_;
    DrinkType type_;
};
void Drink::setDrinkSize(const char drinkSize) {
    if (drinkSize == 's') {
        type_ = DrinkType::small;
        drinkSize_ = "small";
        name_ = drinkSize_ + " coffee";
        price_ = 5;
    }
    else if (drinkSize == 'm') {
        type_ = DrinkType::medium;
        drinkSize_ = "medium";
        name_ = drinkSize_ + " coffee";
        price_ = 7;
    }
    else if (drinkSize == 'l') {
        type_ = DrinkType::large;
        drinkSize_ = "large";
        name_ = drinkSize_ + " coffee";
        price_ = 10;
    }
    else {
        cout << "Invalid input";
    }
}

//decorator

class Sugar : public Drink {
public:
    Sugar(Drink* drink) : drink_(drink) {}

    int getPrice()const override {
        return 1;//cost of sugar
    }
    string getName() const override {
        if (drink_->getToppings() == 1) {
            drink_->addToppings();
            return drink_->getName() + " with sugar";
        }
        else {
            drink_->addToppings();
            return drink_->getName() + ", sugar";
        }
    }
   
private:
    Drink* drink_;
};

class Cream : public Drink {
public:
    Cream(Drink* drink) : drink_(drink) {}

    int getPrice()const override {
        return 2;//cost of cream
    }
    string getName() const override {
        if (drink_->getToppings() == 1) {
            drink_->addToppings();
            return drink_->getName() + " with cream";
        }
        else {
            drink_->addToppings();
            return drink_->getName() + ", cream";
        }
    }

private:
    Drink* drink_;
};

class MilkFoam : public Drink {
public:
    MilkFoam(Drink* drink) : drink_(drink) {}

    int getPrice()const override {
        return 3;//cost of milk foam
    }
    string getName() const override {
        if (drink_->getToppings() == 1) {
            drink_->addToppings();
            return drink_->getName() + " with milk foam";
        }
        else {
            drink_->addToppings();
            return drink_->getName() + ", milk foam";
        }
    }

private:
    Drink* drink_;
};


#endif