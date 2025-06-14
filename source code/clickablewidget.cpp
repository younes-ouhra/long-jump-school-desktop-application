#include "clickablewidget.h"
#include "globalFunctions.h"
#include "adddialog.h"
#include "globalVariables.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QTextEdit>
//#include <QFileDialog>
#include <QDir>
#include <QPushButton>

using namespace std;

QString lastFileName;

clickableWidget::clickableWidget(QWidget *parent):QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    widgetTitel = new QLabel("Goethe Kepler Grundschule", this);
    widgetSubTitel = new QLabel("Sportunterricht - Weitsprung", this);
    menuBar = new QMenuBar(this);
    QAction* importAction = new QAction("Daten importieren", this);
    QAction* exportAction = new QAction("Daten exportieren", this);
    QAction* quitAction = new QAction("schließen", this);
    button_update = new QPushButton("aktualisieren", this);
    button_add = new QPushButton("Schüler/-in hinzufügen", this);
    button_delete = new QPushButton("Schüler/-in löschen", this);
    button_delete->setEnabled(false);
    button_printTheWinners = new QPushButton("Die beiden Pokalsieger ausgeben", this);
    button_printTheWinners->setStyleSheet("font-weight: bold;");
    table = new QTableWidget(this);

    importDialog = new QFileDialog(this);
    exportDialog = new QFileDialog(this);

    connect(importDialog, &QFileDialog::rejected, this, &clickableWidget::onImportDialogRejected);
    connect(exportDialog, &QFileDialog::rejected, this, &clickableWidget::onExportDialogRejected);

    /////////////////////////////////////////////////////////////////////////////

    widgetTitel->setGeometry(275, 30, 300, 30);
    widgetTitel->setStyleSheet("font-size: 24px; color: blue;");
    widgetTitel->setAlignment(Qt::AlignCenter);

    widgetSubTitel->setGeometry(275, 60, 300, 30);
    widgetSubTitel->setStyleSheet("font-size: 16px; color: blue;");
    widgetSubTitel->setAlignment(Qt::AlignCenter);

    /////////////////////////////////////////////////////////////////////////////

    fileMenu = menuBar->addMenu("Datei");
    fileMenu->addAction(importAction);
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    connect(importAction, &QAction::triggered, this, &clickableWidget::onImportClicked);
    connect(exportAction, &QAction::triggered, this, &clickableWidget::onExportClicked);
    connect(quitAction, &QAction::triggered, this, &clickableWidget::onQuitClicked);

    layout->setMenuBar(menuBar);

    /////////////////////////////////////////////////////////////////////////////

    connect(button_add, &QPushButton::clicked, this, &clickableWidget::onAddClicked);
    connect(button_delete, &QPushButton::clicked, this, &clickableWidget::onDeleteClicked);
    connect(button_update, &QPushButton::clicked, this, &clickableWidget::onUpdateClicked);
    connect(button_printTheWinners, &QPushButton::clicked, this, &clickableWidget::onPrintTheWinnersClicked);

    button_update->setGeometry(800, 120, 150, 40);
    button_add->setGeometry(800, 200, 150, 40);
    button_delete->setGeometry(800, 280, 150, 40);
    button_printTheWinners->setGeometry(1000, 600, 200, 40);

    /////////////////////////////////////////////////////////////////////////////

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setColumnCount(5);
    table->setRowCount(20);

    connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [=]()
        {button_delete->setEnabled(table->selectionModel()->hasSelection());});

    QStringList* headers = new QStringList{"Vorname", "Nachname", "Geb.", "1. Sprung", "2. Sprung"};
    table->setHorizontalHeaderLabels(*headers);
    table->setGeometry(160, 100, 535, 600);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    delete headers;
}

clickableWidget::~clickableWidget()
{
    delete menuBar;
    delete fileMenu;
    delete table;
    delete button_update;
    delete button_add;
    delete button_delete;
    delete button_printTheWinners;
    delete widgetTitel;
    delete widgetSubTitel;
    delete myAddDialog;
    delete importDialog;
    delete exportDialog;
}

void clickableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        {table->clearSelection();}
}

void clickableWidget::onImportClicked()
{
    QString fileName = importDialog->getOpenFileName(this, "Datei importieren", QDir::homePath());

    if(!fileName.isEmpty())
    {
        lastFileName = fileName;
        string file = fileName.toStdString();

        getDataFromFile(file, this);
        printTheTable(this->table);
    }
}

void clickableWidget::onExportClicked()
{
    QString fileNameQstr = exportDialog->getSaveFileName(this, "Datei speichern unter", QDir::homePath(), "Textdateien (*.txt);;PDF-Dateien (*.pdf)");

    if(!fileNameQstr.isEmpty())
    {
        string fileNameStr = fileNameQstr.toStdString();
        string fileTyp = fileNameStr.substr(fileNameStr.size()-3, fileNameStr.size()-1);

        if(fileTyp == "txt")
            {writeInTheTextFile(fileNameStr);}

        else if(fileTyp == "pdf")
            {writeInThePDFFile(fileNameStr);}
    }
}

void clickableWidget::onQuitClicked()
    {this->close();}

void clickableWidget::onTableItemClicked()
    {button_delete->setEnabled(true);}

void clickableWidget::onAddClicked()
{
    myAddDialog = new AddDialog(this);
    myAddDialog->setObjectName("Schüler/-in hinzufügen");
    myAddDialog->setModal(true);
    myAddDialog->exec();
}

void clickableWidget::onDeleteClicked()
{
    QTableWidgetItem* item = table->currentItem();          //Einzelnes selektiertes Item abrufen
    if (item)
    {
        int selectedRow = item->row();
        deleteFromTheGroup(selectedRow);
        printTheTable(table);
    }
}

void clickableWidget::onUpdateClicked()
    {printTheTable(table);}

void clickableWidget::onPrintTheWinnersClicked()
{
    string winner1 = "";
    string winner2 = "";

    printTheWinners(winner1, winner2, this);

    if(winner1 != "" && winner2 != "")
    {
        table->setColumnCount(6);
        QStringList* headers = new QStringList{"Vorname", "Nachname", "Geb.", "1. Sprung", "2. Sprung", "Note"};
        table->setHorizontalHeaderLabels(*headers);
        delete headers;

        table->setGeometry(160, 100, 642, 600);
        button_update->setGeometry(1000, 120, 150, 40);
        button_add->setGeometry(1000, 200, 150, 40);
        button_delete->setGeometry(1000, 280, 150, 40);

        printTheTableWithNotes(table);
        string erg = winner1 + "\n" + winner2;
        QMessageBox::information(this, "Ergebnisse", erg.c_str());
    }
}

void clickableWidget::onImportDialogRejected()
    {importDialog->close();}

void clickableWidget::onExportDialogRejected()
    {exportDialog->close();}
