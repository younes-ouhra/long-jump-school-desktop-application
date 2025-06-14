#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

#include "clickablewidget.h"
#include "student.h"
#include <QTableWidgetItem>

void addToTheGroup(Student& newStudent);

void printTheTable(QTableWidget* table);

void printTheTableWithNotes(QTableWidget* table);

int countTheNumberofStudents(string fileName);

void getDataFromFile(string fileName, clickableWidget* obj);

void deleteFromTheGroup(int index);

void printTheWinners(string& str1, string& str2, clickableWidget* obj);

void writeInTheTextFile(string fileName);

void writeInThePDFFile(string fileName);

#endif // GLOBALFUNCTIONS_H
