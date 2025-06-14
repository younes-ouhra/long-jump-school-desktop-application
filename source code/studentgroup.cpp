#include "studentgroup.h"

StudentGroup::StudentGroup():capacity(30), sizeOfStudents(0), sizeOfItems(0)
{
    arrayOfStudents = new Student*[30];
    arrayOfItems = new QTableWidgetItem*[150];

    for(int i = 0; i < 30; i++)
        {arrayOfStudents[i] = nullptr;}

    for(int i = 0; i < 150; i++)
        {arrayOfItems[i] = nullptr;}
}

StudentGroup::~StudentGroup()
{
    for (int i=0; i < sizeOfStudents; i++)
        {delete arrayOfStudents[i];}

    delete[] arrayOfStudents;

    for (int i=0; i < sizeOfItems; i++)
        {delete arrayOfItems[i];}

    delete[] arrayOfItems;
}

int StudentGroup::getSizeOfStudents() const
    {return sizeOfStudents;}

string StudentGroup::getFirstWinner() const
    {return firstWinner;}

string StudentGroup::getSecondWinner() const
    {return secondWinner;}

Student* StudentGroup::getStudent(int index) const
{
    if(index < sizeOfStudents)
        {return arrayOfStudents[index];}

    else
        {return nullptr;}
}

void StudentGroup::addStudent(Student& newStudent)
{
    if(sizeOfStudents < 30)
    {
        arrayOfStudents[sizeOfStudents++] = new Student(newStudent);

        arrayOfItems[sizeOfItems] = new QTableWidgetItem(QString::fromStdString(newStudent.getFirstName()));
        arrayOfItems[sizeOfItems++]->setTextAlignment(Qt::AlignCenter);

        arrayOfItems[sizeOfItems] = new QTableWidgetItem(QString::fromStdString(newStudent.getLastName()));
        arrayOfItems[sizeOfItems++]->setTextAlignment(Qt::AlignCenter);

        arrayOfItems[sizeOfItems] = new QTableWidgetItem(QString::fromStdString(newStudent.getBirthday()));
        arrayOfItems[sizeOfItems++]->setTextAlignment(Qt::AlignCenter);

        arrayOfItems[sizeOfItems] = new QTableWidgetItem(QString::fromStdString(newStudent.getFirstJumpStr()));
        arrayOfItems[sizeOfItems++]->setTextAlignment(Qt::AlignCenter);

        arrayOfItems[sizeOfItems] = new QTableWidgetItem(QString::fromStdString(newStudent.getSecondJumpStr()));
        arrayOfItems[sizeOfItems++]->setTextAlignment(Qt::AlignCenter);
    }
}

void StudentGroup::printInTheTable(QTableWidget* table)
{
    table->setRowCount(sizeOfStudents);
    int offset = 0;

    for(int i = 0; i < sizeOfStudents; i++)
    {
        for(int j = 0; j < 5; j++)
            {table->setItem(i, j, arrayOfItems[i+j+offset]);}

        offset = offset + 4;
    }
}

void StudentGroup::printInTheTableWithNotes(QTableWidget* table)
{
    for(int i = 0; i < sizeOfItems; i++)
        {delete arrayOfItems[i];}

    delete[] arrayOfItems;

    sizeOfItems = sizeOfStudents * 6;
    arrayOfItems = new QTableWidgetItem* [sizeOfItems];

    int x = 0;

    for(int i = 0; i < sizeOfStudents; i++)
    {
        arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getFirstName()));
        arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);

        arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getLastName()));
        arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);

        arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getBirthday()));
        arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);

        arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getFirstJumpStr()));
        arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);

        arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getSecondJumpStr()));
        arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);

        arrayOfItems[x] = new QTableWidgetItem(QString::number(arrayOfStudents[i]->getNote()));
        arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);
    }

    table->setRowCount(sizeOfStudents);
    table->setColumnCount(6);
    int offset = 0;

    for(int i = 0; i < sizeOfStudents; i++)
    {
        for(int j = 0; j < 6; j++)
            {table->setItem(i, j, arrayOfItems[i+j+offset]);}

        offset = offset + 5;
    }
}

void StudentGroup::deleteStudent(int index)
{
    if(index < 30)
    {
        for (int i = index; i < sizeOfStudents - 1; i++)
            {arrayOfStudents[i] = arrayOfStudents[i + 1];}

        arrayOfStudents[sizeOfStudents - 1] = nullptr;
        delete arrayOfStudents[sizeOfStudents - 1];
        sizeOfStudents = sizeOfStudents - 1;

        for(int i = 0; i < sizeOfItems; i++)
            {delete arrayOfItems[i];}

        delete[] arrayOfItems;

        sizeOfItems = sizeOfStudents * 5;
        arrayOfItems = new QTableWidgetItem* [sizeOfItems];

        int x = 0;

        for(int i = 0; i < sizeOfStudents; i++)
        {
            arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getFirstName()));
            arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);

            arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getLastName()));
            arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);

            arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getBirthday()));
            arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);

            arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getFirstJumpStr()));
            arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);

            arrayOfItems[x] = new QTableWidgetItem(QString::fromStdString(arrayOfStudents[i]->getSecondJumpStr()));
            arrayOfItems[x++]->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void StudentGroup::getTheWinners()
{
    for(int i = 0; i < sizeOfStudents; i++)
        {arrayOfStudents[i]->countTheNote();}

    int indexWinner1 = 0;

    for(int i = 1; i < sizeOfStudents; i++)
    {
        if(arrayOfStudents[i]->getNote() < arrayOfStudents[indexWinner1]->getNote())
            {indexWinner1 = i;}
    }

    int indexWinner2 = indexWinner1;

    for(int i = 1; i < sizeOfStudents; i++)
    {
        if(arrayOfStudents[i]->getNote() <= arrayOfStudents[indexWinner2]->getNote())
            {indexWinner2 = i;}
    }

    firstWinner = arrayOfStudents[indexWinner1]->getFirstName() + " " + arrayOfStudents[indexWinner1]->getLastName() + " " + arrayOfStudents[indexWinner1]->getBirthday();
    secondWinner = arrayOfStudents[indexWinner2]->getFirstName() + " " + arrayOfStudents[indexWinner2]->getLastName() + " " + arrayOfStudents[indexWinner2]->getBirthday();
}
