#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;
using std::ifstream;
using std::list;
using std::getline;
using std::string;
using std::vector;
using std::move;


void readRoster(list<string>& roster, string fileName);
void printRoster(const list<list<string>>& studentEntries);

int main(int argc, char* argv[]) {

    list<list<string>> studentEntries;
    string courseName = "";

    for (int i = 1; i < argc; ++i) {

        list<string> classRoster;
        readRoster(classRoster, argv[i]);

        courseName = argv[i];
        //removing .txt from the course name
        if (courseName.substr(courseName.size() - 4) == ".txt") {
            courseName.erase(courseName.size() - 4);
        }
           


        for (const string student : classRoster) {
            bool studentExist = false;
            //only adding a student course if the student already exist in the list of students
            for (list<string>& existingStudent : studentEntries) {
                if (student == *existingStudent.begin()) {
                   
                    existingStudent.push_back(courseName);
               
                    studentExist = true;
                    break;
                }
            }
            //adding new student to the list of students
            if (studentExist == false) {
                list<string> studentList;
                studentList.push_front(student);
                
                studentList.push_back(courseName);
            
                studentEntries.push_back(move(studentList));
            }
        }
    }

    studentEntries.sort();
    printRoster(studentEntries);
    cout << endl;
}

void readRoster(list<string>& roster, string fileName) {
    ifstream course(fileName);
    string first, last;
    while (course >> first >> last) {
        roster.push_back(first + ' ' + last);
    }
        
    course.close();
}

void printRoster(const list<list<string>>& studentEntries) {
    list<list<string>> removeDropoutsStudent;
    bool dropout = false;
    cout << "All students" << endl;
    cout << "first name last name: courses enrolled " << endl;
    for (list<string> student : studentEntries) {
        auto it = student.begin();
        string studentName = *it;
       
        cout << studentName + ": ";

        ++it;
        for (it; it != student.end();) {
            if (*it != "Dropouts") {
                cout << *it << " ";
            }
           
            if (*it == "Dropouts") {
                dropout = true;
            }
            else {
                dropout = false;
            }
            ++it;
        }

        if (dropout == false) {
            removeDropoutsStudent.push_back(move(student));
        }
        cout << endl;
    }

   
    cout << endl;
    cout << endl;
    cout << "All students, dropouts removed and sorted" << endl;
    cout << "first name last name: courses enrolled " << endl;

    for (list<string> student : removeDropoutsStudent) {
        auto it = student.begin();
        string studentName = *it;

        cout << studentName + ": ";

        ++it;
        for (it; it != student.end();) {
            cout << *it << " ";
            ++it;
        }
        cout << endl;
    }

}