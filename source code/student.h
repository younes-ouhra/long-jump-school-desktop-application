#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <string>
using namespace std;

class Student
{
private:
    string firstName;
    string lastName;
    string birthday;
    string firstJumpStr;
    string secondJumpStr;
    double firstJump;
    double secondJump;
    int note;

public:
    Student(string firstName, string lastName, string birthday, double firstJump, double secondJump);
    Student(string firstName, string lastName, string birthday, string firstJumpStr, string secondJumpStr);
    string getFirstName() const;
    string getLastName() const;
    string getBirthday() const;
    string getFirstJumpStr() const;
    string getSecondJumpStr() const;
    double getFirstJump() const;
    double getSecondJump() const;
    int getNote() const;
    void countTheNote();
};

double replaceCommaWithPoint(string stringVar);
string replacePointWithComma(double doubleVar);

//ostream& operator << (std::ostream& out, int index, const Student& obj);
#endif
