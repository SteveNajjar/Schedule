#include "MainWindow.h"
#include <QLineEdit>
#include <QComboBox>

MainWindow::MainWindow()
{
    setWindowTitle("My First GUI!");
    resize(500,300);

    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter your name: ");
    nameInput->setGeometry(150, 100, 200, 30);

    dropDown = new QComboBox(this);
    dropDown->setPlaceholderText("Choose a time");
    dropDown->setGeometry(150, 150, 200, 30);

}