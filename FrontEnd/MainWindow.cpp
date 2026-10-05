#include "MainWindow.h"
#include <QLineEdit>
#include <QComboBox>
#include <QString>

MainWindow::MainWindow()
{


    setWindowTitle("Stater Scheduler");
    resize(1000,600);

    nameInput = new QComboBox(this);
    nameInput->setPlaceholderText("Enter your name");
    nameInput->setGeometry(0, 100, 200, 30);
    nameInput->addItems(QStringList(getEmployees()));

    timeIn = new QComboBox(this);
    timeIn->setPlaceholderText("Choose a start time");
    timeIn->setGeometry(400, 100, 200, 30);
    timeIn->addItems(QStringList(getStartTimes()));

    timeOut = new QComboBox(this);
    timeOut->setPlaceholderText("Choose an end time");
    timeOut->setGeometry(800, 100, 200, 30);
    timeOut->addItems(QStringList(getEndTimes()));



}
