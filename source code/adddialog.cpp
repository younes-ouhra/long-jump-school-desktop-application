#include "adddialog.h"
#include "student.h"
#include "globalFunctions.h"
#include "clickablewidget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

AddDialog::AddDialog(clickableWidget* parent)
    : theParent(parent)
{
    myButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    validButton = myButtonBox->button(QDialogButtonBox::Ok);
    validButton->setText("Bestätigen");

    cancelButton = myButtonBox->button(QDialogButtonBox::Cancel);
    cancelButton->setText("Abbrechen");

    firstName = new QLabel("Vorname", this);
    lastName = new QLabel("Nachname", this);
    birthday = new QLabel("Geburtsdatum (TT.MM.JJJJ)", this);
    firstJump = new QLabel("1. Sprung", this);
    secondJump = new QLabel("2. Sprung", this);

    firstNameLE = new QLineEdit(this);
    lastNameLE = new QLineEdit(this);
    birthday_day = new QSpinBox(this);
    birthday_month = new QSpinBox(this);
    birthday_year = new QSpinBox(this);
    firstJumpLE = new QLineEdit(this);
    secondJumpLE = new QLineEdit(this);

    //////////////////////////////////////////////////////////////////////////////////////////

    birthday_day->setRange(1, 31);
    birthday_month->setRange(1, 12);
    birthday_year->setMinimum(2000);
    birthday_year->setMaximum(2025);
    birthday_day->setValue(1);
    birthday_month->setValue(1);

    int start_x = 100;
    int start_y = 80;
    int label_width = 150;
    int label_height = 21;

    firstName->setGeometry(start_x, start_y, label_width, label_height);
    lastName->setGeometry(start_x, start_y + 30, label_width, label_height);
    birthday->setGeometry(start_x, start_y + 60, label_width, label_height);
    firstJump->setGeometry(start_x, start_y + 90, label_width, label_height);
    secondJump->setGeometry(start_x, start_y + 120, label_width, label_height);

    start_x = start_x + label_width + 10;
    firstNameLE->setGeometry(start_x, start_y, label_width + 70, label_height);
    lastNameLE->setGeometry(start_x, start_y + 30, label_width + 70, label_height);
    birthday_day->setGeometry(start_x, start_y + 60, 60, 21);
    birthday_month->setGeometry(start_x + 70, start_y + 60, 60, 21);
    birthday_year->setGeometry(start_x + 140, start_y + 60, 80, 21);
    firstJumpLE->setGeometry(start_x, start_y + 90, label_width + 70, label_height);
    secondJumpLE->setGeometry(start_x, start_y + 120, label_width + 70, label_height);
    myButtonBox->setGeometry(300, 260, 160, 25);

    //////////////////////////////////////////////////////////////////////////////////////////

    connect(myButtonBox, &QDialogButtonBox::accepted, this, &AddDialog::onValidClicked);
    connect(myButtonBox, &QDialogButtonBox::rejected, this, &AddDialog::onCancelClicked);
}

AddDialog::~AddDialog()
{
    delete firstName;
    delete lastName;
    delete birthday;
    delete firstJump;
    delete secondJump;
    delete firstNameLE;
    delete lastNameLE;
    delete birthday_day;
    delete birthday_month;
    delete birthday_year;
    delete firstJumpLE;
    delete secondJumpLE;
    delete myButtonBox;
    delete validButton;
    delete cancelButton;
}

void AddDialog::onCancelClicked()
{
    this->close();
}

void AddDialog::onValidClicked()
{
    if (firstNameLE->text().isEmpty() || lastNameLE->text().isEmpty() || birthday_day->text().isEmpty() || birthday_month->text().isEmpty() || birthday_year->text().isEmpty() || firstJumpLE->text().isEmpty() || secondJumpLE->text().isEmpty())
        {QMessageBox::warning(this, "Achtung", "Die Eingaben dürfen nicht leer sein!");}

    else
    {
        QString QStringFirstName = firstNameLE->text();
        QString QStringLastName = lastNameLE->text();
        QString QStringBirthday_day = birthday_day->text();
        QString QStringBirthday_month = birthday_month->text();
        QString QStringBirthday_year = birthday_year->text();
        QString QStringFirstJump = firstJumpLE->text();
        QString QStringSecondJump = secondJumpLE->text();

        vector <QString> vec = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

        for (const auto& it : vec)
        {
            if (QStringBirthday_day == it)
                {QStringBirthday_day = "0" + QStringBirthday_day;}

            if (QStringBirthday_month == it)
                {QStringBirthday_month = "0" + QStringBirthday_month;}
        }

        QString QStringBirthday = QStringBirthday_day + "." + QStringBirthday_month + "." + QStringBirthday_year;

        if(!(isThisDouble(QStringFirstJump)) || !(isThisDouble(QStringSecondJump)))
            {QMessageBox::warning(this, "Achtung", "Die Eingaben sind ungültig!");}

        else if((isThisDouble(QStringFirstJump)) && (isThisDouble(QStringSecondJump)))
        {
            Student temp(QStringFirstName.toStdString(), QStringLastName.toStdString(), QStringBirthday.toStdString(), QStringFirstJump.toStdString(), QStringSecondJump.toStdString());
            addToTheGroup(temp);
            printTheTable(theParent->table);
            this->close();
        }
    }
}

bool isThisDouble(const QString& myQString)
{
    string myString = myQString.toStdString();
    int kommaCount = 0;

    for (char c : myString)
    {
        if (c == ',')
        {
            kommaCount++;
            if (kommaCount > 1) return false; // Mehr als ein Komma
        }

        else if (!isdigit(c))
        {return false;}
    }

    return !myString.empty() && myString != "," && kommaCount <= 1;
}
