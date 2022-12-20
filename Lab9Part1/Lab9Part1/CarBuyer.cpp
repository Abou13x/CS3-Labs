// needed for lab
// Abou Diomande
// 10/31/2022

#include <iostream>
#include <vector>
#include <cstdlib>
#include <array>
#include "CarFactory.h"

using std::vector;
using std::cout; using std::endl;

class CarLot {
public:
    CarLot();
    Car* testDriveCar() { return car4sale_; }

    // if a car is bought, requests a new one
    Car* buyCar() {
        Car* bought = &car4sale_[next];
        car4sale_[next] = *(factories_[rand() % factories_.size()]->requestCar());
        return bought;
    }
    //get the next car
    Car* nextCar() {
        ++next;
        if (next == LOT_SIZE)next = 0;
        Car* result = &car4sale_[next];
        return result;
    }
    //setting the size of the car lot
    int lotSize() { return LOT_SIZE; }

    /*void print() {
        std::cout << "Current Lot " << next << std::endl;
        for (int i = 0; i < LOT_SIZE; ++i) {
            std::cout << car4sale_[i].getMake() << " ";
            std::cout << car4sale_[i].getModel() << std::endl;
        }
        std::cout << std::endl;
    }*/

private:
    static const int LOT_SIZE = 10;
    static int next;
    Car car4sale_[LOT_SIZE]; // array of cars for sale
    vector<CarFactory*> factories_;
};
int CarLot::next = 0;


CarLot::CarLot() {
    // creates 2 Ford factories and 2 Toyota factories 
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());

    // Fill lot with random cars
    for (int i = 0; i < LOT_SIZE; ++i) {
        car4sale_[i] = *(factories_[rand() % factories_.size()]->requestCar());
    }
}

CarLot* carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id) {
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();
    //string array of toyota models
    static const std::array<std::string, 5> ModelsOfToyota = { "Corolla", "Camry", "Prius", "4Runner", "Yaris" };

    //randomly selects one of those models 
    std::string modelToBuy = ModelsOfToyota[rand() % ModelsOfToyota.size()];
    //buy will testdrive all the cars in the lot
    for (int i = 0; i < carLotPtr->lotSize(); ++i) {
        Car* toBuy = carLotPtr->nextCar();
        cout << "Buyer " << id << endl;
        cout << "test driving "
            << toBuy->getMake() << " "
            << toBuy->getModel();



        if (toBuy->getMake() == "Toyota" && toBuy->getModel()== modelToBuy) {
            cout << ", love it! buying it!" << endl;
          //  carLotPtr->buyCar();
          //  carLotPtr->print();
           //break;
        }
        else
            cout << ", did not like it!" << endl;
    }
}

// test-drives a car
// buys it if Ford
void fordLover(int id) {
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();

    //creates an array of ford models
    static const std::array<std::string, 4> modelsOfFord = { "Focus", "Mustang", "Explorer", "F-150" };
    // randomly selects one of the models form the array
    std::string modelToBuy = modelsOfFord[rand() % modelsOfFord.size()];
    //buy will testdrive all the cars in the lot
    for (int i = 0; i < carLotPtr->lotSize(); ++i) {
        Car* toBuy = carLotPtr->nextCar();
        cout << "Buyer " << id << endl;
        cout << "test driving "
            << toBuy->getMake() << " "
            << toBuy->getModel();

        if (toBuy->getMake() == "Ford" && toBuy->getModel() == modelToBuy) {
            cout << ", love it! buying it!" << endl;
            //  carLotPtr->buyCar();
            //  carLotPtr->print();
             //break;
        }
        else
            cout << ", did not like it!" << endl;
    }
}



int main() {
    srand(time(nullptr));

    const int numBuyers = 10;
    for (int i = 0; i < numBuyers; ++i)
        if (rand() % 2 == 0)
            toyotaLover(i);
        else
            fordLover(i);
}