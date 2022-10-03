// set/multiset example
// Abou Diomande
// 10/1/2022

#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using std::cout; using std::endl;
using std::cin;
using std::set;
using std::ifstream;
using std::string; using std::getline;



class Student {
public:
    Student(string firstName, string lastName) :
        firstName_(firstName), lastName_(lastName) {}

    // move constructor, not really needed, generated automatically
    Student(Student&& org) :
        firstName_(move(org.firstName_)),
        lastName_(move(org.lastName_))
    {}

    // force generation of default copy constructor
    Student(const Student& org) = default;

    string getName() const { return firstName_ + ' ' + lastName_; };

  // void addCourse(string course_name) { classes_.push_back(course_name); }

    /* void print() const {
         cout << firstName_ + ' ' + lastName_ << " ";
         for (auto& className : classes_) {
             if (className != "Dropouts") {
                 cout << className << ' ';
             }
         }

         cout << endl;
     }*/

     // needed for unique() and for remove()
    friend bool operator== (Student left, Student right) {
        return left.lastName_ == right.lastName_ &&
            left.firstName_ == right.firstName_;
    }

    // needed for sort()
    friend bool operator< (Student left, Student right) {
        return left.firstName_ < right.firstName_ ||
            (left.firstName_ == right.firstName_ &&
                left.lastName_ < right.lastName_);
    }
private:
    string firstName_;
    string lastName_;
};

// reading a list from a fileName
void readRoster(set<Student>& roster, set<Student>& dropouts, string fileName);
// printing a list out
void printRoster(const set<Student>&);
void removeDropouts(set<Student>&, set<Student>&);

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last" << endl; exit(1);
    }

    set<Student> students;
    set<Student> dropouts;
    for (int i = 1; i < argc; ++i) {
        readRoster(students, dropouts, argv[i]);

    }
    //cout << "All students" << endl;
   // printRoster(students);
    removeDropouts(dropouts, students);
    cout << endl;
    cout << endl;
    cout << "Currently enrolled students" << endl;
    printRoster(students);
    return 0;
}

void readRoster(set<Student>& roster, set<Student>& dropouts,  string fileName) {
    ifstream course(fileName);
    string first, last;
    string courseName = fileName.substr(0, fileName.size() - 4);
    while (course >> first >> last) {
        auto it = roster.find(Student(first, last));
        if (it == roster.end()){
            roster.insert(Student(first, last));
        }
        if (courseName == "Dropouts") {
            dropouts.insert(Student(first, last));
        }

    }
    course.close();
}

void printRoster(const set<Student>& roster) {
    for (auto it = roster.cbegin(); it != roster.cend(); ++it) {
        cout << it->getName();
        cout << endl;
    }
}
void removeDropouts(set<Student>& dropouts, set<Student>& roster) {
    for (auto student : dropouts) {
        auto it = roster.find(student);
        if (it != roster.end()) {
            roster.erase(it);
        }
    }
}