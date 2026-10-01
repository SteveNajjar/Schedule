#include "MainWindow.h"
#include <QLineEdit>
#include <QComboBox>
#include <QString>

MainWindow::MainWindow()
{
    QString employee_one = "Ryland Williams";
    QString employee_two = "Evan Winkler";
    QString employee_three = "Steve Najjar";
    employees = new QList<QString>;
    employees->append(employee_one);
    employees->append(employee_two);
    employees->append(employee_three);
    names = new QStringList(employees);
    //times =     new QStringList();

    setWindowTitle("Stater Scheduler");
    resize(1000,600);

    nameInput = new QComboBox(this);
    nameInput->setPlaceholderText("Enter your name");
    nameInput->setGeometry(0, 100, 200, 30);
    nameInput->addItems(names);

    timeIn = new QComboBox(this);
    timeIn->setPlaceholderText("Choose a start time");
    timeIn->setGeometry(400, 100, 200, 30);

    timeOut = new QComboBox(this);
    timeOut->setPlaceholderText("Choose an end time");
    timeOut->setGeometry(800, 100, 200, 30);



}
