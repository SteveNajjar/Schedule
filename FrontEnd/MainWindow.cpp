#include "MainWindow.h"
#include <QComboBox>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>

MainWindow::MainWindow()
{
    setWindowTitle("Stater Scheduler");
    resize(1000, 600);

    // Create a table with 12 rows and 3 columns
    tableWidget = new QTableWidget(14, 3, this);
    tableWidget->setGeometry(100, 100, 800, 450);

    // Set column headers
    tableWidget->setHorizontalHeaderLabels({
        "Employee Name",
        "Time In",
        "Time Out"
    });

    // Make columns fill the table
    tableWidget->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    // Create dropdown menus for every row
    for (int row = 0; row < 14; row++)
    {
        // Employee dropdown
        QComboBox *nameInput = new QComboBox();
	nameInput->setEditable(true);
	nameInput->setFrame(false);
        nameInput->addItem("Select employee");
        nameInput->addItems(getEmployees());

        // Start time dropdown
        QComboBox *timeIn = new QComboBox();
	timeIn->setEditable(true);
	timeIn->setFrame(false);
        timeIn->addItem("Select start time");
        timeIn->addItems(getStartTimes());

        // End time dropdown
        QComboBox *timeOut = new QComboBox();
	timeOut->setEditable(true);
	timeOut->setFrame(false);
        timeOut->addItem("Select end time");
        timeOut->addItems(getEndTimes());

        // Insert dropdowns into the table
        tableWidget->setCellWidget(row, 0, nameInput);
        tableWidget->setCellWidget(row, 1, timeIn);
        tableWidget->setCellWidget(row, 2, timeOut);
    }
}

