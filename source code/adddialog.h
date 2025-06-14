#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include "clickablewidget.h"
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialog>
#include <QLabel>
namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(clickableWidget* parent = nullptr);
    ~AddDialog();
    void onCancelClicked();
    void onValidClicked();

private:
    QLabel* firstName;
    QLabel* lastName;
    QLabel* birthday;
    QLabel* firstJump;
    QLabel* secondJump;

    QLineEdit* firstNameLE;
    QLineEdit* lastNameLE;
    QSpinBox* birthday_day;
    QSpinBox* birthday_month;
    QSpinBox* birthday_year;
    QLineEdit* firstJumpLE;
    QLineEdit* secondJumpLE;
    QDialogButtonBox* myButtonBox;
    QPushButton* validButton;
    QPushButton* cancelButton;
    clickableWidget* theParent;
};

bool isThisDouble(const QString& myQString);

#endif // ADDDIALOG_H
