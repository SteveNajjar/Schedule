#include "MainWindow.h"
#include <QLineEdit>
#include <QComboBox>
#include <QString>

MainWindow::MainWindow()
{
    //std::string time_array[2] = {"6:00am", "6:30am"};
    //QList<QString> times = {"6:00am", "6:30am"};
    QString employee_one = "Ryland Williams";
    QString employee_two = "Evan Winkler";
    QString employee_three = "Steve Najjar";
    QList<QString> people;
    people.append(employee_one);
    people.append(employee_two);
    people.append(employee_three);

    setWindowTitle("Stater Scheduler");
    resize(1000,600);

    nameInput = new QComboBox(this);
    nameInput->setPlaceholderText("Enter your name");
    nameInput->setGeometry(0, 100, 200, 30);
    nameInput->addItems(QStringList(people));

    timeIn = new QComboBox(this);
    timeIn->setPlaceholderText("Choose a start time");
    timeIn->setGeometry(400, 100, 200, 30);
    timeIn->addItems(QStringList(getStartTimes()));

    timeOut = new QComboBox(this);
    timeOut->setPlaceholderText("Choose an end time");
    timeOut->setGeometry(800, 100, 200, 30);
    timeOut->addItems(QStringList(getEndTimes()));



}
