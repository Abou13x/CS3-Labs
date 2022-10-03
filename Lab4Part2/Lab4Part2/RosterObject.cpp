// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


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

    void addCourse(string course_name) { classes_.push_back(course_name); }

    void print(int printNumber) const {
      
        if (printNumber == 1) {

            cout << firstName_ + ' ' + lastName_ << ": ";
            for (auto& className : classes_) {

                if (!(className == "Dropouts")) {
                    cout << className << ' ';
                }

            }
            cout << endl;
        }
      
        if (printNumber == 2) {
          
            bool dropout = false;
            string classes = "";
            int count = 0;
           
            //removes dropouts
            for (auto& className : classes_) {
                if (className != "Dropouts") {
                    dropout = false;
                    classes += className + " ";
                }
                else {
                    dropout = true;
                }
            }
            if (dropout == false) {
                cout << firstName_ + ' ' + lastName_ << ": ";
                cout << classes;
                cout << endl;
            }
        }
       
    }

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
    list<string> classes_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);
// printing a list out
void printRoster(const list<Student>& roster);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last" << endl; exit(1);
   }

    // vector of courses of students
    list<Student> courseStudents;
    for (int i = 1; i < argc; ++i) {
        readRoster(courseStudents, argv[i]);
     
    }
    courseStudents.sort();
    printRoster(courseStudents);

    return 0;

}


void readRoster(list<Student>& roster, string fileName) {
    ifstream course(fileName);
    string first, last;
    string courseName = fileName.substr(0, fileName.size() - 4);
    bool foundStudent = false;
    while (course >> first >> last) {
        for (auto& student : roster)
          
            if (student.getName() == first + " " + last) {
                foundStudent = true;
                student.addCourse(courseName);
            }

        if (!foundStudent) {
            Student newStudent(first, last);
            newStudent.addCourse(courseName);
            roster.push_back(newStudent);
        }

        foundStudent = false;
    }
    course.close();

}

// printing a list out
void printRoster(const list<Student>& roster) {
    cout << "All students" << endl;
    cout << "first name last name: courses enrolled " << endl;
    for (const auto& student : roster) {
        student.print(1);
        
    }

    cout << endl;
    cout << endl;
    cout << "All students, dropouts removed and sorted" << endl;
    cout << "first name last name: courses enrolled " << endl;
    for (const auto& student : roster) {
        student.print(2);
    }
        
}