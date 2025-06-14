#include "globalVariables.h"
#include "globalFunctions.h"

#include <QTableWidgetItem>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QString>
#include <fstream>

using namespace std;

StudentGroup myGroup;

void addToTheGroup(Student& newStudent)
    {myGroup.addStudent(newStudent);}

void printTheTable(QTableWidget* table)
    {myGroup.printInTheTable(table);}

void printTheTableWithNotes(QTableWidget* table)
    {myGroup.printInTheTableWithNotes(table);}

void purgeString(string& word)
{
    size_t result=0;
    while((result=word.find_first_not_of("abcdefghijklmnopqrstuvwxyz" "äöüß" "ABCDEFGHILJKLMNOPQRSTUVWXYZ""ÄÖÜ"))!=string::npos)
    {word.erase(result, 1);}
}

int countTheNumberofStudents(string fileName)
{
    fstream source(fileName);
    string word = "";

    int counter = 0;
    while (source >> word)
    {
        purgeString(word);
        if(word == "Schueler")       {counter++;}
    }
    return counter;
}

void getDataFromFile(string fileName, clickableWidget* obj)
{
    int numOfStudentsFromTheFile = countTheNumberofStudents(fileName);

    if(numOfStudentsFromTheFile + myGroup.getSizeOfStudents() > 30)
        {QMessageBox::warning(obj, "Achtung", "Die Größe der Groupe darf maximal 30 sein");}

    else if(numOfStudentsFromTheFile + myGroup.getSizeOfStudents() <= 30)
    {
        fstream source(fileName);
        string word = "";
        string firstname = "";
        string lastname = "";
        string birthday = "";
        string firstJump = "";
        string secondJump = "";

        while (source >> word)
        {
            purgeString(word);
            if(word == "Schueler")
            {
                source >> firstname;
                source >> lastname;
                source >> birthday;
                source >> firstJump;
                source >> secondJump;

                Student temp(firstname, lastname, birthday, firstJump, secondJump);
                myGroup.addStudent(temp);
            }
        }
        source.close();
    }
}

void deleteFromTheGroup(int index)
    {myGroup.deleteStudent(index);}


void printTheWinners(string& str1, string& str2, clickableWidget* obj)
{
    if(myGroup.getSizeOfStudents() == 0)
        {QMessageBox::warning(obj, "Achtung", "Keine Daten gefunden!");}

    else if(myGroup.getSizeOfStudents() > 0)
    {
        myGroup.getTheWinners();
        str1 = myGroup.getFirstWinner();
        str2 = myGroup.getSecondWinner();
    }
}

void writeInTheTextFile(string fileName)
{
    ofstream out(fileName);

    for(int i = 0; i < myGroup.getSizeOfStudents(); i++)
    {
        out << "Schüler " << i + 1 << ": ";
        out << myGroup.getStudent(i)->getFirstName() << "\t\t";
        out << myGroup.getStudent(i)->getLastName() << "\t\t";
        out << myGroup.getStudent(i)->getBirthday() << "\t\t";
        out << myGroup.getStudent(i)->getFirstJumpStr() << "\t\t";
        out << myGroup.getStudent(i)->getSecondJumpStr() << endl;
    }
}

void writeInThePDFFile(string fileName)
{
    QPdfWriter writer(fileName.c_str());
    writer.setPageSize(QPageSize::A4);
    writer.setResolution(300);

    QPainter painter(&writer);
    int yRect = 100;
    QRect rect(50, yRect, 2300, 100);
    painter.setFont(QFont("Times", 22, QFont::Bold));

    painter.drawText(rect, Qt::AlignCenter, "Die Daten der Schüler");

    int startX = 50;
    int startY = 300;
    int cellWidth = 450;
    int cellHeight = 80;

    QStringList header = {"Vorname", "Nachname", "Geb.-Datum", "1. Sprung", "2. Sprung"};
    int spalten = header.size();
    painter.setFont(QFont("Times", 12, QFont::Bold));

    for(int i = 0; i < spalten; i++)
    {
        QRect tempRect(startX + (i * cellWidth), startY, cellWidth, cellHeight);
        painter.drawRect(tempRect);
        painter.drawText(tempRect, Qt::AlignCenter, header[i]);
    }

    painter.setFont(QFont("Times", 12));

    for(int i = 0; i < myGroup.getSizeOfStudents(); i++)
    {
        QStringList arr = {
                            myGroup.getStudent(i)->getFirstName().c_str(),
                            myGroup.getStudent(i)->getLastName().c_str(),
                            myGroup.getStudent(i)->getBirthday().c_str(),
                            myGroup.getStudent(i)->getFirstJumpStr().c_str(),
                            myGroup.getStudent(i)->getSecondJumpStr().c_str()};

        cellHeight += 100;

        for(int i = 0; i < spalten; i++)
        {
            QRect tempRect(startX + (i * cellWidth), startY, cellWidth, cellHeight);
            painter.drawRect(tempRect);
            painter.drawText(tempRect, Qt::AlignCenter, arr[i]);
        }
    }

    painter.end();
}
