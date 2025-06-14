#include "student.h"
//#include <iostream>
//#include <iomanip>

Student::Student(string firstName, string lastName, string birthday, double firstJump, double secondJump)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = birthday;
    this->firstJump = firstJump;
    this->secondJump = secondJump;

    this->firstJumpStr = replacePointWithComma(firstJump);
    this->secondJumpStr = replacePointWithComma(secondJump);
}

Student::Student(string firstName, string lastName, string birthday, string firstJumpStr, string secondJumpStr)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = birthday;
    this->firstJumpStr = firstJumpStr;
    this->secondJumpStr = secondJumpStr;

    this->firstJump = replaceCommaWithPoint(firstJumpStr);
    this->secondJump = replaceCommaWithPoint(secondJumpStr);
}

string Student::getFirstName() const            {return firstName;}

string Student::getLastName() const             {return lastName;}

string Student::getBirthday() const             {return birthday;}

string Student::getFirstJumpStr() const         {return firstJumpStr;}

string Student::getSecondJumpStr() const        {return secondJumpStr;}

double Student::getFirstJump() const            {return firstJump;}

double Student::getSecondJump() const           {return secondJump;}

int Student::getNote() const                    {return note;}

void Student::countTheNote()
{
    int note1 = 0;

    if(firstJump >= 5)                                              {note1 = 1;}

    else if(firstJump >= 4.50 && firstJump <= 4.99)                 {note1 = 2;}

    else if(firstJump >= 4.00 && firstJump <= 4.49)                 {note1 = 3;}

    else if(firstJump >= 3.50 && firstJump <= 3.99)                 {note1 = 4;}

    else if(firstJump >= 3.00 && firstJump <= 3.49)                 {note1 = 5;}

    else if(firstJump < 3.00)                                       {note1 = 6;}

    int note2 = 6;

    if(secondJump > firstJump)
    {
        double improvement = (secondJump - firstJump) * 100;

        if(improvement >  50.00)                                                {note2 = 1;}

        else if(improvement > 40.00 && improvement <= 50.00)                    {note2 = 2;}

        else if(improvement > 30.00 && improvement <= 40.00)                    {note2 = 3;}

        else if(improvement > 20.00 && improvement <= 30.00)                    {note2 = 4;}

        else if(improvement > 10.00 && improvement <= 20.00)                    {note2 = 5;}

        else if(improvement >= 10.00)                                           {note2 = 6;}

        if(note2 <= note1)              {note = note2;}
        else if(note2 >= note1)         {note = note1;}
    }

    else if(secondJump <= firstJump)
    {
        note = note1;
    }
}

double replaceCommaWithPoint(string stringVar)
{
    int found = stringVar.find(',');
    if (found != std::string::npos)
    {
        stringVar.erase(found, 1);
        stringVar.insert(stringVar.begin() + found, '.');
    }

    return stod(stringVar);
}

string replacePointWithComma(double doubleVar)
{
    string str = std::to_string(doubleVar);
    int found = str.find('.');
    if (found != std::string::npos)
    {
        str.erase(found, 1);
        str.insert(str.begin() + found, ',');
    }

    int i = str.size() - 1;
    while (str[i] == '0') {
        i--;
    }
    str = str.substr(0, i + 1);

    return str;
}

/*
void Student::printStudent(int index) const
{
    cout << "Student " << index << ":\t";
    cout << left << setw(10) << this->getFirstName();
    cout << left << setw(10) << this->getLastName();
    cout << right << setw(15) << this->getBirthday();
    cout << endl;
}
*/

//std::ostream& operator << (std::ostream& out, int index, const Student& obj)
//{
//    obj.printStudent(index);
//    return out;
//}
