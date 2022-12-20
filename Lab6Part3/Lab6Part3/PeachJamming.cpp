// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Abou Diomande
// 10/12/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include<algorithm>
#include <functional>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque; using namespace std::placeholders;

struct Peaches {
    double weight; // oz
    bool ripe;  // ripe or not
    void print() const { cout << (ripe ? "ripe" : "green") << ", " << weight << endl; }
};



int main() {
    srand(time(nullptr));
    const double minWeight = 8.;
    const double maxWeight = 3.;

    cout << "Input basket size: ";
    int size;
    cin >> size;

    vector <Peaches> basket(size);

    // assign random weight and ripeness peaches in the basket
    // replace with generate()
    /*for (auto it = basket.begin(); it != basket.end(); ++it) {
        it->weight = minWeight +
            static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        it->ripe = rand() % 2;
    }*/
    generate(basket.begin(), basket.end(), [=]() {
        Peaches p;
        p.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        p.ripe = rand() % 2;
        return p;
        });


    // for_each() possibly
    cout << "all peaches" << endl;
    /*for (const auto& e : basket) {
        e.print();
    }*/
    for_each(basket.begin(), basket.end(), [](Peaches p) {
        p.print();
        });

    // moving all the ripe peaches from basket to peck
    // remove_copy_if() with back_inserter()/front_inserter() or equivalents
    deque<Peaches> peck;
   /* for (auto it = basket.begin(); it != basket.end();)
        if (it->ripe) {
            peck.push_front(std::move(*it));
            it = basket.erase(it);
        }
        else
            ++it;*/

    remove_copy_if(basket.begin(), basket.end(), back_inserter(peck), [](Peaches p) {
        
        return p.ripe == false;
        });//come back

   
    basket.erase(remove_if(basket.begin(), basket.end(), [](Peaches& p) {
        return p.ripe == true;
        }), basket.end());
   

    // for_each() possibly
    cout << "peaches remainng in the basket" << endl;
    /*for (const auto& e : basket) {
        e.print();
    }*/
    for_each(basket.begin(), basket.end(), [](Peaches p) {
        p.print();
        });

    cout << endl;

    // for_each() possibly
    cout << "peaches moved to the peck" << endl;
    /*for (const auto& e : peck) {
        e.print();
    }*/
    for_each(peck.begin(), peck.end(), [](Peaches p) {
        p.print();
        });


    // prints every "space" peach in the peck
    const int space = 3;
    cout << "\nevery " << space << "\'d peach in the peck" << endl;

    // replace with advance()/next()/distance()
    // no explicit iterator arithmetic
    /*auto it = peck.cbegin(); int i = 1;
    while (it != peck.cend()) {
        if (i == space) {
            it->print();
            i = 0;
        }
        ++i;
        ++it;
    }*/
   // auto it = peck.cbegin();
    auto it2 = peck.cbegin();
    int dist;
    while (it2 != peck.cend()) {
        dist = distance(it2, peck.cend());
        it2->print();

        if (dist >= 3)
            advance(it2, space);
        else
            it2 = peck.cend();
   }


    const double weightToJam = 10.0;


    // putting all small ripe peaches in a jam
    // use a binder to create a functor with configurable max weight
    // accumulate() or count_if() then remove_if()

    //functor class
    class functor {
        public:
            functor(double w) {
                weightToJamMax_ = w;//constructor
            };
            double operator()  ( double jamW, Peaches p){


                if (p.weight < weightToJamMax_) {
                    jamW += p.weight;
                }
               
            return jamW;
            }
        private:
            double weightToJamMax_;
    };
    functor Jam(weightToJam);
    double jamWeight = accumulate(peck.begin(), peck.end(), 0.0, bind(Jam, _1,_2));
    cout << "Weight of jam is: " << jamWeight;

   
    //double jamWeight = 0;
    /*for (auto it = peck.begin(); it != peck.end();)
        if (it->weight < weightToJam) {
            jamWeight += it->weight;
            it = peck.erase(it);
        }
        else
            ++it;*/

}
