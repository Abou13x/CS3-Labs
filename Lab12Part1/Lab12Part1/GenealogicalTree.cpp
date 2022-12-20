// traversing genealogical tree using Composite and Visitors
// Mikhail Nesterenko
// 11/17/2022

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::cin; using std::endl;
using std::string;
using std::vector;
using namespace std;


class Person { // component
public:
    Person(string firstName, Person* spouse, Person* father, Person* mother) :
        firstName_(firstName), spouse_(spouse), father_(father), mother_(mother) {}
    const string& getFirstName() { return firstName_; }
    Person* getSpouse() { return spouse_; }
    void setSpouse(Person* spouse) { spouse_ = spouse; }
    Person* getFather() { return father_; }
    Person* getMother() { return mother_; }
    virtual void accept(class PersonVisitor*) = 0;
    virtual ~Person() {}
private:
    const string firstName_;
    Person* spouse_;
    Person* father_;
    Person* mother_;
};


// leaf
// man has a last name 
class Man : public Person {
public:
    Man(string lastName, string firstName, Person* spouse,
        Person* father, Person* mother) :
        lastName_(lastName),
        Person(firstName, spouse, father, mother) {}
    const string& getLastName() const { return lastName_; }
    void accept(class PersonVisitor* visitor) override;
private:
    const string lastName_;
};

// composite
// woman has a list of children
class Woman : public Person {
public:
    Woman(vector<Person*> children,
        string firstName,
        Person* spouse,
        Person* father, Person* mother) :
        children_(children),
        Person(firstName, spouse, father, mother) {}
    const vector<Person*>& getChildren() const { return children_; }
    void setChildren(const vector<Person*>& children) { children_ = children; }
    void accept(class PersonVisitor* visitor) override;
private:
    vector<Person*> children_;
};

// abstract visitor
class PersonVisitor {
public:
    virtual void visit(Man*) = 0;
    virtual void visit(Woman*) = 0;
    virtual ~PersonVisitor() {}
};

// composite methods that define traversal
void Man::accept(PersonVisitor* visitor) {
    visitor->visit(this);
}

