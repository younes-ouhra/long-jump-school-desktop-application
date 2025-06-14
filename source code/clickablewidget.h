#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include <QString>
#include <QLabel>
#include <QWidget>
#include <QMenuBar>
#include <QFileDialog>
#include <QPushButton>
#include <QTableWidget>
#include <QDialogButtonBox>

using namespace std;

class clickableWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit clickableWidget(QWidget *parent = nullptr);
        ~clickableWidget();

    protected:
        QDialog* myAddDialog;
        QMenuBar* menuBar;
        QMenu* fileMenu;
        QTableWidget* table;
        QPushButton* button_update;
        QPushButton* button_add;
        QPushButton* button_delete;
        QPushButton* button_printTheWinners;
        QLabel* widgetTitel;
        QLabel* widgetSubTitel;
        QFileDialog* importDialog;
        QFileDialog* exportDialog;

    public:
        void mousePressEvent(QMouseEvent *event) override;
        void onImportClicked();
        void onExportClicked();
        void onQuitClicked();
        void onTableItemClicked();
        void onAddClicked();
        void onDeleteClicked();
        void onUpdateClicked();
        void onPrintTheWinnersClicked();
        void onImportDialogRejected();
        void onExportDialogRejected();

    friend class AddDialog;
};

#endif
