// demoes hashmap implementation
// Mikhail Nesterenko
// 4/15/2014

#include "HashMap.h"
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;

int main() {
    hashmap<int, int> testHash;

    cout << "Adding elements to hashmap using updated insert" << endl;
    cout << endl;
    for (int i = 1; i <= 10; ++i) {
        auto tempPair = testHash.insert(make_pair(i, (i * 10)));
        cout << "Key: " << tempPair.first->first << endl;
        cout << "Value(Using operator[]): " << testHash[i] << endl;
        cout << "Bool: " << tempPair.second << endl;
    }

    cout << endl;
    cout << "Inserting an already existing element" << endl;
    cout << endl;
    auto tempPair = testHash.insert(make_pair(2, 20));
    cout << "Key: " << tempPair.first->first << endl;
    cout << "Value(Using operator[]): " << testHash[2] << endl;
    cout << "Bool: " << tempPair.second << endl;

    cout << endl;
    cout << "Erase test" << endl;

    auto eraseTest = testHash.erase(3);
    if (eraseTest.second) {
        cout << "3 was removed" << endl;
        if (eraseTest.first != nullptr) {
            cout << "The next element is: " << eraseTest.first->second << endl;
        }
        else {
            cout << "There is no next element" << endl;
        }
    }
    else
    {
        cout << "Failed to remove 3, not found in map" << endl;
    }

    cout << endl;
    cout << "Rehash test" << endl;
    testHash.rehash(300);
    cout << "Rehash test Succesful" << endl;

}