void Woman::accept(PersonVisitor* visitor) {
    // children traversal through mother only
    // father's children are not traversed so as not 
    // to traverse them twice: for mother and father

    visitor->visit(this);

    // traversing descendants
    for (auto child : children_)
        child->accept(visitor);
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter : public PersonVisitor {
public:
    void visit(Man* m) override {
        cout << m->getFirstName() << " " << m->getLastName() << endl;
    }
    void visit(Woman* w) override {
        cout << w->getFirstName() << " ";
        if (w->getSpouse() != nullptr)
            cout << static_cast<Man*>(w->getSpouse())->getLastName();
        else if (w->getFather() != nullptr)
            cout << static_cast<Man*> (w->getFather())->getLastName();
        else
            cout << "Doe";
        cout << endl;
    }
};


class ChildrenPrinter : public PersonVisitor {
public:
    void visit(Man* m) override {
        cout << m->getFirstName() << ": ";
        Woman* spouse = static_cast<Woman*>(m->getSpouse());
        if (spouse != nullptr)
            printNames(spouse->getChildren());
        cout << endl;
    }
    void visit(Woman* w) override {
        cout << w->getFirstName() << ": ";
        printNames(w->getChildren());
        cout << endl;
    }
private:
    void printNames(const vector<Person*>& children) {
        for (const auto c : children)
            cout << c->getFirstName() << ", ";
    }
};

class lookUpPersonVisitor : public PersonVisitor {
public:
    lookUpPersonVisitor(string firstName1, string lastName1, string firstName2, string lastName2) :
         firstName1_(firstName1), lastName1_(lastName1), firstName2_(firstName2), lastName2_(lastName2){}

    void visit(Woman* w) override{
        string wLastName = "";
        if (w->getFirstName() == firstName1_) {
            if (w->getSpouse() != nullptr) {
                wLastName = static_cast<Man*>(w->getSpouse())->getLastName();
            }
            else if (w->getFather() != nullptr) {
                wLastName = static_cast<Man*>(w->getFather())->getLastName();
            }
            else {
                wLastName = "Doe";
            }
            if (wLastName == lastName1_) {
                person1 = w;
                foundPerson1_ = true;
                return;
            }
        }
        

        if (w->getFirstName() == firstName2_) {
            if (w->getSpouse() != nullptr) {
                wLastName = static_cast<Man*>(w->getSpouse())->getLastName();
            }
            else if (w->getFather() != nullptr) {
                wLastName = static_cast<Man*>(w->getFather())->getLastName();
            }
            else {
                wLastName = "Doe";
            }
            if (wLastName == lastName2_) {
                person2 = w;
                foundPerson2_ = true;
            }
        }
        
     
    }

    void visit(Man* m) override {
        if (m->getFirstName() == firstName1_ && m->getLastName() == lastName1_) {
            person1 = m;
            foundPerson1_ = true;
            return;
        }
        if (m->getFirstName() == firstName2_ && m->getLastName() == lastName2_) {
            person2 = m;
            foundPerson2_ = true;
        }
    }

    bool isRelated() {
                if(foundPerson1_ && foundPerson2_){

                    //both are the same person
                    if (person1 == person2) {
                        return true;
                    }
                    //parent-child relationship
                    if (person1->getMother() == person2 || person1->getFather() == person2) {
                        return true;
                    }
                    if (person2->getMother() == person1 || person2->getFather() == person1) {
                        return true;
                    }

                    //Aunts and Uncle relationship
                    Woman* mother = static_cast<Woman*>(person1->getMother());
                    if (mother != nullptr) {
                        if (mother->getMother() != nullptr) {
                            Woman* grandMother = static_cast<Woman*>(mother->getMother());
                            vector<Person*> auntsAndUncles = grandMother->getChildren();
                            for (Person* person : auntsAndUncles) {
                                if (person2 == person) {
                                    return true;
                                }
                            }
                        }
                    }
                    //sibilings 
                    if (person1->getMother() == person2->getMother()) {
                        return true;
                    }

                    return false;
                }
                else {
                    return false;
                }
          
    }

  
private:
    const string firstName1_;
    const string lastName1_;
    const string firstName2_;
    const string lastName2_;
    Person* person1 = nullptr;
    Person* person2 = nullptr;
    bool foundPerson1_ = false;
    bool foundPerson2_ = false;
};


// demonstrating the operation
int main() {

    // setting up the genealogical tree      
    // the tree is as follows
    //    
    //
    //       James Smith  <--spouse-->   Mary 
    //	                                  |
    //	                                 children -------------------------
    //	                                  |              |                |
    //	                                  |              |                |
    //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
    //	                                  |
    //	                                 children------------
    //	                                  |                 |
    //                                     |                 |
    //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
    //	       |
    //	     children
    //	       |
    //          |
    //	     Susan


    // first generation
    Man* js = new Man("Smith", "James", nullptr, nullptr, nullptr);
    Woman* ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
    ms->setSpouse(js); js->setSpouse(ms);

    // second generation
    Woman* ps = new Woman({}, "Patricia", nullptr, js, ms);
    Man* wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
    ps->setSpouse(wj); wj->setSpouse(ps);

    vector<Person*> marysKids = { ps,
                       new Man("Smith", "Robert", nullptr, js, ms),
                       new Woman({}, "Linda", nullptr, js, ms) };
    ms->setChildren(marysKids);

    // third generation
    Man* mj = new Man("Johnson", "Michael", nullptr, wj, ps);
    vector<Person*> patsKids = { mj, new Woman({}, "Barbara", nullptr, wj, ps) };
    ps->setChildren(patsKids);

    Woman* jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
    vector<Person*> jensKids = { new Woman({}, "Susan", nullptr, mj ,jj) };

    jj->setSpouse(mj); mj->setSpouse(jj);
    jj->setChildren(jensKids);


    // defining two visitors
    ChildrenPrinter* cp = new ChildrenPrinter;
    NamePrinter* np = new NamePrinter;

    // executing the traversal with the composite
    // and the specific visitor

    /*
    cout << "\nNAME LIST\n";
    ms->accept(np);
    cout << endl << endl;


    cout << "CHILDREN LIST\n";
    ms->accept(cp);
    */

    cout << "\nJAMES' CHILDREN\n";
    js->accept(cp);

    //lookup relative main code

    cout << "Enter first candidate: ";
    string firstPerson;
    getline(cin, firstPerson);

    cout << "Enter second candidate: ";
    string secondPerson;
    getline(cin, secondPerson);

    string firstName1 = firstPerson.substr(0, firstPerson.find(' '));
    string lastName1 = firstPerson.substr(firstPerson.find(' ') + 1, firstPerson.length());
    string firstName2 = secondPerson.substr(0, secondPerson.find(' '));
    string lastName2 = secondPerson.substr(secondPerson.find(' ') + 1, secondPerson.length());


    lookUpPersonVisitor* lookup1 = new lookUpPersonVisitor(firstName1, lastName1, firstName2, lastName2);

    ms->accept(lookup1);
  
    if (lookup1->isRelated() == true) {
        cout << "They are close relatives." << endl;
    }
    else {
        cout << "They are just friends." << endl;
    }

}