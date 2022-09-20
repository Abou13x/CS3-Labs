#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_
#include <iostream>
#include "list.hpp"
#include <string>
using std::endl; using std::cout; using std::string;


template <typename T> class Collection;
template <typename T> bool equal(const Collection<T>&, const Collection<T>&);


template<typename T>
class Collection {
public:

    void add(const T& key);
    void remove(const T&);
    T last();
    void print();

  
    friend bool equal<T>(const Collection<T>& Collection1, const Collection<T>& Collection2);

private:

	node<T>* front;
};

template <typename T> 
void Collection<T>::add(const T& key) {
    node<T>* tempNode = new node<T>;
    tempNode->setData(key);
    tempNode->setNext(front);
    front = tempNode;
}

template <typename T> void Collection<T>::remove(const T& key) {

    node<T>* prev = NULL;
    node<T>* currentNode = front;
    node<T>* next;
    while (currentNode != NULL) {
        next = currentNode->getNext();
        if (currentNode->getData() == key) {
            if (prev != NULL) {
                prev->setNext(currentNode->getNext());
            }
           
            delete currentNode;
        }
        if (currentNode != NULL)
            prev = currentNode;
        currentNode = next;
    }
}

template <typename T> 
 T Collection<T>::last() {
    return front->getData();
}

template <typename T> 
void Collection<T>::print() {
    node<T>* currentNode = front;
    while (currentNode != NULL) {
        cout << currentNode->getData() <<endl;
        currentNode = currentNode->getNext();
    }
}

template <typename T>
bool equal(const Collection<T>& Collection1, const Collection<T>& Collection2) {

    node<T>* collection1 = Collection1.front;
    node<T>* collection2 = Collection2.front;

    if (collection1 == NULL && collection2 == NULL) {
        return true;
    }
    else if (collection1 != NULL && collection2 == NULL) {
        return false;
    }
    else if (collection1 == NULL && collection2 != NULL) {
        return false;
    }
    else {
        while (collection1 != NULL && collection2 != NULL) {
            if (collection1->getData() != collection2->getData()) {
                return false;
            }
            collection1 = collection1->getNext();
            collection2 = collection2->getNext();
        }

        if (collection1 != NULL && collection2 == NULL) {
            return false;
        }
        if (collection1 == NULL && collection2 != NULL) {
            return false;
        }

    }

    return true;
}

#endif