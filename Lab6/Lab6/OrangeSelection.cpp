// selecting oranges
// converting vectors to multimaps
// Abou Diomande
// 10/05/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety { orange, pear, apple };
vector<string> colors = { "red", "green", "yellow" };

struct Fruit {
    Variety v;
    string color; // red, green or orange
};


int main() {
    srand(time(nullptr));
  //  vector <Fruit> tree(rand() % 100 + 1);
    multimap<Variety, string> fruit;

    // random fruit and color selection
    int count = rand() % 100 + 1;
    for (int i = 0; i <= count; ++i) {
        fruit.emplace((static_cast<Variety>(rand() % 3)), colors[rand() % 3]);
    }
 
    // printing colors of oranges
    cout << "Colors of the oranges: ";
    for (auto i = fruit.lower_bound(Variety::orange); i != fruit.upper_bound(Variety::orange); ++i) {
        cout << i->second << ", ";
    }
    cout << endl;

}
