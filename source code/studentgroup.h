#ifndef STUDENTGROUP_H
#define STUDENTGROUP_H

#include "student.h"
#include <QTableWidgetItem>

class StudentGroup
{
    private:
        const int capacity;
        int sizeOfStudents;
        int sizeOfItems;
        Student** arrayOfStudents;
        QTableWidgetItem** arrayOfItems;
        string firstWinner;
        string secondWinner;

    public:
        StudentGroup();
        ~StudentGroup();
        int getSizeOfStudents() const;
        string getFirstWinner() const;
        string getSecondWinner() const;
        Student* getStudent(int index) const;
        void addStudent(Student& newStudent);
        void printInTheTable(QTableWidget* table);
        void printInTheTableWithNotes(QTableWidget* table);
        void deleteStudent(int index);
        void getTheWinners();
};

#endif // STUDENTGROUP_H
